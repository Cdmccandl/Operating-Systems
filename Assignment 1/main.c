#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <error.h>
#include <assert.h>
#include <errno.h>
/*
 Conor McCandless Assignemnt 1
 CS 3600 Operating Systems
 this program uses the fork command to generate a duplicate process that lists its
 ID as well as the parents ID it then executes a separate compiled c program that loops
 5 times listing the child PID the parent then lists the exit status after waiting for the
 child to finish*/
//helped Joe Turner with project design

int main() {
    int waitStatus;
    int result = fork();
    if (result < 0){
        perror("fork error!");
        return(errno);
    }
    else if (result == 0){ //child
        assert (printf("Child PID: %d\n", getpid()) != 0);
        assert (printf("Parent PID %d\n", getppid()) != 0);
        execl("./counter", "counter", "5", (char *)0);
        perror("execl failure!");//execl only returns if it fails
        return(errno);
    }
    else { //parent
        int waitReturn = waitpid(result, &waitStatus, 0);
        if (waitReturn == -1) {
            perror("wait failed");
            return(errno);
        } else if (WIFEXITED(waitStatus) == 0) {
            perror("child termination error");
            return(errno);
        }
        else{
            assert (printf("Process %d exited with status %d\n", result, WEXITSTATUS(waitStatus)) != 0);
        }
    }

    return 0;
}