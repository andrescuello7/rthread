#include "../include/process_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDS 100
#define MAX_LINE_LEN 1024

void process_list() {
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
