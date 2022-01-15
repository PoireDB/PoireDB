#include "../include/acutest.h"
#include "../include/lexer/lexer.h"

void test_EOF(void) {
  lexer_T *l = init_lexer("<testdata>", "");
  token_T *t = next_token(l);
  TEST_CHECK(t->type == _EOF);
  free(t);
  free(l);
}

void test_identifier(void) {
  lexer_T *l = init_lexer(
      "<testdata>", "_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
  token_T *t = next_token(l);
  TEST_CHECK(t->type == IDENTIFIER);
  TEST_CHECK(strcmp(t->value->string,
                    "_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") ==
             0);
  free(t);
  free(l);
}

void test_punctuator(void) {
  char *punctuators = ";><=.,{}()";
  lexer_T *l = init_lexer("<testdata>", punctuators);
  token_T *t = next_token(l);
  size_t current_punctuator_index = 0;

  while (t->type != _EOF) {
    TEST_CHECK(t->type == PUNCTUATOR);
    TEST_CHECK(t->value->character == punctuators[current_punctuator_index]);
    current_punctuator_index++;
    t = next_token(l);
  }

  free(t);
  free(l);
}

void test_boolean(void) {
  lexer_T *l = init_lexer("<testdata>", "true false");

  token_T *MustBeTrue = next_token(l);
  token_T *MustBeFalse = next_token(l);

  TEST_CHECK(MustBeTrue->type == VBOOLEAN);
  TEST_CHECK(MustBeFalse->type == VBOOLEAN);

  TEST_CHECK(MustBeTrue->value->boolean);
  TEST_CHECK(!MustBeFalse->value->boolean);

  free(MustBeTrue);
  free(MustBeFalse);

  free(l);
}

void test_number(void) {
  char *input[] = {
      "1234567890",
      "1234567890.0123456789",
  };
  double excpt_output[] = {
      1234567890,
      1234567890.0123456789,
  };
  for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++) {
    lexer_T *l = init_lexer("<testdata>", input[i]);
    token_T *t = next_token(l);
    TEST_CHECK(t->type == VNUMBER);
    TEST_CHECK(t->value->number == excpt_output[i]);
    free(t);
    free(l);
  }
}

TEST_LIST = {{"eof", test_EOF},
             {"identifier", test_identifier},
             {"punctuator", test_punctuator},
             {"boolean", test_boolean},
             {"number", test_number},
             {NULL, NULL}};