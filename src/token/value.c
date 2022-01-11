/** 
 *  MIT License
 *  Copyright (c) 2022 PoireDB authors and contributors
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

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