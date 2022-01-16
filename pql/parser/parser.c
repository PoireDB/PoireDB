/**
 * MIT License
 * Copyright (c) 2022 PoireDB authors and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "../include/parser/parser.h"

static char *dump_token_type(token_type_T type) {
  return _dumped_token_types[type];
}

parser_T *init_parser(lexer_T *lexer) {
  parser_T *parser = calloc(1, sizeof(struct PARSER_STRUCT));
  parser->lexer = lexer;
  parser->current_token = check_next_token(parser);
  return parser;
}

token_T *check_next_token(parser_T *parser) {
  token_T *tok = next_token(parser->lexer);
  if (tok->type == ERROR) {
    log_error("unable to process token at %s-%s: `%c`:(%d)",
              dump_token_position(tok->start_pos),
              dump_token_position(tok->end_pos), tok->value->character,
              (int)tok->value->character);
    exit(1);
  }
  return tok;
}

query_AST_T *parser_parse(parser_T *parser) {
  /* ========= parse db top statement ========= */
  require_keyword_token(parser, "db");
  char *database_name = parser->current_token->value->string;
  require_token(parser, VSTRING);
  require_punctuator(parser, ';');

  top_statement_AST_T **top_compound = parser_parse_top_statements(parser);

  /* ========= return AST ========= */
  query_AST_T *ast = init_query_AST(database_name);
  ast->top_compound = top_compound;
  return ast;
}

top_statement_AST_T **parser_parse_top_statements(parser_T *parser) {
  top_statement_AST_T **top_compound =
      calloc(100000, sizeof(struct TOP_STATEMENT_AST_STRUCT *));
  size_t current_stmt_index = 0;
  while (parser->current_token->type != _EOF) {
    top_compound[current_stmt_index] = parser_parse_top_statement(parser);
    current_stmt_index++;
  }
  return top_compound;
}

top_statement_AST_T *parser_parse_top_statement(parser_T *parser) {
  switch (parser->current_token->type) {
  case KEYWORD: {
    char *keyword = parser->current_token->value->string;
    if (strcmp(keyword, "delete") == 0)
      return parser_parse_delete_top_statement(parser);
    if (strcmp(keyword, "table") == 0)
      return parser_parse_table_top_statement(parser);
  }
  default:
    printf("i don't know %d: %s", parser->current_token->type,
           parser->current_token->value->string);
    // printf("i don't know %c", parser->current_token->type);
    exit(1);
  }
  return NULL;
}

top_statement_AST_T *parser_parse_delete_top_statement(parser_T *parser) {
  /* ========= parse delete top statement ========= */
  require_keyword_token(parser, "delete");
  char *table_name = parser->current_token->value->string;
  require_token(parser, IDENTIFIER);
  require_punctuator(parser, ';');

  /* ========= initialize delete top statement AST ========= */
  delete_top_statement_AST_T *delete_stmt_ast =
      calloc(1, sizeof(struct DELETE_TOP_STATEMENT_AST_STRUCT));
  delete_stmt_ast->table_name = table_name;

  /* ======= initialize more general (top statement) AST and return ======= */
  top_statement_AST_T *ast = init_top_statement_AST(DELETE);
  ast->statement.delete_stmt = delete_stmt_ast;
  return ast;
}

top_statement_AST_T *parser_parse_table_top_statement(parser_T *parser) {
  /* ========= parse table top statement ========= */
  require_keyword_token(parser, "table");
  char *table_name = parser->current_token->value->string;
  require_token(parser, IDENTIFIER);
  require_punctuator(parser, '{');
  require_punctuator(parser, '}');
  require_punctuator(parser, ';');

  /* ========= initialize delete top statement AST ========= */
  table_top_statement_AST_T *table_stmt_ast =
      calloc(1, sizeof(struct TABLE_TOP_STATEMENT_AST_STRUCT));
  table_stmt_ast->table_name = table_name;

  /* ======= initialize more general (top statement) AST and return ======= */
  top_statement_AST_T *ast = init_top_statement_AST(TABLE);
  ast->statement.table_stmt = table_stmt_ast;
  return ast;
}

#define POS_ARGS                                                               \
  parser->lexer->filename, parser->current_token->start_pos.line,              \
      parser->current_token->start_pos.column,                                 \
      parser->current_token->end_pos.line,                                     \
      parser->current_token->end_pos.column

void require_token(parser_T *parser, token_type_T token_type) {
  if (parser->current_token->type != token_type) {
    log_error("%s:(%d:%d::%d:%d): unexcepted: `%s`, excepted `%s` token",
              POS_ARGS, dump_token_type(parser->current_token->type),
              dump_token_type(token_type));
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}

void require_keyword_token(parser_T *parser, char *keyword) {
  if (parser->current_token->type != KEYWORD) {
    log_error("%s:(%d:%d::%d:%d): unexcepted: `%s`, excepted `%s` token "
              "(keyword=`%s`)",
              POS_ARGS, dump_token_type(parser->current_token->type),
              dump_token_type(KEYWORD), keyword);
    exit(1);
  }
  if (strcmp(parser->current_token->value->string, keyword)) {
    printf("%s:(%d:%d::%d:%d): unexcepted keyword: `%s`, excepted: `%s`",
           POS_ARGS, parser->current_token->value->string, keyword);
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}

void require_punctuator(parser_T *parser, char punctuator) {
  if (parser->current_token->type != PUNCTUATOR) {
    log_error("%s:(%d:%d::%d:%d): unexcepted: `%s`, excepted punctuator: `%c`",
              POS_ARGS,
              dump_token_value(parser->current_token->value,
                               parser->current_token->type),
              punctuator);
    exit(1);
  }
  if (parser->current_token->value->character != punctuator) {
    log_error("%s:(%d:%d::%d:%d): unexcepted punctuator: `%c`", POS_ARGS,
              parser->current_token->value->character);
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}