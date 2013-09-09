#include "machine.h"

void machine_omega()
{

}

void machine_whitespace(char *in)
{
	char *f = in;
	char *b;
	int s = 1;
	MachineResult *res;

	while (res == NULL)
	{
		switch (s)
		{
		case 0:
			f--;
			res = (MachineResult *)malloc(sizeof(MachineResult));
			res->f = f;
			res->token = NULL;
		break;
		case 1:
			if (*f == '\n' || *f == '\r' || *f == '\t' || *f == ' ')
				s++;
			else
				s--;
		break;
		case 2:
			if !(*f == '\n' || *f == '\r' || *f == '\t' || *f == ' ')
				s++;
		break;
		case 3:
			res = (MachineResult *)malloc(sizeof(MachineResult));
			res->f = f;
			res->token = (Token *)malloc(sizeof(Token));
			res->token->type = 0;
			res->token->attribute = 0;
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