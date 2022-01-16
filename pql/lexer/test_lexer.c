#include "../include/lexer/lexer.h"
#include "../include/tau.h"

TAU_MAIN() // sets up Tau (+ main function)

TEST(foo, test_EOF) {
  lexer_T *l = init_lexer("<testdata>", "");
  token_T *t = next_token(l);
  CHECK(t->type == _EOF);
  free(t);
  free(l);
}

TEST(foo, test_identifier) {
  lexer_T *l = init_lexer(
      "<testdata>", "_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
  token_T *t = next_token(l);
  CHECK(t->type == IDENTIFIER);
  CHECK(strcmp(t->value->string,
               "_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == 0);
  free(t);
  free(l);
}

TEST(foo, test_punctuators) {
  char *punctuators = ";><=.,{}()";
  lexer_T *l = init_lexer("<testdata>", punctuators);
  token_T *t = next_token(l);
  size_t current_punctuator_index = 0;

  while (t->type != _EOF) {
    CHECK(t->type == PUNCTUATOR);
    CHECK(t->value->character == punctuators[current_punctuator_index]);
    current_punctuator_index++;
    t = next_token(l);
  }

  free(t);
  free(l);
}

TEST(foo, test_boolean) {
  lexer_T *l = init_lexer("<testdata>", "true false");

  token_T *MustBeTrue = next_token(l);
  token_T *MustBeFalse = next_token(l);

  CHECK(MustBeTrue->type == VBOOLEAN);
  CHECK(MustBeFalse->type == VBOOLEAN);

  CHECK(MustBeTrue->value->boolean);
  CHECK(!MustBeFalse->value->boolean);

  free(MustBeTrue);
  free(MustBeFalse);

  free(l);
}

TEST(foo, test_number) {
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
    CHECK(t->type == VNUMBER);
    CHECK(t->value->number == excpt_output[i]);
    free(t);
    free(l);
  }
}