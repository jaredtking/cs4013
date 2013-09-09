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
			if (*f == '\n' || *f == '\r' || *f == '\t' || *f == ' ')
				s++;
			else
				s--;
		break;
		case 2:
			if (!(*f == '\n' || *f == '\r' || *f == '\t' || *f == ' '))
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

void machine_idres()
{

}

void machine_catchall()
{

}

void machine_int()
{

}

void machine_real()
{

}

void machine_longreal()
{

}