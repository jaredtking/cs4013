#include "machine.h"

void machine_omega()
{

}

MachineResult machine_whitespace(char *in)
{
	char *f = in;
	int s = 1;
	MachineResult res;
	res.token = NULL;
	res.err = 0;

	while (res.token == NULL && res.err == 0)
	{
		switch (s)
		{
		case 0:
			f--;
			res.f = f;
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
			res.token->attribute = 0;
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