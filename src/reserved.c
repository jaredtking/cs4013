#include "reserved.h"

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
	word->type = strtol(pieces[1], (char **)NULL, 10);
	word->attribute = strtol(pieces[2], (char **)NULL, 10);
	word->next = NULL;

	return word;
}