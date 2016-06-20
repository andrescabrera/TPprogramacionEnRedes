#ifndef PETICION_H_INCLUDED
#define PETICION_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "db-access.h"

void atenderPeticion(int socket);

#endif