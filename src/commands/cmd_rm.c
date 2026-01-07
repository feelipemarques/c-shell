#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int cmd_rm(int argc, char **argv){

    for(int i = 1; i < argc; i++){
        if(unlink(argv[i]) < 0){
            perror("rm");
        }
    }

    return 1;
}