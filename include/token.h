#include <stdlib.h>
#include <string.h>
#include "reserved.h"

#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType
{
	TOKEN_WHITESPACE,
	TOKEN_ID,
	TOKEN_PROGRAM,
	TOKEN_VAR,
	TOKEN_ARRAY,
	TOKEN_OF,
	TOKEN_INTEGER,
	TOKEN_REAL,
	TOKEN_PROCEDURE,
	TOKEN_BEGIN,
	TOKEN_END,
	TOKEN_IF,
	TOKEN_THEN,
	TOKEN_ELSE,
	TOKEN_WHILE,
	TOKEN_DO,
	TOKEN_NOT,
	TOKEN_OR,
	TOKEN_DIV,
	TOKEN_MOD,
	TOKEN_AND,
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