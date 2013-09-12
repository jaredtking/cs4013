#include "token.h"

Token *get_next_token(char *line, ReservedWord *reserved_words)
{
	static b = 0;
	static f = 0;
	
	// TODO
}

ReservedWord *tokenize_reserved_word_str (char *in)
{
	ReservedWord *word = (ReservedWord *)malloc(sizeof(ReservedWord));

	char line[200];
	strcpy(line, in);

    // tokenize the line by tabs
    char pieces[3][200];
    char *piece;
    int i = -1;

	piece = strtok (line, RESERVED_WORD_DELIM);
	while (piece != NULL && i++ < 3)
	{
		strcpy (pieces[i], piece);
	    piece = strtok (NULL, RESERVED_WORD_DELIM);
	}

	word->name = malloc(201);
	strcpy(word->name, pieces[0]);
	word->type = int_to_token_type(strtol(pieces[1], (char **)NULL, 10));
	word->attribute = strtol(pieces[2], (char **)NULL, 10);
	word->next = NULL;

	return word;
}

TokenType int_to_token_type (int id)
{
	if (id == 1000)
		return TOKEN_PROGRAM;
	else if (id == 1001)
		return TOKEN_VAR;
	else if (id == 1002)
		return TOKEN_ARRAY;
	else if (id == 1003)
		return TOKEN_OF;
	else if (id == 1004)
		return TOKEN_INTEGER;
	else if (id == 1005)
		return TOKEN_REAL;
	else if (id == 1006)
		return TOKEN_PROCEDURE;
	else if (id == 1007)
		return TOKEN_BEGIN;
	else if (id == 1008)
		return TOKEN_END;
	else if (id == 1009)
		return TOKEN_IF;
	else if (id == 1010)
		return TOKEN_THEN;
	else if (id == 1011)
		return TOKEN_ELSE;
	else if (id == 1012)
		return TOKEN_WHILE;
	else if (id == 1013)
		return TOKEN_DO;
	else if (id == 1014)
		return TOKEN_NOT;
	else if (id == 1015)
		return TOKEN_OR;
	else if (id == 1016)
		return TOKEN_DIV;
	else if (id == 1017)
		return TOKEN_MOD;
	else if (id == 1018)
		return TOKEN_AND;
	else
		return ERR_TOKEN_NOT_FOUND;
}