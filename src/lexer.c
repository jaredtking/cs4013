#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
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

	char *output_dir = malloc(strlen(argv[3]));
	strcpy (output_dir, argv[3]);

	// ensure the output directory is present  
	struct stat fileStat;
	if (stat(output_dir, &fileStat) < 0)
	{
		mode_t process_mask = umask(0);
		mkdir(output_dir, S_IRWXU | S_IRWXG | S_IRWXO);
		umask(process_mask);

		if (stat(output_dir, &fileStat) < 0)
		{
			fprintf (stderr, "Output directory does not exist!\n");
			exit(1);
		}
	}

	// strip trailing "/" from output dir
	if (strcmp (&output_dir[strlen(output_dir)-1], "\\") == 0)
		output_dir[strlen(output_dir)-1] = 0;

	// open listing file for writing
	char *listing_filename = malloc(strlen(output_dir) + 9);
	sprintf(listing_filename, "%s/listing", output_dir);
	FILE *lf = fopen (listing_filename, "w");

	if (lf == NULL)
	{
		fprintf (stderr, "Can't create listing file at %s!\n", listing_filename);
		exit(1);
	}

	// open tokens file for writing
	char *tokens_filename = malloc(strlen(output_dir) + 9);
	sprintf(tokens_filename, "%s/tokens", output_dir);
	FILE *tf = fopen (tokens_filename, "w");

	if (tf == NULL)
	{
		fprintf (stderr, "Can't create tokens file at %s!\n", tokens_filename);
		exit(1);
	}

	printf("Parsing source file.. ");

	int i = 1;

//	Token *t = getNextToken();
	while (fgets (line, 72, f) != NULL)
	{
		// output line to listing file
		fprintf (lf, "%-10d%s", i, line);

		// tokenize line
//		t = getNextToken(line);

			// write token to tokens file

			// output errors to listing file

		i++;
	}

	fclose(lf);

	printf("ok\n");

	return(0);
}