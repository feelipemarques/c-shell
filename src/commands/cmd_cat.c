#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int cmd_cat(int argc, char **argv){
    int src = open(argv[1], O_RDONLY);

    if(src < 0){
        perror("cat: error reading file");
        return 1;
    }
    char buffer[4096];
    ssize_t bytesRead;

    while((bytesRead = read(src, buffer, sizeof(buffer))) > 0){
        write(1, buffer, bytesRead);
    }
    printf("\n");
    close(src);
    return 1;
}