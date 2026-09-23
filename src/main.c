#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "osinfo.h"
#include "uptime.h"
#include "memory.h"
#include "cpu.h"
#include "colors.h"
#include "packages.h"
#include "shell.h"
#include "wm.h"

#define BUFFER_SIZE 256
#define INFO_COUNT 8

typedef struct {
    const char *key;
    char value[BUFFER_SIZE];
} InfoItem;

static const char *logo[] = {
    COLOR_CYAN "       /\\       " COLOR_RESET,
    COLOR_CYAN "      /  \\      " COLOR_RESET,
    COLOR_CYAN "     /\\   \\     " COLOR_RESET,
    COLOR_CYAN "    /      \\    " COLOR_RESET,
    COLOR_CYAN "   /   ,,   \\   " COLOR_RESET,
    COLOR_CYAN "  /   |  |  -\\  " COLOR_RESET,
    COLOR_CYAN " /_-''    ''-_\\ " COLOR_RESET,
    COLOR_CYAN "                " COLOR_RESET
};

#define LOGO_LINES (sizeof(logo) / sizeof(logo[0]))

int main(void) {
    InfoItem info[INFO_COUNT] = {
        {"OS", "Unknown"},
        {"Kernel", "Unknown"},
        {"Uptime", "Unknown"},
        {"Packages", "Unknown"},
        {"Shell", "Unknown"},
        {"WM/DE", "Unknown"},
        {"Memory", "Unknown"},
        {"CPU", "Unknown"},
    };

    get_os_name(info[0].value, BUFFER_SIZE);
    get_kernel_version(info[1].value, BUFFER_SIZE);
    get_uptime(info[2].value, BUFFER_SIZE);
    get_package_count(info[3].value, BUFFER_SIZE);
    get_shell_info(info[4].value, BUFFER_SIZE),
    get_wm_info(info[5].value, BUFFER_SIZE),
    get_memory_info(info[6].value, BUFFER_SIZE);
    get_cpu_info(info[7].value, BUFFER_SIZE);

    size_t max_key_len = 0;
    for (int i = 0; i < INFO_COUNT; i++) {
        size_t len = strlen(info[i].key);
        if (len > max_key_len) {
            max_key_len = len;
        }
    }

    const char *user = getenv("USER") ? getenv("USER") : "user";

    printf("%s " COLOR_CYAN "%s" COLOR_RESET "@" COLOR_CYAN "archlinux\n" COLOR_RESET, logo[0], user);

    size_t user_host_len = strlen(user) + 10;
    printf("%s ", logo[1]);
    for (size_t i = 0; i < user_host_len; i++) {
        putchar('-');
    }
    putchar('\n');

    for (int i = 0; i < INFO_COUNT; i++) {
        const char *logo_line = (i + 2 < (int)LOGO_LINES ? logo[i + 2] : "                ");
        printf("%s " COLOR_CYAN "%-*s" COLOR_RESET " : %s\n", logo_line, (int)max_key_len, info[i].key, info[i].value);
    }

    printf("%s \n", logo[7]);
    printf("                 "
            BG_BLACK "   " BG_RED "   " BG_GREEN "   "
            BG_YELLOW "   " BG_BLUE "   " BG_MAGENTA "   "
        BG_CYAN "   " BG_WHITE "   " COLOR_RESET "\n\n");

    return EXIT_SUCCESS;
}