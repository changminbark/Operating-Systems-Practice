#include "wrappers.h"

#include <string.h>

char *trim(char *str) {
    // Trim leading space
    while (*str == ' ') str++;

    // Trim trailing space
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t')) {
        *end = '\0';
        end--;
    }

    return str;
}