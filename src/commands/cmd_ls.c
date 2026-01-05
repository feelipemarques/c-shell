#include <stdio.h>
#include <dirent.h>
#include "commands.h"

int cmd_ls(char *input){
    DIR *dir;
    struct dirent *entry;

    if(input == NULL){
        dir = opendir(".");
    }else{
        dir = opendir(input);
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