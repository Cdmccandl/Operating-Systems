#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <stdlib.h>
#include <assert.h>

int main() {

    pid_t childPID = getpid();
    while(1) {
        assert(printf("Awake in PID %d\n", childPID) != 0);
        assert(sleep(1) == 0);
    }
    return 0;
}

