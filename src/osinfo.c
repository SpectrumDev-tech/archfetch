#include "osinfo.h"
#include "utils.h"
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
            strncpy(buffer, start, size - 1);
            buffer[size - 1] = '\0';
            
            trim_quotes(buffer);

            found = 1;
            break;
        }
    }

    fclose(file);
    return found ? 0 : -1;
}