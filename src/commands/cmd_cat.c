#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int cmd_cat(int argc, char **argv){
    int fd = STDIN_FILENO;

    if(argc > 1){
        fd = open(argv[1], O_RDONLY);
        if(fd < 0){
            perror("cat: error reading file");
            return 1;
        }
    }

    char buffer[4096];
    ssize_t bytesRead;

    while((bytesRead = read(fd, buffer, sizeof(buffer))) > 0){
        write(1, buffer, bytesRead);
    }
    printf("\n");
    if(fd != STDIN_FILENO) close(fd);
    return 1;
}