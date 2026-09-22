#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "osinfo.h"

#define BUFFER_SIZE 256

int main(void) {
    char os_buf[BUFFER_SIZE];
    char kernel_buf[BUFFER_SIZE];

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

    return EXIT_SUCCESS;
}