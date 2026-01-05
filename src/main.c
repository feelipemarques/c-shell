#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "../include/commands.h"

int main(){
    
    Commands commands[] = {
        {"exit", cmd_exit},
        {"help", cmd_help},
        {"version", cmd_version},
        {"clear", cmd_clear},
        {"echo", cmd_echo},
        {"pwd", cmd_pwd},
        {"cd", cmd_cd},
        {"ls", cmd_ls},
        {"mkdir", cmd_mkdir}
    };

    int found = 0;
    int running = 1;

    while(running){
        char input[1024];
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);
        
        input[strcspn(input, "\n")] = '\0';

        char *ptr = strchr(input, ' ');
        char *command_name;
        char *args;

        if(ptr == NULL){
            command_name = input;
            args = NULL;
        }else{
            *ptr = '\0';
            command_name = input;
            args = ptr + 1;
        }  

        for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
            if(strcmp(command_name, commands[i].name) == 0){
                found++;
                running = commands[i].action(args);
            }
        }

        if(found == 0){
            printf("Command not found! Try 'help'!\n");
        }

        found = 0;
    }
}