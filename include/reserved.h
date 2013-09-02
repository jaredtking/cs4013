#include <stdlib.h>
#include <stdio.h>

#ifndef RESERVE_H
#define RESERVE_H

typedef struct ReservedWord
{
	char *name;
	int type;
	int attribute;
} ReservedWord;

typedef struct ReservedWordList
{
	ReservedWord word;
	struct ReservedWordList *next;
} ReservedWordList;

ReservedWordList tokenize_reserved_words (const char *lines[]);

#endif