#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "osinfo.h"
#include "uptime.h"
#include "memory.h"
#include "cpu.h"
#include "colors.h"

#define BUFFER_SIZE 256

int main(void) {
    char os_buf[BUFFER_SIZE] = "Unknown";
    char kernel_buf[BUFFER_SIZE] = "Unknown";
    char uptime_buf[BUFFER_SIZE] = "Unknown";
    char mem_buf[BUFFER_SIZE] = "Unknown";
    char cpu_buf[BUFFER_SIZE] = "Unknown";

    get_os_name(os_buf, sizeof(os_buf));
    get_kernel_version(kernel_buf, sizeof(kernel_buf));
    get_uptime(uptime_buf, sizeof(uptime_buf));
    get_memory_info(mem_buf, sizeof(mem_buf));
    get_cpu_info(cpu_buf, sizeof(cpu_buf));

    printf(COLOR_CYAN "       /\\         " COLOR_CYAN "%s" COLOR_RESET "@" COLOR_CYAN "archlinux\n" COLOR_RESET, getenv("USER") ? getenv("USER") : "user");
    printf(COLOR_CYAN "      /  \\        " COLOR_RESET "-------------------\n");
    printf(COLOR_CYAN "     / /\\ \\       " COLOR_CYAN "OS:     " COLOR_RESET "%s\n", os_buf);
    printf(COLOR_CYAN "    / /  \\ \\      " COLOR_CYAN "Kernel: " COLOR_RESET "%s\n", kernel_buf);
    printf(COLOR_CYAN "   / /  __\\ \\     " COLOR_CYAN "Uptime: " COLOR_RESET "%s\n", uptime_buf);
    printf(COLOR_CYAN "  / /  /  /  \\    " COLOR_CYAN "Memory: " COLOR_RESET "%s\n", mem_buf);
    printf(COLOR_CYAN " / /__/  /____\\   " COLOR_CYAN "CPU:    " COLOR_RESET "%s\n", cpu_buf);
    printf(COLOR_CYAN "/________/_____\\   " COLOR_RESET "\n\n");

    return EXIT_SUCCESS;
}