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
} parser_T;

parser_T *init_parser(lexer_T *lexer);
query_AST_T *parser_parse(parser_T *parser);
top_statement_AST_T **parser_parse_top_statements(parser_T *parser);
top_statement_AST_T *parser_parse_top_statement(parser_T *parser);
top_statement_AST_T *parser_parse_delete_top_statement(parser_T *parser);
token_T *check_next_token(parser_T *parser);
void require_token(parser_T *parser, token_type_T token_type);
void require_keyword_token(parser_T *parser, char *keyword);
void require_punctuator(parser_T *parser, char punctuator);

#endif /* _PARSER_H_ */