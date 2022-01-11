#ifndef _TOKEN_TYPE_H_
#define _TOKEN_TYPE_H_

typedef enum TOKEN_TYPE_ENUM
{
  VSTRING,
  VCHARACTER,
  VNUMBER,
  VBOOLEAN,
  KEYWORD,
  PUNCTUATOR,
  EOF,
  ERROR,
} token_type_T;

#endif /* _TOKEN_TYPE_H_ */