#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <syscall.h>
#include <assert.h>
#include <stdlib.h>
#include "syscall.h"

void handler(int signum);

int main() {

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    assert (sigaction(SIGCHLD, &action, NULL) == 0);
    assert (sigaction(SIGCONT, &action, NULL) == 0);
    assert (sigaction(SIGINT, &action, NULL) == 0);

    pid_t childPID = fork();

    if (childPID < 0) {
        perror("fork error!");
        return (errno);
    } else if (childPID == 0) {
        execl("./child", "child", (char *) 0);
        perror("execl() failure");
        return (errno);
    } else {
        int counter = 0;
        while (counter < 5) {
            assert(printf("Parent is going to SIGSTOP child\n") != 0);
            assert(kill(childPID, 19) == 0);
            assert(sleep(2) == 0);
            assert(printf("Parent is going to SIGCONT the child\n") != 0);
            assert(kill(childPID, 18) == 0);
            assert(sleep(2) == 0);
            counter++;
        }
        assert(kill(childPID, 2) == 0);
        pause();
        return 0;
    }
}

void handler(int signum) {
    if(signum == 17){
        write(1,"Child has exited\n",18);
        int waitStatus = 0;
        wait(&waitStatus);
        if (waitStatus == -1){
            perror("wait failure");
            exit(errno);
        }
        else if (WIFSIGNALED(waitStatus) != 0){
            WRITESTRING("Exit code: ");
            WRITEINT(WTERMSIG(waitStatus), 5);
        }
        else if (WIFEXITED(waitStatus) != 0){
            WRITESTRING("Exit Code: ");
            WRITEINT(WEXITSTATUS(waitStatus), 5);
        }
        else{
            perror("child termination error");
            exit(errno);
        }
        exit(EXIT_SUCCESS);
    }
    else if (signum == 19){
        write(1,"Caught stop signal\n", 20); //this cannot be caught
    }
    else if (signum == 18){
        write(1,"Caught continue signal\n", 24);//only prints once assuming signal is collapsing
    }

}
