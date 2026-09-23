#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_shell_info(char *buffer, size_t size) {
    const char *shell_path = getenv("SHELL");
    if (shell_path == NULL || strlen(shell_path) == 0) return -1;

    const char *slash = strrchr(shell_path, '/');
    if (slash != NULL) shell_path = slash + 1;

    strncpy(buffer, shell_path, size -1);
    buffer[size - 1] = '\0';
    return 0;
}