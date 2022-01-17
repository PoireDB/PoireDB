# MIT License
# Copyright (c) 2022 PoireDB authors and contributors
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(pql)


add_executable(pql_lex 
  pql_lex.c
  lexer/lexer.c
  token/token.c
  token/position.c
  token/value.c
  util/string.c
  util/file.c
  log/log.c)
add_executable(pql 
  main.c)
add_executable(pql_parse 
  pql_parse.c
  AST/AST.c
  parser/parser.c
  lexer/lexer.c
  token/token.c
  token/position.c
  token/value.c
  util/string.c
  util/file.c
  log/log.c)
add_executable(pql_token_test
  token/test_token.c
  token/token.c
  token/position.c
  token/value.c
  util/string.c)
add_executable(pql_lexer_test
  lexer/test_lexer.c
  lexer/lexer.c
  token/token.c
  token/position.c
  token/value.c
  util/string.c
  log/log.c)
add_executable(pql_parser_test
  parser/test_parser.c
  parser/parser.c
  AST/AST.c
  lexer/lexer.c
  token/token.c
  token/position.c
  token/value.c
  util/string.c
  log/log.c)

enable_testing()
add_test(TokenTest pql_token_test)
add_test(LexerTest pql_lexer_test)
add_test(ParserTest pql_parser_test)