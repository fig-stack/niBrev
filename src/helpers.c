#include "../include/helpers.h"

const char *getLoadCommandName(uint32_t cmd) {
  for (size_t i = 0; i < sizeof(loadCommandTable) / sizeof(LoadCommandEntry);
       i++) {
    if (loadCommandTable[i].cmd == cmd) {
      return loadCommandTable[i].name;
    }
  }
  return NULL;
}

int get_header(struct mach_header_64 *header, FILE *binary) {
  if (fread(header, sizeof(struct mach_header_64), 1, binary) != 1) {
    ERROR("Error reading header");
    return (-1);
  }

  if (header->magic != MH_MAGIC_64) {
    ERROR("Not a 64-bit Mach-O binary");
    return (-1);
  }

  if (fseek(binary, -sizeof(struct mach_header_64), SEEK_CUR) != 0) {
    ERROR("fseek() failed");
    return (-1);
  }

  return 0;
}

uint32_t swap_uint32(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}
