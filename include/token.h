#include <stdlib.h>
#include <string.h>

#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType
{
	TOKEN_WHITESPACE,
	TOKEN_ID,
	TOKEN_RESERVED_WORD, // TODO temporary
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
	TOKEN_NUM,
	ERR_TOKEN_NOT_FOUND,
	TOKEN_LEXERR,
	TOKEN_ATTRIBUTE_INT,
	TOKEN_ATTRIBUTE_REAL,
	TOKEN_ATTRIBUTE_LONGREAL,
	TOKEN_NO_ATTRIBUTE
} TokenType;

typedef struct Token
{
	TokenType type;
	TokenType attribute;
} Token;

#define RESERVED_WORD_DELIM "\t"

typedef struct ReservedWord
{
	char *name;
	int type;
	int attribute;
	struct ReservedWord *next;
} ReservedWord;

Token *get_next_token(char *line, ReservedWord *reserved_words);
ReservedWord *tokenize_reserved_word_str (char *line);

#endif