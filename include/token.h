#include <stdlib.h>
#include <string.h>

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
	TOKEN_NUM,
	TOKEN_RELOP,
	TOKEN_MULOP,
	TOKEN_ADDOP,
	TOKEN_ASSIGNOP,
	TOKEN_SEMICOLON,
	TOKEN_COLON,
	TOKEN_COMMA,
	TOKEN_PERIOD,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LBRACKET,
	TOKEN_RBRACKET,
	ERR_TOKEN_NOT_FOUND,
	TOKEN_LEXERR
} TokenType;

typedef struct Token
{
	TokenType type;
	TokenType attribute;
} Token;

#define ATTRIBUTE_INT 999
#define ATTRIBUTE_REAL 998
#define ATTRIBUTE_LONGREAL 997
#define ATTRIBUTE_GE 996
#define ATTRIBUTE_LE 995
#define ATTRIBUTE_NE 994

#define RESERVED_WORD_DELIM "\t"

typedef struct ReservedWord
{
	char *name;
	TokenType type;
	int attribute;
	struct ReservedWord *next;
} ReservedWord;

Token *get_next_token (char *line, ReservedWord *reserved_words);
ReservedWord *tokenize_reserved_word_str (char *line);
TokenType int_to_token_type (int id);

#endif