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
#include "../include/tau.h"
#include "../include/util/string.h"

TAU_MAIN()

TEST(foo, test_DBSTMT) {
  char *fish_text = "Lorem ipsum dolor sit amet, consectetuer "
                    "adipiscing elit. Aenean commodo ligula eget dolor";
  lexer_T *l = init_lexer("<testdata>", format("db `%s`;", fish_text));
  parser_T *p = init_parser(l);
  query_AST_T *AST = parser_parse(p);

  CHECK(strcmp(AST->database_name, fish_text) == 0);

  free(AST);
  free(l);
  free(p);
}

TEST(foo, test_DELETESTMT) {
  lexer_T *l = init_lexer("<testdata>", "db ``;\n"
                                        "delete account;");
  parser_T *p = init_parser(l);
  query_AST_T *AST = parser_parse(p);

  CHECK(AST->top_compound[0]->type == DELETE);
  CHECK(strcmp(AST->top_compound[0]->statement.delete_stmt->table_name,
               "account") == 0);

  free(AST);
  free(l);
  free(p);
}

TEST(foo, test_EMPTYTABLESTMT) {
  lexer_T *l = init_lexer("<testdata>", "db ``;\n"
                                        "table account {};");
  parser_T *p = init_parser(l);
  query_AST_T *AST = parser_parse(p);

  CHECK(AST->top_compound[0]->type == TABLE);
  CHECK(strcmp(AST->top_compound[0]->statement.table_stmt->table_name,
               "account") == 0);

  free(AST);
  free(l);
  free(p);
}