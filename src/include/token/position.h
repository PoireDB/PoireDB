#ifndef _TOKEN_POSITION_H_
#define _TOKEN_POSITION_H_

#include "../util/string.h"
#include <stdlib.h>

typedef struct TOKEN_POSITION_STRUCT
{
  size_t index;
  size_t line, column;
} token_pos_T;

token_pos_T *init_token_position(size_t index, size_t line, size_t column);
token_pos_T *advance_token_position(token_pos_T *old_position);
char *dump_token_position(token_pos_T *position);

#endif /* _TOKEN_POSITION_H_ */