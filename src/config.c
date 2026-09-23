#include "config.h"
#include "colors.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void trim_inplace(char *str) {
    if (!str || *str == '\0') return;

    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char) * end)) {
        *end = '\0';
        end--;
    }
}

static char* skip_leading_spaces(char *str) {
    while(*str && isspace((unsigned char) * str)) str++;
    return str;
}

void load_config(Config *config) {
    if (!config) return;

    memset(config, 0, sizeof(Config));
    snprintf(config->color, sizeof(config->color), "cyan");
    snprintf(config->memory_unit, sizeof(config->memory_unit), "mib");
    config->show_palette = true;

    const char *home = getenv("HOME");
    if (!home) return;

    char path[512];
    snprintf(path, sizeof(path), "%s/.config/archfetch/archfetch.conf", home);

    FILE *file = fopen(path, "r");
    if (!file) return;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *comment = strchr(line, '#');
        if (comment) *comment = '\0';

        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';
        char *key = skip_leading_spaces(line);
        trim_inplace(key);

        char *value = skip_leading_spaces(eq + 1);
        trim_inplace(value);

        if (strlen(key) == 0 || strlen(value) == 0) continue;

        if (strcmp(key, "color") == 0) {
            snprintf(config->color, sizeof(config->color), "%s", value);
        } else if (strcmp(key, "memory_unit") == 0) {
            snprintf(config->memory_unit, sizeof(config->memory_unit), "%s", value);
        } else if (strcmp(key, "show_palette") == 0) {
            config->show_palette = (strcmp(value, "true") == 0 || strcmp(value, "1") == 0);
        }
    }
    fclose(file);
}

const char* get_color_code(const char *color_name) {
    if (!color_name) return COLOR_CYAN;

    if (strcmp(color_name, "red") == 0) return COLOR_RED;
    if (strcmp(color_name, "green") == 0) return COLOR_GREEN;
    if (strcmp(color_name, "yellow") == 0) return COLOR_YELLOW;
    if (strcmp(color_name, "blue") == 0) return COLOR_BLUE;
    if (strcmp(color_name, "magenta") == 0) return COLOR_MAGENTA;
    if (strcmp(color_name, "white") == 0) return COLOR_WHITE;
    return COLOR_CYAN;
}