#include "../include/token/token.h"

token_T *init_token(
    token_type_T type,
    token_pos_T *start_pos, token_pos_T *end_pos,
    token_value_T *value)
{
  token_T *token = calloc(1, sizeof(struct TOKEN_STRUCT));
  token->type = type;
  token->start_pos = start_pos;
  token->end_pos = end_pos;
  token->value = value;
  return token;
}

char *dump_token(token_T *token)
{
  return format("tok(t:%d;sp:%s,ep:%s,v:%s)",
                token->type,
                dump_token_position(token->start_pos),
                dump_token_position(token->end_pos),
                dump_token_value(token->value, token->type));
}