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

#ifndef _AST_H_
#define _AST_H_

#include <stdlib.h>

typedef struct DELETE_TOP_STATEMENT_AST_STRUCT {
  char *table_name;
} delete_top_statement_AST_T;

typedef enum TOP_STATEMENT_AST_TYPE { DELETE } top_statement_AST_type_T;

typedef struct TOP_STATEMENT_AST_STRUCT {
  top_statement_AST_type_T type;

  union {
    delete_top_statement_AST_T *delete_stmt;
  } * statement;
} top_statement_AST_T;

typedef struct QUERY_AST_STRUCT {
  char *database_name;
} query_AST_T;

query_AST_T *init_query_AST(char *database_name);
top_statement_AST_T *init_top_statement_AST(top_statement_AST_type_T type);

#endif /* _AST_H_ */