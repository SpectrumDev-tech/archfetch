#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
    char color[16];
    char memory_unit[8];
    bool show_palette;
} Config;

void load_config(Config *config);

const char* get_color_code(const char *color_name);

#endif // CONFIG_H