#include <iostream>
#include <unistd.h>

int main(){

    pid_t pid1 = fork();
    if(pid1 == 0){
        pid_t pid2 = fork();
        if(pid2 == 0){
            if(execlp("ls", "ls", NULL) == -1){
                perror("error execing ls");
                return 3;
            }
        }
        else {
            waitpid(pid2, NULL, 0);
            if(execlp("date", "date", NULL) == -1){
                perror("error execing date");
                return 5;
            }
        }
    }
    else {
        waitpid(pid1, NULL, 0);
        if(execlp("pwd", "pwd", NULL) == -1){
            perror("error execing pwd");
            return 7;
        }
    }

    return EXIT_SUCCESS;
}