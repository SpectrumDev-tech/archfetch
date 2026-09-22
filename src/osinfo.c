#include "osinfo.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int get_os_name(char *buffer, size_t size) {
    FILE *file = fopen("/etc/os-release", "r");
    if (file == NULL) {
        return -1;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
            char *start = line + 12;
            if (*start == '"') {
                start++;
            }

            strncpy(buffer, start, size - 1);
            buffer[size - 1] = '\0';

            size_t len = strlen(buffer);
            while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '"' || buffer[len - 1] == '\r')) {
                buffer[len - 1] = '\0';
                len--;
            }
            found = 1;
            break;
        }
    }

    fclose(file);
    return found ? 0 : -1;
}