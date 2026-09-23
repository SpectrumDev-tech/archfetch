#define _DEFAULT_SOURCE

#include "packages.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int get_package_count(char *buffer, size_t size) {
    DIR *dir = opendir("/var/lib/pacman/local");
    if (dir == NULL) return -1;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        if (strcmp(entry->d_name, "ALPM_DB_VERSION") == 0) {
            continue;
        }

        if (entry->d_type == DT_DIR) {
            count++;
        }
    }

    closedir(dir);

    snprintf(buffer, size, "%d (pacman)", count);
    return 0;
}