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

static token_T *init_token_with_null_pos(token_type_T type, token_value_T *value)
{
  return init_token(
      type,
      (token_pos_T){.index = 0, .line = 0, .column = 0},
      (token_pos_T){.index = 0, .line = 0, .column = 0},
      value);
}

parser_T *init_parser(
    lexer_T *lexer,
    void (*lexing_error)(token_T *error_token),
    void (*unexcepted_tok_error_by_type)(token_type_T required_token_typed,
                                         token_T *unexcepted_token),
    void (*unexcepted_tok_error)(token_T *excepted_token, token_T *unexcepted_token))
{
  parser_T *parser = calloc(1, sizeof(struct PARSER_STRUCT));
  parser->lexer = lexer;
  parser->lexing_error = lexing_error;
  parser->unexcepted_tok_error_by_type = unexcepted_tok_error_by_type;
  parser->unexcepted_tok_error = unexcepted_tok_error;
  parser->prefix_triggers = calloc(PREFIXES_MAX_SIZE,
                                   sizeof(struct PARSER_PREFIX_TRIGGER_STRUCT *));
  parser->prefix_triggers_amount = 0;
  eat_next_token(parser);
  add_prefix_trigger_by_token(parser,
                              init_token_with_null_pos(
                                  KEYWORD, init_token_value_with_string("table")),
                              eat_table_statement);
  return parser;
}

static void eat_next_token(parser_T *parser)
{
  parser->current_token = next_token(parser->lexer);
}

static void require_token_by_type(parser_T *parser, token_type_T required_token_type)
{
  if (required_token_type != parser->current_token->type)
  {
    parser->unexcepted_tok_error_by_type(required_token_type, parser->current_token);
    exit(1);
  }
}

static void require_token(parser_T *parser, token_T *required)
{
  if (required != parser->current_token)
  {
    parser->unexcepted_tok_error(required, parser->current_token);
    exit(1);
  }
}

#ifdef cur_prefix
#warning "cur_prefix macro will be removed"
#undef cur_prefix
#endif

#define cur_prefix parser->prefix_triggers[parser->prefix_triggers_amount]

static void add_prefix_trigger_by_token(
    parser_T *parser, token_T *token_prefix, AST_T *(*eat_function)(parser_T *parser))
{
  cur_prefix->prefix_type = TOKEN_PREFIX;
  cur_prefix->token_prefix = token_prefix;
  cur_prefix->eat_function = eat_function;
  parser->prefix_triggers_amount++;
}

static void add_prefix_trigger_by_token_type(
    parser_T *parser, token_type_T type_prefix, AST_T *(*eat_function)(parser_T *parser))
{
  cur_prefix->prefix_type = TOKEN_TYPE_PREFIX;
  cur_prefix->type_prefix = type_prefix;
  cur_prefix->eat_function = eat_function;
  parser->prefix_triggers_amount++;
}

#undef cur_prefix

static AST_T *eat_table_statement(parser_T *parser)
{
  eat_next_token(parser);
  require_token_by_type(parser, VSTRING);
  char *table_name = parser->current_token->value->string;
}