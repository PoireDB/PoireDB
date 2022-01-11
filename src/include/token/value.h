#ifndef _TOKEN_VALUE_H_
#define _TOKEN_VALUE_H_

#include "type.h"
#include "../util/string.h"
#include <stdbool.h>

typedef union TOKEN_VALUE_UNION
{
  char *string;
  char character;
  double number;
  bool boolean;
} token_value_T;

token_value_T *init_token_value_with_string(char *string);
token_value_T *init_token_value_with_character(char character);
token_value_T *init_token_value_with_number(double number);
token_value_T *init_token_value_with_boolean(bool boolean);
char *dump_token_value(token_value_T *value, token_type_T type);

#endif /* _TOKEN_VALUE_H_ */