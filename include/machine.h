#include <stdlib.h>
#include <string.h>
#include "reserved.h"
#include "token.h"
#include <stdio.h>

#ifndef MACHINE_H
#define MACHINE_H

typedef enum MachineError
{
	MACHINE_ERR_NONE,
	MACHINE_ERR_NO_MATCH
} MachineError;

typedef struct MachineResult
{
	Token *token;
	char *f;
	MachineError err;
} MachineResult;

MachineResult machine_omega(char *in);
MachineResult machine_whitespace(char *in);
MachineResult machine_idres(char *in, ReservedWord *reserved_words);

int is_alpha(char c);
int is_alpha_numeric(char c);
int is_whitespace(char c);

#endif