#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int cmd_cp(int argc, char **argv){
    int src = open(argv[1], 0);
    int dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if(src < 0 || dest < 0){
        perror("cp: error opening file");
        return -1;
    }

    char buffer[4096];
    ssize_t bytesRead;

    while((bytesRead = read(src, buffer, sizeof(buffer))) > 0){
       write(dest, buffer, bytesRead);
    }

    if(bytesRead < 0){
        perror("cp: error reading source file");
        close(src);
        close(dest);
        return -1;
    }

    close(src);
    close(dest);

    return 1;
}