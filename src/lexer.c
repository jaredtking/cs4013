#include <stdio.h>
#include "reserved.h"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf ("usage: %s reserved_words_file source_file output_dir\n", argv[0]);
		exit(1);
	}

	printf("-- Lexer begin --\n");

	FILE *f;
	char line[200];

	/* tokenize reserved words file */

	ReservedWord *head, *curr;
	head = NULL;

	f = fopen (argv[1], "r");

	if (f == NULL)
	{
		fprintf (stderr, "Can't open reserved words file!\n");
		exit(1);
	}

	printf("Parsing reserved words file.. ");

	while (fgets (line, 200, f) != NULL)
	{
		curr = tokenize_reserved_word_str (line);
		curr->next = head;
		head = curr;
	}

	curr = head;
	fclose(f);

	printf("ok\n");

	/* tokenize input source file */

	f = fopen (argv[2], "r");

	if (f == NULL)
	{
		fprintf (stderr, "Can't open source file!\n");
		exit(1);
	}

	char *output_dir;
	strcpy (output_dir, argv[3]);

	char *listing_filename = malloc(strlen(output_dir) + 9);
	sprintf(listing_filename, "%s/listing", output_dir);
	FILE *lf = fopen (listing_filename, "w");

	if (lf == NULL)
	{
		fprintf (stderr, "Can't create listing file at %s!\n", listing_filename);
		exit(1);
	}

	printf("Parsing source file.. ");

	int i = 1;

	while (fgets (line, 200, lf) != NULL)
	{
		printf("%s", line);
		// output line to listing file
		//fprintf (lf, "%-10d%s\n", i, line);

		// tokenize line

			// output errors to listing file

		i++;
	}

	fclose(lf);

	printf("ok\n");

	return(0);
}