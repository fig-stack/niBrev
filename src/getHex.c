#include "../include/getHex.h"
#include "../include/helpers.h"

void getHex(FILE *binary) {
  uint32_t buffer = 0;
  uint64_t mem_addr = base;
  uint8_t ascii_buf[4];
  struct mach_header_64 header;
  uint32_t current_cmd = 0;
  
  fread(&header, sizeof(struct mach_header_64), 1, binary);
  if (feof(binary)) {
    ERROR("unexpected end of file");
    return;
  } else if (ferror(binary)) {
    ERROR("error reading file");
    return;
  }

  if (header.magic != MH_MAGIC_64) {
    ERROR("Not a 64-bit Mach-O binary");
    return;
  }

  if (fseek(binary, -sizeof(struct mach_header_64), SEEK_CUR) != 0) {
    ERROR("fseek() failed");
    return;
  }

  while ((fread(&buffer, 1, BUFFER_SIZE, binary)) == BUFFER_SIZE) {
    ascii_buf[0] = buffer & 0xFF;
    ascii_buf[1] = (buffer >> 8) & 0xFF;
    ascii_buf[2] = (buffer >> 16) & 0xFF;
    ascii_buf[3] = (buffer >> 24) & 0xFF;

    printf("0x%llx: %02x %02x %02x %02x   %c%c%c%c", mem_addr, ascii_buf[0],
           ascii_buf[1], ascii_buf[2], ascii_buf[3],
           isprint(ascii_buf[0]) ? ascii_buf[0] : '.',
           isprint(ascii_buf[1]) ? ascii_buf[1] : '.',
           isprint(ascii_buf[2]) ? ascii_buf[2] : '.',
           isprint(ascii_buf[3]) ? ascii_buf[3] : '.');
    if (mem_addr <= base + sizeof(struct mach_header_64)) {
      if (mem_addr == base) {
        printf(" %s", "magic");
      } else if (mem_addr == base + 4) {
        printf(" %s", "cputype");
      } else if (mem_addr == base + 8) {
        printf(" %s", "cpusubtype");
      } else if (mem_addr == base + 12) {
        printf(" %s", "filetype");
      } else if (mem_addr == base + 16) {
        printf(" %s", "ncmds");
      } else if (mem_addr == base + 20) {
        printf(" %s", "sizeofcmds");
      } else if (mem_addr == base + 24) {
        printf(" %s", "flags");
      }
    }

    if (mem_addr >= base + sizeof(struct mach_header_64) &&
        current_cmd < header.ncmds) {
      const char *cmd_name = getLoadCommandName(buffer);
      if (cmd_name) {
        printf(" %s", cmd_name);
        current_cmd++;
      }
    }

    printf("\n");
    mem_addr += BUFFER_SIZE;
  }

  rewind(binary);
}
