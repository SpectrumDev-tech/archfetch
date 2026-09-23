#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "osinfo.h"
#include "uptime.h"
#include "memory.h"

#define BUFFER_SIZE 256

int main(void) {
    char os_buf[BUFFER_SIZE];
    char kernel_buf[BUFFER_SIZE];
    char uptime_buf[BUFFER_SIZE];
    char mem_buf[BUFFER_SIZE];

    printf("Arch Linux System Information Fetcher\n");
    printf("-------------------------------------\n");

    if (get_os_name(os_buf, sizeof(os_buf)) == 0) {
        printf("OS:      %s\n", os_buf);
    } else {
        printf("OS:      Unknown\n");
    }

    if (get_kernel_version(kernel_buf, sizeof(kernel_buf)) == 0) {
        printf("kernel: %s\n", kernel_buf);
    } else {
        fprintf(stderr, "Error: Could not read kernel version\n");
        return EXIT_FAILURE;
    }

    if (get_uptime(uptime_buf, sizeof(uptime_buf)) == 0) {
        printf("Uptime: %s\n", uptime_buf);
    } else {
        printf("Uptime: Unknown\n");
    }

    if (get_memory_info(mem_buf, sizeof(mem_buf)) == 0) {
        printf("RAM: %s\n", mem_buf);
    } else {
        printf("RAM: Unknown\n");
    }


    return EXIT_SUCCESS;
}