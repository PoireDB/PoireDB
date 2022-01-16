#include "../include/parser/parser.h"
#include "../include/tau.h"
#include "../include/util/string.h"

TAU_MAIN()

TEST(foo, test_DBSTMT) {
  char *fish_text = "Lorem ipsum dolor sit amet, consectetuer "
                    "adipiscing elit. Aenean commodo ligula eget dolor";
  lexer_T *l = init_lexer("<testdata>", format("db `%s`;", fish_text));
  parser_T *p = init_parser(l);
  query_AST_T *AST = parser_parse(p);

  CHECK(strcmp(AST->database_name, fish_text) == 0);

  free(AST);
  free(l);
  free(p);
}

TEST(foo, test_DELETESTMT) {
  lexer_T *l = init_lexer("<testdata>", "db ``;\n"
                                        "delete account;");
  parser_T *p = init_parser(l);
  query_AST_T *AST = parser_parse(p);

  CHECK(AST->top_compound[0]->type == DELETE);
  CHECK(strcmp(AST->top_compound[0]->statement.delete_stmt->table_name,
               "account") == 0);

  free(AST);
  free(l);
  free(p);
}

TEST(foo, test_EMPTYTABLESTMT) {
  lexer_T *l = init_lexer("<testdata>", "db ``;\n"
                                        "table account {};");
  parser_T *p = init_parser(l);
  query_AST_T *AST = parser_parse(p);

  CHECK(AST->top_compound[0]->type == TABLE);
  CHECK(strcmp(AST->top_compound[0]->statement.table_stmt->table_name,
               "account") == 0);

  free(AST);
  free(l);
  free(p);
}