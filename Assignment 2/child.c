#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <error.h>
#include <errno.h>
#include <assert.h>

int main(){

    int parentPID = getppid();

    assert(kill(parentPID, SIGUSR1) == 0);
    assert(kill(parentPID, SIGUSR2) == 0);
    assert(kill(parentPID, SIGHUP) == 0);
    assert(kill(parentPID, SIGHUP) == 0);
    assert(kill(parentPID, SIGHUP) == 0);

    return 0;
}
