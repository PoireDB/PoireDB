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
  lexer->current_position = init_token_position(0, 1, 0);
  update_lexer(lexer);
  return lexer;
}

static void update_lexer(lexer_T *lexer)
{
  lexer->current_character = lexer->input[lexer->current_position.index];
  if (lexer->current_position.index + 1 >= lexer->input_length)
    lexer->next_character = '\0';
  lexer->next_character = lexer->input[lexer->current_position.index + 1];
}

static void advance_lexer(lexer_T *lexer)
{
  switch (lexer->current_character)
  {
  case '\n':
    lexer->current_position.column = 0;
    lexer->current_position.line++;
    break;
  default:
    lexer->current_position.column++;
    break;
  }
  lexer->current_position.index++;
  update_lexer(lexer);
}

static void skip_whitespace(lexer_T *lexer)
{
  while (isspace(lexer->current_character))
    advance_lexer(lexer);
}

static token_T *get_name_token(lexer_T *lexer)
{
  char *name_buffer = calloc(10000, sizeof(char));
  size_t current_index = 0;
  token_pos_T start_pos = lexer->current_position;
  while (letter(lexer->current_character))
  {
    name_buffer[current_index] = lexer->current_character;
    advance_lexer(lexer);
    current_index++;
  }
  name_buffer[current_index] = '\0';
  if (!strcmp(name_buffer, "true") || !strcmp(name_buffer, "false"))
  {
    return init_token(
        VBOOLEAN,
        start_pos,
        lexer->current_position,
        init_token_value_with_boolean(!strcmp(name_buffer, "true")));
  }
  return init_token(
      IDENTIFIER,
      start_pos,
      lexer->current_position,
      init_token_value_with_string(name_buffer));
}

static token_T *get_number_token(lexer_T *lexer)
{
  char *number_string_buffer = calloc(10000, sizeof(char));
  size_t current_index = 0;
  token_pos_T start_pos = lexer->current_position;
  while (isdigit(lexer->current_character))
  {
    number_string_buffer[current_index] = lexer->current_character;
    advance_lexer(lexer);
    current_index++;
  }
  number_string_buffer[current_index] = '\0';
  if (lexer->current_character != '.')
    goto ret;
  else
  {
    number_string_buffer[current_index] = '.';
    current_index++;
  }

floating_point:
  advance_lexer(lexer);
  while (isdigit(lexer->current_character))
  {
    number_string_buffer[current_index] = lexer->current_character;
    advance_lexer(lexer);
    current_index++;
  }

ret:
{
  double number = atof(number_string_buffer);
  return init_token(
      VNUMBER,
      start_pos,
      lexer->current_position,
      init_token_value_with_number(number));
}
}

static token_T *get_comment_token(lexer_T *lexer)
{
  token_pos_T start_pos = lexer->current_position;
  advance_lexer(lexer);
  advance_lexer(lexer);
  skip_whitespace(lexer);
  char *comment_buffer = calloc(10000, sizeof(char));
  size_t current_index = 0;
  while (lexer->current_character != '\n' || finished(lexer))
  {
    comment_buffer[current_index] = lexer->current_character;
    advance_lexer(lexer);
    current_index++;
  }
  return init_token(
      COMMENT,
      start_pos,
      lexer->current_position,
      init_token_value_with_string(comment_buffer));
}

static token_T *get_string_token(lexer_T *lexer)
{
  token_pos_T start_pos = lexer->current_position;
  advance_lexer(lexer);
  char *string_buffer = calloc(100000, sizeof(char));
  size_t current_index = 0;
  while (lexer->current_character != '`')
  {
    if (finished(lexer))
    {
      log_error("string not closed with '`': %s:%d:%d(%d)", lexer->filename,
                lexer->current_position.line, lexer->current_position.column, lexer->current_position.index);
      exit(1);
    }
    string_buffer[current_index] = lexer->current_character;
    advance_lexer(lexer);
    current_index++;
  }
  advance_lexer(lexer);
  return init_token(
      VSTRING,
      start_pos,
      lexer->current_position,
      init_token_value_with_string(string_buffer));
}

token_T *next_token(lexer_T *lexer)
{
  if (finished(lexer))
    return init_token(
        _EOF,
        lexer->current_position,
        advance_token_position(lexer->current_position),
        init_token_value_with_character('\0'));
  if (isspace(lexer->current_character))
    skip_whitespace(lexer);
  if (lexer->current_character == '-' && lexer->next_character == '-')
    return get_comment_token(lexer);
  if (letter(lexer->current_character))
    return get_name_token(lexer);
  if (isdigit(lexer->current_character))
    return get_number_token(lexer);
  if (lexer->current_character == '`')
    return get_string_token(lexer);
  if (punctuator(lexer->current_character))
  {
    char punctuator = lexer->current_character;
    token_pos_T start_pos = lexer->current_position;
    advance_lexer(lexer);
    return init_token(
        PUNCTUATOR,
        start_pos,
        lexer->current_position,
        init_token_value_with_character(punctuator));
  }
  token_T *error_token = init_token(
      ERROR,
      lexer->current_position,
      advance_token_position(lexer->current_position),
      init_token_value_with_character(lexer->current_character));
  advance_lexer(lexer);
  return error_token;
}

static bool letter(char character)
{
  return (character >= 'a' && character <= 'z') ||
         (character >= 'A' && character <= 'Z') ||
         character == '_';
}

static bool punctuator(char character)
{
  return (character == ';' || character == '>' || character == '<' ||
          character == '=' || character == '.' || character == ',' ||
          character == '{' || character == '}' || character == '(' ||
          character == ')');
}

static bool finished(lexer_T *lexer)
{
  return lexer->current_character == '\0';
}