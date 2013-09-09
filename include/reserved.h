#include <stdlib.h>
#include <string.h>

#ifndef RESERVE_H
#define RESERVE_H

#define RESERVED_WORD_DELIM "\t"

typedef struct ReservedWord
{
	char *name;
	int type;
	int attribute;
	struct ReservedWord *next;
} ReservedWord;

ReservedWord *tokenize_reserved_word_str (char *line);

#endif