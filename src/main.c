#include "../include/main.h"
#include "../include/getHex.h"
#include "../include/getExports.h"

int main(int argc, char *argv[]) {
  FILE *binary;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        return 1;
    }

  
    binary = fopen(argv[1], "rb");
    if (!binary) {
        ERROR("Couldn't open file");
        return 1;
    }

    getHex(binary);
    printf("\n\n");

    getExports(binary);

    fclose(binary);
    return 0;
}
