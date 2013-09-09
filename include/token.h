#include <stdlib.h>
#include <string.h>
#include "reserved.h"

#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType
{
	TOKEN_WHITESPACE,
	TOKEN_LEXERR,
	TOKEN_NO_ATTRIBUTE,
	ERR_TOKEN_NOT_FOUND
} TokenType;

typedef struct Token
{
	TokenType type;
	TokenType attribute;
} Token;

Token *get_next_token(char *line, ReservedWord *reserved_words);

#endif