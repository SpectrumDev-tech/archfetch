#include "utils.h"
#include <stddef.h>
#include <string.h>

void trim_newline(char *str) {
    if (str == NULL) return;
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

void trim_quotes(char *str) {
    if (str == NULL) return;
    trim_newline(str);

    size_t len = strlen(str);

    if (len > 0 && (str[len - 1] == '"' || str[len - 1] == '\'')) {
        str[len - 1] = '\0';
        len--;
    }

    if (len > 0 && (str[0] == '"' || str[0] == '\'')) {
        memmove(str, str + 1, len);
    }
}