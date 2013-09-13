#include "machine.h"

MachineResult machine_omega(char *in, ReservedWord *reserved_words)
{
	/*
	This machine is the super machine that ties all
	of the other machines together. If no match is made
	then an unrecognized LEXERR token will be returned.
	There is an ordering to the machines according to:
	  i) efficiency rule
	  ii) tokenizing rule
	*/

	char *f = in;
	MachineResult res;
	res.err = MACHINE_ERR_NO_MATCH;

	int i = 0;
	while (i < 7 && res.err == MACHINE_ERR_NO_MATCH)
	{
		switch (i)
		{
		case 0:
			res = machine_whitespace(f);
		break;
		case 1:
			res = machine_idres(f, reserved_words);
		break;
		case 2:
			res = machine_longreal(f);
		break;
		case 3:
			res = machine_real(f);
		break;
		case 4:
			res = machine_int(f);
		break;
		case 5:
			res = machine_relop(f);
		break;
		case 6:
			res = machine_catchall(f);
		break;
		}
	}

	// include lexeme in result
	res.lexeme = (char *)malloc(res.f - in + 1);
	strncpy(res.lexeme, in, res.f - in);
	res.lexeme[res.f - in] = '\0';

	// lexerr when no match is made
	if (res.err == MACHINE_ERR_NO_MATCH)
	{
		res.token = (Token *)malloc(sizeof(Token));
		res.token->type = TOKEN_LEXERR;
		res.token->attribute = 0;
	}

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
		case 0: // no match
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1: // start
			if (is_whitespace(*f))
				s++;
			else
				s--;
		break;
		case 2:
			if (!is_whitespace(*f))
			{
				f--;
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_WHITESPACE;
				res.token->attribute = 0;
			}
		break;
		}

		f++;
	}

	res.f = f;

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
		case 0: // no match
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1: // start
			if (is_alpha(*f))
				s++;
			else
				s--;
		break;
		case 2: // letter
			if (!is_alpha_numeric(*f))
			{
				// check if reserved word
				char *word = (char *)malloc(f - in + 1);
				strncpy(word, in, f - in);
				word[f - in] = '\0';

				f--;				

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
						res.token->attribute = 0;
					}
				}				
			}
		break;
		}

		f++;
	}

	res.f = f;

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
		case 0: // no match
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1: // start
			if (is_numeric(*f))
				s++;
			else
				s--;
		break;
		case 2:
			if (!is_numeric(*f))
			{
				// make sure int is not too long
				int len = f - in;
				if (len > MAX_INT_LEN)
					res.err = MACHINE_ERR_INT_TOO_LONG;
				// make sure there is not a leading zero
				else if (*in == '0' && len > 1)
					res.err = MACHINE_ERR_NUM_LEADING_ZERO;
				else
				{
					res.token = (Token *)malloc(sizeof(Token));
					res.token->type = TOKEN_NUM;
					res.token->attribute = ATTRIBUTE_INT;
				}

				f--;				
			}
		break;
		}

		f++;
	}

	res.f = f;

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
		case 0: // no match
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1: // start
			if (is_numeric(*f))
				s++;
			else
				s--;
		break;
		case 2: // digit
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
		case 3: // period
			if (!is_numeric(*f))
				s++;
		break;
		case 4:
			f--;

			// make sure fraction is not too long
			if (f - dot - 1 > MAX_REAL_YY_LEN)
				res.err = MACHINE_ERR_REAL_YY_TOO_LONG;
			// make sure there is not a leading zero
			else if (*in == '0')
				res.err = MACHINE_ERR_NUM_LEADING_ZERO;
			else
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_NUM;
				res.token->attribute = ATTRIBUTE_REAL;
			}

			f--;
		break;
		}

		f++;
	}

	res.f = f;

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
		case 0: // no match
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1: // start
			if (is_numeric(*f))
				s++;
			else
				s--;
		break;
		case 2: // digit
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
		case 3: // period
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
		case 4: // digit
			if (is_plus_or_minus(*f))
				s++;
			else if (is_numeric(*f))
			{
				s = 6;
				sign = f;
			}
			else
				s = 0;
		break;
		case 5: // sign
			if (is_numeric(*f))
			{
				s++;
				sign = f;
			}
			else
				s = 0;
		break;
		case 6: // digit
			if (!is_numeric(*f))
				s++;
		break;
		case 7:
			f--;

			// make sure exponent is not too long
			if (f - sign > MAX_REAL_ZZ_LEN)
				res.err = MACHINE_ERR_REAL_ZZ_TOO_LONG;
			// make sure there is not a leading zero
			else if (*in == '0')
				res.err = MACHINE_ERR_NUM_LEADING_ZERO;
			else
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_NUM;
				res.token->attribute = ATTRIBUTE_LONGREAL;
			}

			f--;
		break;
		}

		f++;
	}

	res.f = f;

	return res;
}

MachineResult machine_relop(char *in)
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
		case 0: // no match
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1: // start
			if (*f == '>')
				s = 2;
			else if (*f == '<')
				s = 3;
			else if (*f == '=')
				s = 4;
			else
				s--;
		break;
		case 2: // >
			if (*f == '=')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_RELOP;
				res.token->attribute = ATTRIBUTE_GE;
			}
			else
			{
				f--;
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_RELOP;
				res.token->attribute = *f;
			}
		break;
		case 3: // <
			if (*f == '=')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_RELOP;
				res.token->attribute = ATTRIBUTE_LE;				
			}
			else if (*f == '>')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_RELOP;
				res.token->attribute = ATTRIBUTE_NE;				
			}
			else
			{
				f--;
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_RELOP;
				res.token->attribute = *f;
			}
		break;
		case 4:
			f--;
			res.token = (Token *)malloc(sizeof(Token));
			res.token->type = TOKEN_RELOP;
			res.token->attribute = *f;
		break;
		}

		f++;
	}

	res.f = f;

	return res;
}

MachineResult machine_catchall(char *in)
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
		case 0: // no match
			f--;
			res.err = MACHINE_ERR_NO_MATCH;
		break;
		case 1: // start
			if (*f == '+')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_ADDOP;
				res.token->attribute = *f;
			}
			else if (*f == '-')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_ADDOP;
				res.token->attribute = *f;
			}
			else if (*f == '*')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_MULOP;
				res.token->attribute = *f;
			}
			else if (*f == '/')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_MULOP;
				res.token->attribute = *f;
			}
			else if (*f == ',')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_COMMA;
				res.token->attribute = 0;
			}
			else if (*f == ';')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_SEMICOLON;
				res.token->attribute = 0;
			}
			else if (*f == '(')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_LPAREN;
				res.token->attribute = 0;
			}
			else if (*f == ')')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_RPAREN;
				res.token->attribute = 0;
			}
			else if (*f == '[')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_LBRACKET;
				res.token->attribute = 0;
			}
			else if (*f == ']')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_RBRACKET;
				res.token->attribute = 0;
			}			
			else if (*f == '.')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_PERIOD;
				res.token->attribute = 0;
			}
			else if (*f == ',')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_COMMA;
				res.token->attribute = 0;
			}
			else if (*f == ':')
				s = 2;
			else
				s = 0;
		break;
		case 2:
			if (*f == '=')
			{
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_ASSIGNOP;
				res.token->attribute = 0;
			}
			else
			{
				f--;
				res.token = (Token *)malloc(sizeof(Token));
				res.token->type = TOKEN_COLON;
				res.token->attribute = 0;
			}
		break;
		}

		f++;
	}

	res.f = f;

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