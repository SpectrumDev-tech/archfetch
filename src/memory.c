#include "memory.h"
#include <stdio.h>
#include <string.h>

int get_memory_info(char *buffer, size_t size, const char *unit) {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        return -1;
    }

    char line[256];
    unsigned long total_kb = 0;
    unsigned long avail_kb = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "MemTotal: %lu kB", &total_kb) == 1) continue;
        if (sscanf(line, "MemAvailable: %lu kB", &avail_kb) == 1) continue;
    }

    fclose(file);

    if (total_kb == 0 || avail_kb == 0) return -1;

    unsigned long used_kb = total_kb - avail_kb;
    
    double used = (double)used_kb / 1024.0;
    double total = (double)total_kb / 1024.0;

    if (unit != NULL && strcmp(unit, "gib") == 0) {
        used /= 1024.0;
        total /= 1024.0;
        snprintf(buffer, size, "%.2f GiB / %.2f GiB", used, total);
    } else {
        snprintf(buffer, size, "%.2f MiB / %.2f MiB", used, total);
    }

    return 0;
}