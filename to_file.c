#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


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

    if (argc != 3) {
        printf("Usage: %s <program_name> <output_file>\n", argv[0]);
        return 1;
    }

    char *exec = argv[1];
    char *filename = argv[2];

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1) {
            perror("failed to open file");
            exit(-1);
        }

        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("failed to put stdout in file");
            exit(-1);
        }
        close(fd);

        execlp(exec, exec, NULL);
        perror("exec failed");
        exit(1);
    }

    wait(NULL);

    return 0;
}
 