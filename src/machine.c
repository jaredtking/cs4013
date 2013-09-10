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
			f--;
			res.f = f;

			// check if reserved word
			char *word = (char *)malloc(f - in + 1);
			strncpy(word, in, f - in);
			word[f - in] = '\0';

			ReservedWord *rw = is_reserved_word(word, reserved_words);
			if (rw != NULL)
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = rw->type;
				res.token->attribute = rw->attribute;
			}
			else
			{
				// make sure id is not too long
				if (strlen(word) > MAX_ID_LEN)
					res.err = MACHINE_ERR_ID_TOO_LONG;
				else
				{
					res.token = (Token *)malloc(sizeof(Token));
					res.token->type = TOKEN_ID;
					res.token->attribute = TOKEN_NO_ATTRIBUTE;
				}
			}
		break;
		}

		f++;
	}

	return res;		
}

MachineResult machine_catchall(char *in)
{
	//char *f = in;
	//int s = 1;
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
			if (is_numeric(*f))
				s++;
			else
				s--;
		break;
		case 2:
			if (!is_numeric(*f))
				s++;
		break;
		case 3:
			f--;

			// make sure int is not too long
			if (f - in > MAX_INT_LEN)
				res.err = MACHINE_ERR_INT_TOO_LONG;
			else
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_NUM;
				res.token->attribute = TOKEN_ATTRIBUTE_INT;
			}
		break;
		}

		f++;
	}

	return res;
}

MachineResult machine_real(char *in)
{
	char *f = in;
	char *dot;
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
			if (is_numeric(*f))
				s++;
			else
				s--;
		break;
		case 2:
			if (!is_numeric(*f))
			{
				if (*f == '.')
				{
					// make sure the int is not too long
					if (f - in > MAX_REAL_XX_LEN)
						res.err = MACHINE_ERR_REAL_XX_TOO_LONG;
					else
						s++;

					dot = f;
				}
				else
					s = 0;
			}
		break;
		case 3:
			if (!is_numeric(*f))
				s++;
		break;
		case 4:
			f--;

			// make sure fraction is not too long
			if (f - dot - 1 > MAX_REAL_YY_LEN)
				res.err = MACHINE_ERR_REAL_YY_TOO_LONG;
			else
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_NUM;
				res.token->attribute = TOKEN_ATTRIBUTE_REAL;
			}
		break;
		}

		f++;
	}

	return res;
}

MachineResult machine_longreal(char *in)
{
	char *f = in;
	char *dot;
	char *sign;
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
			if (is_numeric(*f))
				s++;
			else
				s--;
		break;
		case 2:
			if (!is_numeric(*f))
			{
				if (*f == '.')
				{
					if (f - in > MAX_REAL_XX_LEN)
						res.err = MACHINE_ERR_REAL_XX_TOO_LONG;
					else
						s++;

					dot = f;
				}
				else
					s = 0;
			}
		break;
		case 3:
			if (!is_numeric(*f))
			{
				if (*f == 'E')
				{
					// make sure fraction is not too long
					if (f - dot - 1 > MAX_REAL_YY_LEN)
						res.err = MACHINE_ERR_REAL_YY_TOO_LONG;
					else
						s++;
				}
				else
					s = 0;
			}
		break;
		case 4:
			if (is_plus_or_minus(*f))
				s++;
			else if (is_numeric(*f))
			{
				s = 7;
				sign = f;
			}
			else
				s = 0;
		break;
		case 5:
			if (is_numeric(*f))
			{
				s++;
				sign = f;
			}
			else
				s = 0;
		break;
		case 6:
			if (!is_numeric(*f))
				s++;
		break;
		case 7:
			f--;

			// make sure exponent is not too long
			if (f - sign > MAX_REAL_ZZ_LEN)
				res.err = MACHINE_ERR_REAL_ZZ_TOO_LONG;
			else
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_NUM;
				res.token->attribute = TOKEN_ATTRIBUTE_LONGREAL;
			}
		break;
		}

		f++;
	}

	return res;
}

/* Useful checks */

int is_alpha(char c)
{
	return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
}

int is_alpha_numeric(char c)
{
	return is_alpha (c) || is_numeric (c);
}

int is_numeric(char c)
{
	return c >= '0' && c <= '9';
}

int is_plus_or_minus(char c)
{
	return c == '+' || c == '-';
}

ReservedWord *is_reserved_word(char *word, ReservedWord *reserved_words)
{
	ReservedWord *curr = reserved_words;
	while (curr != NULL)
	{
		if (strcmp(word, curr->name) == 0)
			return curr;

		curr = curr->next;
	}

	return NULL;
}

int is_whitespace(char c)
{
	return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}