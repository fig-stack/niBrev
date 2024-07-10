#include "../include/getExports.h"
#include "../include/helpers.h"

void getExports(FILE *binary) {
  uint32_t cmd, cmdsize, dataoff, datasize;

  uint32_t buffer = 0;
  uint64_t mem_addr = base;
  uint8_t byte_buf[4];
  uint32_t current_cmd = 0;
  uint64_t exports_end = base;

  struct mach_header_64 *header = malloc(sizeof(struct mach_header_64));
  if (get_header(header, binary) != 0) {
    ERROR("Error getting header");
    return;
  }

  while ((fread(&buffer, 1, BUFFER_SIZE, binary)) == BUFFER_SIZE) {
    byte_buf[0] = buffer & 0xFF;
    byte_buf[1] = (buffer >> 8) & 0xFF;
    byte_buf[2] = (buffer >> 16) & 0xFF;
    byte_buf[3] = (buffer >> 24) & 0xFF;

    /* check if the current buffer is LC_DYLD_EXPORTS_TRIE */
    if (mem_addr >= base + sizeof(struct mach_header_64) &&
        current_cmd < header->ncmds && buffer == LC_DYLD_EXPORTS_TRIE) {
      printf("*_-_-_-_-_-_-_-_- LC_DYLD_EXPORTS_TRIE _-_-_-_-_-_-_-_-*\n"
             "   - - - - - - - - FOUND AT 0x%llx - - - - - - - -    \n"
             "._-_-_-_-_-_-_-_- ~~~~~~~~~~~~~~~~~~~~ -_-_-_-_-_-_-_-.\n\n",
             mem_addr);

      fseek(binary, -4, SEEK_CUR); // Ensure we're at the start of the command
      fread(&cmd, sizeof(uint32_t), 1, binary);
      fread(&cmdsize, sizeof(uint32_t), 1, binary);
      fread(&dataoff, sizeof(uint32_t), 1, binary);
      fread(&datasize, sizeof(uint32_t), 1, binary);

      printf("JUMPING TO 0x%llx\n", (uint64_t)dataoff);

      /* store the end of the exports structure */
      exports_end = base + (uint64_t)dataoff + (uint64_t)datasize;

      /* set the memory address tracker to the start of the structure */
      mem_addr = base + (uint64_t)dataoff;

      if (fseek(binary, dataoff, SEEK_SET) != 0) {
        ERROR("fseek() failed");
        return;
      }
      break;
    }

    mem_addr += BUFFER_SIZE;
  }

  if (ferror(binary)) {
    ERROR("Error reading file");
    return;
  }

  /* Loop through the exports */
  uint8_t last_bytes_buf[LAST_BYTES_SIZE];
  int bytesRead = 0;
  char accumulator[256] = {0};
  int accumulatorIndex = 0;

  while ((bytesRead = fread(last_bytes_buf, 1, LAST_BYTES_SIZE, binary)) > 0 &&
         mem_addr < exports_end) {
    for (int i = 0; i < bytesRead; i++) {
      if (isalpha(last_bytes_buf[i]) || last_bytes_buf[i] == '_' ||
          last_bytes_buf[i] == '/' || last_bytes_buf[i] == '-') {
        if (accumulatorIndex < 255) {
          accumulator[accumulatorIndex++] = last_bytes_buf[i];
        }
      } else {
        if (accumulatorIndex >= MIN_STRING_LENGTH) {
          accumulator[accumulatorIndex] = '\0';
          printf("%s\n", accumulator);
        }
        accumulatorIndex = 0;
      }
    }

    mem_addr += LAST_BYTES_SIZE;
  }

  if (accumulatorIndex >= MIN_STRING_LENGTH) {
    accumulator[accumulatorIndex] = '\0';
    printf("%s\n", accumulator);
  }
}

