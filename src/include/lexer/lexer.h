#ifndef _LEXER_H_
#define _LEXER_H_

#include "../token/token.h"
#include "../token/position.h"
#include <string.h>

typedef struct LEXER_STRUCT
{
  char *filename;
  char *input;
  size_t input_length;
  token_pos_T *current_position;
  char current_character;
  char next_character;
} lexer_T;

lexer_T *init_lexer(char *filename, char *input);

/**
 * @brief   Update current_character and next_character members
 * @param   lexer   lexer struct 
 */
static void update_lexer(lexer_T *lexer);

static void advance_lexer(lexer_T *lexer);

static void skip_whitespace(lexer_T *lexer);

token_T *next_token(lexer_T *lexer);

#endif /* _LEXER_H_ */