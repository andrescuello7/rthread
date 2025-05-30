#include "for_uvicorn.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100
char *PATH;
char *PORT;
char *MANAGER;

// Struct to store process information for each thread
typedef struct {
    int id;
    char *port;
    char *path;
    char *manager;
} ThreadStruct;

// Thread function that forks a child process and executes the target process
void *run_process(void *arg){
    ThreadStruct *process = (ThreadStruct*)arg;
    
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error: build fork");
        pthread_exit(NULL);
    }

    if (pid == 0) {
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
        if (strcmp(process->manager, "node") == 0) {
            setenv("PORT", process->port, 1);
            execlp("node", "node", process->path, (char *)NULL);
        }
        perror("Error in execlp");
        exit(EXIT_FAILURE);
    } else {
        logger(pid);
        printf("\033[01;32m[+]\033[0m Process run on PORT [%s] PID [\033[01;33m%d\033[0m]\n", process->port, pid);
    }

    // TODO: Wait for the child process to finish
    // int status;
    // waitpid(pid, &status, 0);
    pthread_exit(NULL);
}

// Create and run multiple threads to launch concurrent processes
void threads_exec(int num_threads){
    pthread_t threads[num_threads];
    ThreadStruct thread_data[num_threads];
    
    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].id = i;
        thread_data[i].port = PORT;
        thread_data[i].path = PATH;
        thread_data[i].manager = MANAGER;
        pthread_create(&threads[i], NULL, run_process, (void*)&thread_data[i]);
    }
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

int main(int argc, char **argv){
    if(argc != 7 || strcmp(argv[1], "-m") != 0 || strcmp(argv[3], "-r") != 0 || strcmp(argv[5], "-p") != 0){
        printf("$ rthread -m [NPM|UVICORN] -r [ROOT(main.py)] -p [PORT]!\n");
        exit(-1);
    }
    
    // Read CLI arguments
    MANAGER = argv[2];
    PATH = argv[4];
    PORT = argv[6];
    int num_threads = 1;
    
    // Start thread(s) to run the process(es)
    threads_exec(num_threads);
    return 0;
}
