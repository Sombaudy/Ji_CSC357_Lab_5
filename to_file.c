#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <program_name> <output_file>\n", argv[0]);
        return 1;
    }

    char *exec = argv[1];
    char *filename = argv[2];

    
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("failed to open file");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("failed to put stdout in file");
        return 1;
    }
    close(fd);

    execlp(exec, exec, NULL);
    perror("exec failed (note: when running program write ./tofile ./<program_name> <file_name>)");
    return 1;
}
 