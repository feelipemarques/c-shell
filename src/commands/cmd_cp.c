#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int cmd_cp(int argc, char **argv){
    int src = open(argv[1], 0);

    int dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);

    char buffer[4096];

    while(read(src, buffer, 4096) != 0){
        write(dest, buffer, 4096);
    }

    close(src);
    close(dest);

    return 1;
}