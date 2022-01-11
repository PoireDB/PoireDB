#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "type.h"
#include "value.h"
#include "position.h"
#include "../util/string.h"

typedef struct TOKEN_STRUCT
{
  token_type_T type;
  token_pos_T *start_pos;
  token_pos_T *end_pos;
  token_value_T *value;
} token_T;

token_T *init_token(
    token_type_T type, token_pos_T *start_pos, token_pos_T *end_pos, token_value_T *value);
char *dump_token(token_T *token);

#endif /* _TOKEN_H_ */