#include <stdlib.h>
#include <string.h>
#include "reserved.h"
#include "token.h"
#include <stdio.h>

#ifndef MACHINE_H
#define MACHINE_H

typedef struct MachineResult
{
	Token *token;
	char *f;
	int err;
} MachineResult;

#define MACHINE_ERR_NONE 0
#define MACHINE_ERR_NO_MATCH 1

MachineResult machine_whitespace(char *in);

#endif