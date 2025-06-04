#include "../include/logs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDS 100
#define MAX_LINE_LEN 1024

void add_log(ProcesStruct process) {
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

void get_logs() {
    const char *path = "logs/log.txt";
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("ERROR: File not found");
        return;
    }

    char line[MAX_LINE_LEN];
    int ids[MAX_IDS];
    int id_count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}
