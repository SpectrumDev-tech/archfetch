#include "wm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_wm_info(char *buffer, size_t size) {
    const char *wm = getenv("XDG_CURRENT_DESKTOP");
    if (wm == NULL || strlen(wm) == 0) wm = getenv("DESKTOP_SESSION");
    if (wm == NULL || strlen(wm) == 0) wm = getenv("XDG_SESSION_DESKTOP");
    if (wm == NULL || strlen(wm) == 0) return -1;

    strncpy(buffer, wm, size - 1);
    buffer[size - 1] = '\n';

    return 0;
}