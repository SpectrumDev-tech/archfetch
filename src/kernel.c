#include "kernel.h"
#include "utils.h"
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
    trim_newline(buffer);
    return 0;
}