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

#ifndef _PARSER_H_
#define _PARSER_H_

#include "../lexer/lexer.h"
#include "../AST/AST.h"

typedef struct PARSER_STRUCT
{
  lexer_T *lexer;
  token_T *current_token;
  void (*lexing_error)(token_T *error_token);
  void (*unexcepted_tok_error_by_type)(
      token_type_T required_token_typed, token_T *unexcepted_token);
  void (*unexcepted_tok_error)(
      token_T *excepted_token, token_T *unexcepted_token);

  // needed for registering a prefixes for statements eat functions:
#define PREFIXES_MAX_SIZE 100000
  struct PARSER_PREFIX_TRIGGER_STRUCT **prefix_triggers;
  size_t prefix_triggers_amount;
} parser_T;

typedef struct PARSER_PREFIX_TRIGGER_STRUCT
{
  enum
  {
    TOKEN_PREFIX,
    TOKEN_TYPE_PREFIX,
  } prefix_type;
  token_T *token_prefix;
  token_type_T type_prefix;
  AST_T *(*eat_function)(parser_T *parser);
} parser_prefix_trigger_t;

static token_T *init_token_with_null_pos(token_type_T type, token_value_T *value);

parser_T *init_parser(
    lexer_T *lexer,
    void (*lexing_error)(token_T *error_token),
    void (*unexcepted_tok_error_by_type)(token_type_T required_token_typed,
                                         token_T *unexcepted_token),
    void (*unexcepted_tok_error)(token_T *excepted_token, token_T *unexcepted_token));
static void eat_next_token(parser_T *parser);
static void require_token_by_type(parser_T *parser, token_type_T required_token_type);
static void require_token(parser_T *parser, token_T *required);
static void add_prefix_trigger_by_token(
    parser_T *parser, token_T *token_prefix, AST_T *(*eat_function)(parser_T *parser));
static void add_prefix_trigger_by_token_type(
    parser_T *parser, token_type_T type_prefix, AST_T *(*eat_function)(parser_T *parser));
static AST_T *eat_table_statement(parser_T *parser);

#endif /* _PARSER_H_ */