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
        {"mkdir", cmd_mkdir},
        {"rmdir", cmd_rmdir},
        {"cp", cmd_cp}
    };

    int found = 0;
    int running = 1;

    while(running){
        char input[1024];
        printf("myshell> ");
        fgets(input, sizeof(input), stdin);
        
        input[strcspn(input, "\n")] = '\0'; // Transforma o '\n' (quebra de linha) em um '\0'

        char *argv[10];
        int argc = 0;
        char *start = input;
        char *p = input;

        while(*p != '\0' && argc < 10){
            if(*p == ' '){
                *p = '\0';
                argv[argc++] = start;
                start = p + 1;
            }
            p++; 
        }

        if (*start != '\0' && argc < 9) {
            argv[argc++] = start;
        }

        argv[argc] = NULL;

        for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
            if(strcmp(argv[0], commands[i].name) == 0){
                found++;
                running = commands[i].action(argc, argv);
            }
        }

        if(found == 0){
            printf("Command not found! Try 'help'!\n");
        }

        found = 0;
    }
}