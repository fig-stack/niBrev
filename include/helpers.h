#ifndef HELPERS_H
#define HELPERS_H

#include "main.h"
#include <stdlib.h>

int get_header(struct mach_header_64 *header, FILE *binary);
const char *getLoadCommandName(uint32_t cmd);
uint32_t swap_uint32(uint32_t val);

#endif

