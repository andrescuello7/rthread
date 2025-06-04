#include "for_uvicorn.h"
#include "process_list.h"
#include "logs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

ProcesStruct process_data[1];

// Thread function that forks a child process and executes the target process
void *run_process(void *arg)
{
    ProcesStruct *process = (ProcesStruct *)arg;
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error: build fork");
        pthread_exit(NULL);
    }

    if (pid == 0)
    {
        // Special formatting for uvicorn: convert path to module format + ":app"
        if (strcmp(process->manager, "uvicorn") == 0)
        {
            char formatted[256];
            for_uvicorn_path(process->path, formatted);
            
            char new_path_uvi[300];
            sprintf(new_path_uvi, "%s:app", formatted);
            
            process->path = new_path_uvi;
            execlp("uvicorn", "uvicorn", "--port", process->port, process->path, (char *)NULL);
        }
        if (strcmp(process->manager, "node") == 0)
        {
            setenv("PORT", process->port, 1);
            execlp("node", "node", process->path, (char *)NULL);
        }
        perror("Error in execlp");
        exit(EXIT_FAILURE);
    }
    else
    {
        process->id = pid;
        add_process(*process);
        add_log(*process);
        printf("\033[01;32m[+]\033[0m Process run on PORT [%s] PID [\033[01;33m%d\033[0m]\n\n", process->port, pid);
    }

    // TODO: Wait for the child process to finish
    // int status;
    // waitpid(pid, &status, 0);
    pthread_exit(NULL);
}

// Create and run multiple threads to launch concurrent processes
void create_model(
    int num_threads, 
    char *PATH,
    char *PORT,
    char *MANAGER)
{
    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        process_data[i].id = i;
        process_data[i].port = PORT;
        process_data[i].path = PATH;
        process_data[i].manager = MANAGER;
        pthread_create(&threads[i], NULL, run_process, (void *)&process_data[i]);
    }
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void val_args(int argc, char **argv){
    if (argc == 2 && (strcmp(argv[1], "--logs") == 0))
    {
        get_logs();
    }
    else if (argc == 2 && (strcmp(argv[1], "--list") == 0))
    {
        list_processes();
        exit(0);
    }
    else if (argc == 3 && (strcmp(argv[1], "-k") == 0 || strcmp(argv[1], "--kill") == 0))
    {
        char *PID = argv[2];
        remove_process_by_pid(atoi(PID));
        execlp("kill", "kill", "-9", PID, (char *)NULL);
    }
    else if (argc == 7 && (strcmp(argv[1], "-m") == 0 && strcmp(argv[3], "-r") == 0 && strcmp(argv[5], "-p") == 0))
    {
        // TODO: Number of THREADS in 1
        create_model(1, argv[4], argv[6], argv[2]);
    } else {
        printf("\x1b[35mR-THREAD Run Programs _(^_^)_ \x1b[0m\n\n\x1b[35m$\x1b[0m rthread -m (node|uvicorn) -r (path) -p PORT\n\n\x1b[35m$\x1b[0m rthread -k --kill (PID) \n\x1b[35m$\x1b[0m rthread --logs \n\x1b[35m$\x1b[0m rthread --list \n");
    }
    exit(0);
}

int main(int argc, char **argv)
{
    val_args(argc, argv);
    return 0;
}
