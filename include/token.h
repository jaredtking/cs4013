#include <stdlib.h>
#include <string.h>
#include "reserved.h"

#ifndef TOKEN_H
#define TOKEN_H

enum TokenType
{
	WHITESPACE,
	NOTFOUND
}

typedef union Token
{
	enum TokenType type;
	int attribute;
} Token;

Token *get_next_token(char *line, ReservedWord *reserved_words);

#endif