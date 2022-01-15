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

#ifndef _LEXER_H_
#define _LEXER_H_

#include <ctype.h>
#include <string.h>

#include "../log/log.h"
#include "../token/position.h"
#include "../token/token.h"

typedef struct LEXER_STRUCT {
  char *filename;
  char *input;
  size_t input_length;
  token_pos_T current_position;
  char current_character;
  char next_character;
} lexer_T;

lexer_T *init_lexer(char *filename, char *input);

/**
 * @brief   Update current_character and next_character members
 * @param   lexer   lexer struct
 */
static void update_lexer(lexer_T *lexer);
static void advance_lexer(lexer_T *lexer);
static void skip_whitespace(lexer_T *lexer);

static token_T *get_name_token(lexer_T *lexer);
static token_T *get_number_token(lexer_T *lexer);
static token_T *get_comment_token(lexer_T *lexer);
static token_T *get_string_token(lexer_T *lexer);
token_T *next_token(lexer_T *lexer);

static bool letter(char character);
static bool punctuator(char character);
static bool finished(lexer_T *lexer);

#endif /* _LEXER_H_ */