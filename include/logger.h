#ifndef LOGGER
#define LOGGER
typedef struct
{
    int id;
    char *port;
    char *path;
    char *manager;
} ProcesStruct;

void logger(ProcesStruct process);

#endif
