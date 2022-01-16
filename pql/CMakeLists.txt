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
add_test(LexerTest pql_lexer_test)