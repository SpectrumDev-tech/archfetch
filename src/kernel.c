#include "kernel.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int get_kernel_version(char *buffer, size_t size) {
    FILE *file = fopen("/proc/sys/kernel/osrelease", "r");
    if (file == NULL) {
        return -1;
    }

    if (fgets(buffer, size, file) == NULL) {
        fclose(file);
        return -1;
    }

    fclose(file);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len -1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return 0;
}