#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

    pid_t pid = fork();
    const int size = argc;
    if(pid == 0) {
        char **args = new char*[size];
        for (int i = 0; i < argc- 1; i++) {
            args[i] = argv[i + 1];
        }
        args[argc-1] = NULL;

        if (execvp(argv[1], args) == -1) {
            perror("error execing");
            return 5;
        }
        delete * args;
    }
    else {
        waitpid(pid, NULL, 0);
        char * done[1];
        done[0] = (char *)"done";
        if(execvp("echo", done) == -1){
            perror("error execing");
            return 69;
        }
    }

    return EXIT_SUCCESS;
}