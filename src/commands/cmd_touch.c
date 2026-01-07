#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int cmd_touch(int argc, char **argv){
    for(int i = 1; i < argc; i++){
        int new = open(argv[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if(new < 0){
            perror("touch: error creating file");
        }
        close(new);
    }
    return 1;
}