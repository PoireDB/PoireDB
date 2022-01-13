cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(pql LANGUAGES C)
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