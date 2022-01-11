#include "../include/token/value.h"

token_value_T *init_token_value_with_string(char *string)
{
  token_value_T *value = calloc(1, sizeof(union TOKEN_VALUE_UNION));
  value->string = string;
  return value;
}

token_value_T *init_token_value_with_character(char character)
{
  token_value_T *value = calloc(1, sizeof(union TOKEN_VALUE_UNION));
  value->character = character;
  return value;
}

token_value_T *init_token_value_with_number(double number)
{
  token_value_T *value = calloc(1, sizeof(union TOKEN_VALUE_UNION));
  value->number = number;
  return value;
}

token_value_T *init_token_value_with_boolean(bool boolean)
{
  token_value_T *value = calloc(1, sizeof(union TOKEN_VALUE_UNION));
  value->boolean = boolean;
  return value;
}

char *dump_token_value(token_value_T *value, token_type_T type)
{
  switch (type)
  {
  case VNUMBER:
    return format("%f", value->number);
  case PUNCTUATOR:
  case ERROR:
  case VCHARACTER:
    return format("%c", value->character);
  case VBOOLEAN:
    return value->boolean ? "true" : "false";
  case EOF:
    return "(eof)";
  default:
    return "(?)";
  }
}