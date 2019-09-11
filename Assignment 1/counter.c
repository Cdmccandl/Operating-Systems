#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    char *p = 0;
    long countToThis = strtol(argv[1],&p,10);
    for (int i = 1; i <= countToThis; i++) {
        assert (printf("I am the child with PID: %d %d\n", getpid(), i) !=0);
    }

    return countToThis;
}

