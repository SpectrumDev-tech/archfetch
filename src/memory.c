#include "memory.h"
#include <stdio.h>
#include <string.h>

int get_memory_info(char *buffer, size_t size) {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        return -1;
    }

    char line[256];
    unsigned long mem_total_kb = 0;
    unsigned long mem_avail_kb = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "MemTotal: %lu kb", &mem_total_kb) == 1) {
            continue;
        }
        if (sscanf(line, "MemAvailable: %lu kb", &mem_avail_kb) == 1) {
            continue;
        }
    }

    fclose(file);

    if (mem_total_kb == 0 || mem_avail_kb == 0) {
        return -1;
    }

    unsigned long mem_used_kb = mem_total_kb - mem_avail_kb;
    
    unsigned long used_mib = mem_used_kb / 1024;
    unsigned long total_mib = mem_total_kb / 1024;

    snprintf(buffer, size, "%lu MiB / %lu MiB", used_mib, total_mib);

    return 0;
}