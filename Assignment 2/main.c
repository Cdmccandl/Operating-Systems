#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <errno.h>
#include <syscall.h>
#include <assert.h>

void handler(int signum);

int main() {

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset (&action.sa_mask);
    action.sa_flags = SA_RESTART;
    assert (sigaction (SIGUSR1, &action, NULL) == 0);
    assert (sigaction (SIGUSR2, &action, NULL) == 0);
    assert (sigaction (SIGHUP, &action, NULL) == 0);


    int waitStatus = 0;
    pid_t childPID = fork();

    if (childPID < 0){
        perror("fork error!");
        return(errno);
    }
    else if (childPID == 0){
        execl("./child","child",NULL);
        perror("execl() failure");
        return(errno);
    }
    else {
        int waitReturn;
        waitReturn = waitpid(childPID, &waitStatus, 0);
        if (waitReturn == -1) {
            perror("wait failure");
            return (errno);
        }
        else if (WIFEXITED(waitStatus) == 0){
            perror("child termination error");
            return(errno);
        }
        else{
            assert(printf("Process %d exited with status %d\n", childPID, WEXITSTATUS(waitStatus)) != 0);
        }
    }
    return 0;
}

void handler(int signum){
    if(signum == 10) {
        assert(printf("caught SIGUSR1 signal %d\n", signum) != 0);
    }
    else if (signum == 12){
        assert(printf("caught SIGUSR2 signal %d\n", signum) != 0);
    }
    else if (signum == 1){
        assert(printf("caught hanging signal %d\n", signum) != 0);
    } else{
        assert(printf("nice signal code: %d\n", signum) != 0);
    }
}
