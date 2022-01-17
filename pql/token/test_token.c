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

#include "../include/tau.h"
#include "../include/token/token.h"
#include <stdbool.h>

TAU_MAIN()

TEST(foo, test_TokenPositionDump) {
  token_pos_T p = init_token_position(1, 2, 3);
  CHECK(strcmp(dump_token_position(p), "pos(index=1, line=2, column=3)") == 0);
}

TEST(foo, test_TokenValueDump) {
  token_value_T *btrue = init_token_value_with_boolean(true);
  token_value_T *bfalse = init_token_value_with_boolean(false);

  CHECK(strcmp(dump_token_value(btrue, VBOOLEAN), "true") == 0);
  CHECK(strcmp(dump_token_value(bfalse, VBOOLEAN), "false") == 0);

  token_value_T *eof = init_token_value_with_character('\0');
  CHECK(strcmp(dump_token_value(eof, _EOF), "(eof)") == 0);

  token_value_T *chr = init_token_value_with_character('z');
  CHECK(strcmp(dump_token_value(chr, PUNCTUATOR), "z") == 0);
  CHECK(strcmp(dump_token_value(chr, ERROR), "z") == 0);
  CHECK(strcmp(dump_token_value(chr, VCHARACTER), "z") == 0);

  char *str_str = "hello";
  token_value_T *str = init_token_value_with_string("hello");

  CHECK(strcmp(dump_token_value(str, IDENTIFIER), str_str) == 0);
  CHECK(strcmp(dump_token_value(str, KEYWORD), str_str) == 0);
  CHECK(strcmp(dump_token_value(str, VSTRING), str_str) == 0);
  CHECK(strcmp(dump_token_value(str, COMMENT), str_str) == 0);
}