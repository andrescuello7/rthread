#include <cjson/cJSON.h>
#include "logs.h"
#ifndef SAVE_JSON_FILE
#define SAVE_JSON_FILE
#ifndef ADD_PROCESS
#define ADD_PROCESS
#ifndef LIST_PROCESSES
#define LIST_PROCESSES
#ifndef REMOVE_PROCESS_BY_PID
#define REMOVE_PROCESS_BY_PID

int save_json_file(cJSON *root);
void add_process(ProcesStruct process);
void remove_process_by_pid(int pid);
void list_processes();

#endif
#endif
#endif
#endif
