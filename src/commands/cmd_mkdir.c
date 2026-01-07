#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "commands.h"

int cmd_mkdir(int argc, char **argv){
    if(argv[1] == NULL){
        printf("mkdir: dir name cannot be null\n");
        return 1;
    }
    mkdir(argv[1], 0644);
    return 1;
}