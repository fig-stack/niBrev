#ifndef GET_EXPORTS_H
#define GET_EXPORTS_H

#include "helpers.h"
#include "main.h"
#include <ctype.h>
#include <sys/_endian.h>

#define LAST_BYTES_SIZE 20
#define MIN_STRING_LENGTH 4

void getExports(FILE *binary);

#endif
