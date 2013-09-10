#include <stdlib.h>
#include <string.h>

#include "token.h"
#include <stdio.h>

#ifndef MACHINE_H
#define MACHINE_H

typedef enum MachineError
{
	MACHINE_ERR_NONE,
	MACHINE_ERR_NO_MATCH,
	MACHINE_ERR_ID_TOO_LONG,
	MACHINE_ERR_INT_TOO_LONG,
	MACHINE_ERR_REAL_XX_TOO_LONG,
	MACHINE_ERR_REAL_YY_TOO_LONG,
	MACHINE_ERR_REAL_ZZ_TOO_LONG
} MachineError;

typedef struct MachineResult
{
	Token *token;
	char *f;
	MachineError err;
} MachineResult;

#define MAX_ID_LEN 10
#define MAX_INT_LEN 10
#define MAX_REAL_XX_LEN 5
#define MAX_REAL_YY_LEN 5
#define MAX_REAL_ZZ_LEN 2

MachineResult machine_omega(char *in);
MachineResult machine_whitespace(char *in);
MachineResult machine_idres(char *in, ReservedWord *reserved_words);
MachineResult machine_int(char *in);
MachineResult machine_real(char *in);
MachineResult machine_longreal(char *in);

int is_alpha(char c);
int is_alpha_numeric(char c);
int is_numeric(char c);
int is_plus_or_minus(char c);
ReservedWord *is_reserved_word(char *word, ReservedWord *reserved_words);
int is_whitespace(char c);

#endif