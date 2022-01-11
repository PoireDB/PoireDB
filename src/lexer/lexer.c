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

#include "../include/lexer/lexer.h"

lexer_T *init_lexer(char *filename, char *input)
{
  lexer_T *lexer = calloc(1, sizeof(struct LEXER_STRUCT));
  lexer->filename = filename;
  lexer->input = input;
  lexer->input_length = strlen(input);
  lexer->current_position = init_token_position(1, 1, 0);
  return lexer;
}

static void update_lexer(lexer_T *lexer)
{
  lexer->current_character = lexer->input[lexer->current_position->index];
  if (lexer->current_position->index + 1 >= lexer->input_length)
    lexer->next_character = '\0';
  lexer->next_character = lexer->input[lexer->current_position->index + 1];
}

static void advance_lexer(lexer_T *lexer)
{
  switch (lexer->current_character)
  {
  case '\n':
    lexer->current_position->column = 0;
    lexer->current_position->line++;
    break;
  default:
    lexer->current_position->column++;
    break;
  }
  lexer->current_position->index++;
  update_lexer(lexer);
}

static void skip_whitespace(lexer_T *lexer)
{
  while (isspace(lexer->current_character))
    advance_lexer(lexer);
}

token_T *next_token(lexer_T *lexer)
{
  token_T *error_token = init_token(
      ERROR,
      lexer->current_position,
      advance_token_position(lexer->current_position),
      init_token_value_with_character(lexer->current_character));
  advance_lexer(lexer);
  return error_token;
}