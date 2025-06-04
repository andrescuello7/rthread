#include "../include/process_list.h"
#include "logs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#define RELATIVE_PATH "/.config/rthread/actives.json"

char* get_file_path() {
    const char* home = getenv("HOME");
    if (!home) return NULL;

    size_t path_len = strlen(home) + strlen(RELATIVE_PATH) + 1;
    char* full_path = malloc(path_len);
    if (!full_path) return NULL;

    snprintf(full_path, path_len, "%s%s", home, RELATIVE_PATH);
    return full_path;
}

cJSON* load_json_file() {
    char* file_path = get_file_path();
    if (!file_path) {
        return cJSON_CreateArray();
    }

    FILE *file = fopen(file_path, "r");
    if (!file) {
        free(file_path);
        return cJSON_CreateArray();
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    rewind(file);

    char *data = malloc(len + 1);
    fread(data, 1, len, file);
    data[len] = '\0';
    fclose(file);

    cJSON *root = cJSON_Parse(data);
    free(data);
    free(file_path);

    if (!root) {
        return cJSON_CreateArray();
    }

    return root;
}

int save_json_file(cJSON *root) {
    char* file_path = get_file_path();
    if (!file_path) {
        perror("No se pudo obtener la ruta del archivo");
        return 1;
    }

    char command[512];
    snprintf(command, sizeof(command), "mkdir -p %s/.config/rthread", getenv("HOME"));
    system(command);

    char *string = cJSON_Print(root);
    FILE *file = fopen(file_path, "w");
    if (!file) {
        perror("Error guardando archivo");
        free(string);
        free(file_path);
        return 1;
    }

    fwrite(string, 1, strlen(string), file);
    fclose(file);
    free(string);
    free(file_path);
    return 0;
}


void add_process(ProcesStruct process) {
    cJSON *root = load_json_file();

    cJSON *item = cJSON_CreateObject();
    cJSON_AddNumberToObject(item, "pid", process.id);
    cJSON_AddStringToObject(item, "process", process.port);
    cJSON_AddStringToObject(item, "path", process.path);
    cJSON_AddStringToObject(item, "manager", process.manager);

    cJSON_AddItemToArray(root, item);

    save_json_file(root);
    cJSON_Delete(root);
}

void remove_process_by_pid(int pid) {
    cJSON *root = load_json_file();

    int size = cJSON_GetArraySize(root);
    for (int i = 0; i < size; ++i) {
        cJSON *item = cJSON_GetArrayItem(root, i);
        cJSON *pid_item = cJSON_GetObjectItem(item, "pid");
        if (pid_item && pid_item->valueint == pid) {
            cJSON_DeleteItemFromArray(root, i);
            break;
        }
    }

    save_json_file(root);
    cJSON_Delete(root);
}

void list_processes() {
    cJSON *root = load_json_file();

    int size = cJSON_GetArraySize(root);
    for (int i = 0; i < size; ++i) {
        cJSON *item = cJSON_GetArrayItem(root, i);
        int pid = cJSON_GetObjectItem(item, "pid")->valueint;
        const char *process = cJSON_GetObjectItem(item, "process")->valuestring;
        const char *path = cJSON_GetObjectItem(item, "path")->valuestring;

        printf("\x1b[32mPID\x1b[0m: \x1b[35m%d\x1b[0m | PROCESS: \x1b[35m%s\x1b[0m | PATH: [\x1b[35m%s\x1b[0m]\n", pid, process, path);
    }

    cJSON_Delete(root);
}