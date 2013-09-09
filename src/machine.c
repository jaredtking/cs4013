#include "machine.h"

MachineResult machine_omega(char *in)
{
	/*
	This machine is the super machine that ties all
	of the other machines together. If no match is made
	then an unrecognized LEXERR token will be returned.
	There is an ordering to the machines according to:
	  i) efficiency rule
	  ii) tokenizing rule
	*/
	// TODO try all machines

	// no match
	MachineResult res;
	res.token = (Token *)malloc(sizeof(Token));
	res.token->type = TOKEN_LEXERR;
	res.token->attribute = ERR_TOKEN_NOT_FOUND;
	return res;
}

MachineResult machine_whitespace(char *in)
{
	char *f = in;
	int s = 1;
	MachineResult res;
	res.token = NULL;
	res.err = MACHINE_ERR_NONE;

	while (res.token == NULL && res.err == MACHINE_ERR_NONE)
	{
		switch (s)
		{
		case 0:
			f--;
			res.f = f;
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1:
			if (is_whitespace(*f))
				s++;
			else
				s--;
		break;
		case 2:
			if (is_whitespace(*f))
				s++;
		break;
		case 3:
			res.f = f;
			res.token = (Token *)malloc(sizeof(Token));
			res.token->type = TOKEN_WHITESPACE;
			res.token->attribute = TOKEN_NO_ATTRIBUTE;
		break;
		}

		f++;
	}

	return res;
}

MachineResult machine_idres(char *in, ReservedWord *reserved_words)
{
	char *f = in;
	int s = 1;
	MachineResult res;
	res.token = NULL;
	res.err = MACHINE_ERR_NONE;

	while (res.token == NULL && res.err == MACHINE_ERR_NONE)
	{
		switch (s)
		{
		case 0:
			f--;
			res.f = f;
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1:
			if (is_alpha(*f))
				s++;
			else
				s--;
		break;
		case 2:
			if (!is_alpha_numeric(*f))
				s++;
		break;
		case 3:
			// check if reserved word
			// TODO

			// check if too long
			// TODO

			res.f = f;
			res.token = (Token *)malloc(sizeof(Token));
			res.token->type = TOKEN_ID;
			res.token->attribute = TOKEN_NO_ATTRIBUTE;
		break;
		}

		f++;
	}

	return res;		
}

MachineResult machine_catchall(char *in)
{
	char *f = in;
	int s = 1;
	MachineResult res;
	res.token = NULL;
	res.err = MACHINE_ERR_NONE;

	// TODO

	return res;
}

MachineResult machine_int(char *in)
{
	char *f = in;
	int s = 1;
	MachineResult res;
	res.token = NULL;
	res.err = MACHINE_ERR_NONE;

	// TODO

	return res;
}

MachineResult machine_real(char *in)
{
	char *f = in;
	int s = 1;
	MachineResult res;
	res.token = NULL;
	res.err = MACHINE_ERR_NONE;

	// TODO

	return res;
}

MachineResult machine_longreal(char *in)
{
	char *f = in;
	int s = 1;
	MachineResult res;
	res.token = NULL;
	res.err = MACHINE_ERR_NONE;

	// TODO

	return res;
}

/* Useful checks */

int is_alpha(char c)
{
	return (c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
}

int is_alpha_numeric(char c)
{
	return is_alpha(c) || ( c >= '0' && c <= '9' );
}

int is_whitespace(char c)
{
	return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}