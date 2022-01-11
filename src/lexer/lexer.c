/**
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 *  under the License.    
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