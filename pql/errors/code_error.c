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

#include "../include/errors/code_error.h"

code_error_T *init_code_error(char* filename, char* source, char* message,
                              token_pos_T start_pos, token_pos_T end_pos) {
  code_error_T *e = calloc(1, sizeof(struct CODE_ERROR_STRUCT));
  e->filename = filename;
  e->source = source;
  e->message = message;
  e->start_pos = start_pos;
  e->end_pos = end_pos;
  return e;
}

void print_code_error(code_error_T* error) {
  printf("✘ found error at %s at %zu:%zu[%zu] => %zu:%zu[%zu]:\n", error->filename,
         error->start_pos.line, error->start_pos.column, error->start_pos.index,
         error->end_pos.line, error->end_pos.column, error->end_pos.index);
  printf(" ➤ %s:\n", error->message);
//  char** code_lines = calloc(10000, sizeof(char*));
//  size_t current_line = 0;
//
//  code_lines[current_line] = strtok(error->source, "\n");
//  while (code_lines[current_line] != NULL)
//  {
//    code_lines[current_line] = strtok(error->source, "\n");
//  }
//  for (size_t i = error->start_pos.line; i <= error->end_pos.line; i++) {
//    printf("%s\n", code_lines[i - 1]);
//  }
}

void print_code_error_and_exit(code_error_T* error) {
  print_code_error(error);
  exit(1);
}

static char** split_code(char* code, char delimiter)
{
  char** result    = 0;
  size_t count     = 0;
  char* tmp        = code;
  char* last_comma = 0;
  char delim[2];
  delim[0] = delimiter;
  delim[1] = 0;

  /* Count how many elements will be extracted. */
  while (*tmp)
  {
    if (code == *tmp)
    {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

  /* Add space for trailing token. */
  count += last_comma < (code + strlen(code) - 1);

  /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
  count++;

  result = malloc(sizeof(char*) * count);

  if (result)
  {
    size_t idx  = 0;
    char* token = strtok(code, delim);

    while (token)
    {
      assert(idx < count);
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }
    assert(idx == count - 1);
    *(result + idx) = 0;
  }

  return result;
}
