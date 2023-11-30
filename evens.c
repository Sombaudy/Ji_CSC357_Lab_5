#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


// void limit_fork(rlim_t max_procs)
// {
//     struct rlimit rl;
//     if (getrlimit(RLIMIT_NPROC, &rl))
//     {
//         perror("getrlimit");
//         exit(-1);
//     }
//     else
//     {
//         printf("Current max processes limit: %lu\n", (unsigned long)rl.rlim_cur);
//         printf("Max processes limit (hard limit): %lu\n", (unsigned long)rl.rlim_max);
//     }
//     rl.rlim_cur = max_procs;
//     if (setrlimit(RLIMIT_NPROC, &rl))
//     {
//         perror("setrlimit");
//         exit(-1);
//     }
// }

int main(int argc, char *argv[])
{
    //limit_fork(100);
    /* continue with program logic here */

    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);

    for (int i = 2; i <= N; i += 2) {
        printf("\t%d\n", i);
    }

    
    return 0;
}
 