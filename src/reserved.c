#include "reserved.h"

ReservedWordList tokenize_reserved_words (const char *lines[])
{
	ReservedWordList head;

    int i;
    for(i = 0; lines[i] != NULL; i++)
    {
        printf("[%d] .. %s\n", (i+1), lines[i]);
    }

	return head;
}