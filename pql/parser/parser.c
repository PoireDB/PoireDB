/** 
 *  MIT License
 *  Copyright (c) 2022 PoireDB authors and contributors
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "../include/parser/parser.h"

parser_T *init_parser(lexer_T *lexer)
{
  parser_T *parser = calloc(1, sizeof(struct PARSER_STRUCT));
  parser->lexer = lexer;
  parser->current_token = check_next_token(parser);
  return parser;
}

token_T *check_next_token(parser_T *parser)
{
  token_T *tok = next_token(parser->lexer);
  if (tok->type == ERROR)
  {
    log_fatal("Unexcepted token: `%c`:(%d)", tok->value->character, (int)tok->value->character);
    exit(1);
  }
  return tok;
}

query_AST_T *parser_parse(parser_T *parser)
{
  /* ========= parse db top statement ========= */
  require_keyword_token(parser, "db");
  char *database_name = parser->current_token->value->string;
  require_token(parser, VSTRING);
  require_punctuator(parser, ';');
  // while (parser->current_token->type != _EOF)
  // {
  //   }
  query_AST_T *ast = init_query_AST(database_name);
  return ast;
}

void require_token(parser_T *parser, token_type_T token_type)
{
  if (parser->current_token->type != token_type)
  {
    printf("unexcepted: `%s`", dump_token_value(parser->current_token->value, parser->current_token->type));
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}

void require_keyword_token(parser_T *parser, char *keyword)
{
  if (parser->current_token->type != KEYWORD)
  {
    printf("unexcepted: `%s`", dump_token_value(parser->current_token->value, parser->current_token->type));
    exit(1);
  }
  if (strcmp(parser->current_token->value->string, keyword))
  {
    printf("unexcepted keyword: `%s`, excepted: `%s`", parser->current_token->value->string, keyword);
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}

void require_punctuator(parser_T *parser, char punctuator)
{
  if (parser->current_token->type != PUNCTUATOR)
  {
    printf("unexcepted: `%s`", dump_token_value(parser->current_token->value, parser->current_token->type));
    exit(1);
  }
  if (parser->current_token->value->character != punctuator)
  {
    printf("unexcepted punctuator: `%c`", parser->current_token->value->character);
    exit(1);
  }
  parser->current_token = check_next_token(parser);
}