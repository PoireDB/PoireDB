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
    if (strcmp(keyword, "delete") == 0) {
      return parser_parse_delete_top_statement(parser);
    }
  }
  default:
    printf("i don't know %d: %c", parser->current_token->type,
           parser->current_token->value->character);
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
  // printf("EVERYTHING IS OK!!!!!!!");
  // exit(1);
  ast->statement.delete_stmt = delete_stmt_ast;
  return ast;
}

void require_token(parser_T *parser, token_type_T token_type) {
  if (parser->current_token->type != token_type) {
    log_error("unexcepted: `%s`",
              dump_token_value(parser->current_token->value,
                               parser->current_token->type));
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}

void require_keyword_token(parser_T *parser, char *keyword) {
  if (parser->current_token->type != KEYWORD) {
    log_error("unexcepted: `%s`, excepted keyword: `%s`",
              dump_token_value(parser->current_token->value,
                               parser->current_token->type),
              keyword);
    exit(1);
  }
  if (strcmp(parser->current_token->value->string, keyword)) {
    printf("unexcepted keyword: `%s`, excepted: `%s`",
           parser->current_token->value->string, keyword);
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}

void require_punctuator(parser_T *parser, char punctuator) {
  if (parser->current_token->type != PUNCTUATOR) {
    log_error("unexcepted: `%s`, excepted punctuator: `%c`",
              dump_token_value(parser->current_token->value,
                               parser->current_token->type),
              punctuator);
    exit(1);
  }
  if (parser->current_token->value->character != punctuator) {
    log_error("unexcepted punctuator: `%c`",
              parser->current_token->value->character);
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}