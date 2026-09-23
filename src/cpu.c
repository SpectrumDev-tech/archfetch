#include "cpu.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int get_cpu_info(char *buffer, size_t size) {
    FILE *file = fopen("/proc/cpuinfo", "r");
    if (file == NULL) return -1;
    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "model name", 10) == 0) {
            char *colon = strchr(line, ':');
            if (colon != NULL) {
                colon++;
                while (*colon == ' ' || *colon == '\t') colon++;

                strncpy(buffer, colon, size - 1);
                buffer[size - 1] = '\0';

                trim_newline(buffer);

                found = 1;
                break;
            }
        }
    }
    fclose(file);
    return found ? 0 : -1;
}