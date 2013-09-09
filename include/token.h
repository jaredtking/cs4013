#include <stdlib.h>
#include <string.h>
#include "reserved.h"

#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType
{
	TOKEN_WHITESPACE,
	NOTFOUND,
	SOMETHINGELSE
} TokenType;

typedef struct Token
{
	TokenType type;
	int attribute;
} Token;

Token *get_next_token(char *line, ReservedWord *reserved_words);

#endif