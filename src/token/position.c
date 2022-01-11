#include "../include/token/position.h"

token_pos_T *init_token_position(size_t index, size_t line, size_t column)
{
  token_pos_T *pos = calloc(1, sizeof(struct TOKEN_POSITION_STRUCT));
  pos->index = index;
  pos->line = line;
  pos->column = column;
  return pos;
}

char *dump_token_position(token_pos_T *position)
{
  return format("pos(%d:(%d,%d))", position->index,
                position->line, position->column);
}

token_pos_T *advance_token_position(token_pos_T *old_position)
{
  return init_token_position(
      old_position->index + 1,
      old_position->line,
      old_position->column + 1);
}