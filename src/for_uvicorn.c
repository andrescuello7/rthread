#include "../include/for_uvicorn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Converts a file path like "samples/fastapi/app.py" to module path "samples.fastapi.app"
void for_uvicorn_path(const char *path, char *result) {
    strcpy(result, path);
    int len = strlen(result);
    for (int i = 0; i < len; i++) {
        if (result[i] == '/') {
            result[i] = '.';
        }
    }

    char *last_dot = strrchr(result, '.');
    if (last_dot != NULL) {
        *last_dot = '\0';
    }
}
