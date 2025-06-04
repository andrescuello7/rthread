#ifndef ADD_LOG
#ifndef GET_LOG
#define ADD_LOG
#define GET_LOG

typedef struct
{
    int id;
    char *port;
    char *path;
    char *manager;
} ProcesStruct;

void get_logs();
void add_log(ProcesStruct process);

#endif
#endif
