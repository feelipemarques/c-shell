#include <stdio.h>
#include <dirent.h>
#include "commands.h"

int cmd_ls(int argc, char **argv){
    DIR *dir;
    struct dirent *entry;

    if(argv[1] == NULL){
        dir = opendir(".");
    }else{
        dir = opendir(argv[0]);
    }

    if(dir == NULL){
        printf("ls: cannot open directory\n");
    }

    while((entry = readdir(dir)) != NULL){
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 1;
}