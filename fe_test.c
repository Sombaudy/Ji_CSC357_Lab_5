#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void limit_fork(rlim_t max_procs)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl))
    {
        perror("getrlimit");
        exit(-1);
    }
    else
    {
        printf("Current max processes limit: %lu\n", (unsigned long)rl.rlim_cur);
        printf("Max processes limit (hard limit): %lu\n", (unsigned long)rl.rlim_max);
    }
    rl.rlim_cur = max_procs;
    if (setrlimit(RLIMIT_NPROC, &rl))
    {
        perror("setrlimit");
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
    limit_fork(100);
    /* continue with program logic here */

    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }

    //int N = atoi(argv[1]);

    pid_t pid_odd = fork();

    if (pid_odd < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid_odd == 0) {
        // Child process
        execlp("./odds", "odds", argv[1], NULL);
        perror("execlp");
        exit(1);
    }

    pid_t pid_even = fork();

    if (pid_even < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid_even == 0) {
        // Child process
        execlp("./evens", "evens", argv[1], NULL);
        perror("execlp");
        exit(1);
    }

    waitpid(pid_odd, NULL, 0);
    waitpid(pid_even, NULL, 0);

    return 0;
}
 