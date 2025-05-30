#include "../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Converts a file path like "samples/fastapi/app.py" to module path "samples.fastapi.app"
void logger(int pid) {
    // printf("New log PID[%d]\n", pid);

    char *path = "logs/log.txt";
    char output[1024];
    snprintf(output, sizeof(output), "[+] New process PID[%d]", pid);

    FILE *file = fopen(path, "a");
    if (file == NULL) {
        perror("ERROR: File not found!\n");
        return;
    }

    fprintf(file, "%s\n", output);
    fclose(file);
}
