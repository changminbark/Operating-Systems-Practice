#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "hexdump.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <filename> <offset> <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    unsigned long offset = strtoul(argv[2], NULL, 10);
    unsigned long size = strtoul(argv[3], NULL, 10);

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    if (fseek(fp, offset, SEEK_SET) != 0) {
        perror("Error seeking in file");
        fclose(fp);
        return EXIT_FAILURE;
    }

    unsigned char *buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, size, fp);
    if (bytesRead == 0) {
        fprintf(stderr, "No data read from file.\n");
        free(buffer);
        fclose(fp);
        return EXIT_FAILURE;
    }

    hexdump(buffer, (unsigned int)bytesRead);

    free(buffer);
    fclose(fp);
    return EXIT_SUCCESS;
}
