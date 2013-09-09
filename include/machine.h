#include <stdlib.h>
#include <string.h>
#include "reserved.h"
#include "token.h"

#ifndef MACHINE_H
#define MACHINE_H

typedef struct MachineResult
{
	Token *token;
	char *f;
	int err;
} MachineResult;

#endif