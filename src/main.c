#include "include/lexer/lexer.h"

int main()
{
  lexer_T *l = init_lexer("main.c", "int main() {}");
}