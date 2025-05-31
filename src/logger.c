#include "../include/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void logger(ProcesStruct process) {
    char *path = "logs/log.txt";
    char output[1024];
    snprintf(output, sizeof(output), "PID: %d | PROCESS: %s | PATH: %s", process.id, process.manager, process.path);

    FILE *file = fopen(path, "a");
    if (file == NULL) {
        perror("ERROR: File not found!\n");
        return;
    }

    fprintf(file, "%s\n", output);
    fclose(file);
}
