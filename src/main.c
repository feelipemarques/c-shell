#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include "../include/commands.h"
#include "../include/operators.h"
#include "executor.c"
#include "operator.c"

int main(){

    RedirectInfo redirect;
    redirect.type = REDIRECT_NONE;
    redirect.filename = NULL;
    
    Commands parent_commands[] = {
        {"exit", cmd_exit},
        {"cd", cmd_cd}
    };

    Commands child_commands[] = {
        {"help", cmd_help},
        {"version", cmd_version},
        {"clear", cmd_clear},
        {"echo", cmd_echo},
        {"pwd", cmd_pwd},
        {"ls", cmd_ls},
        {"mkdir", cmd_mkdir},
        {"rmdir", cmd_rmdir},
        {"cp", cmd_cp},
        {"touch", cmd_touch},
        {"cat", cmd_cat},
        {"rm", cmd_rm}
    };

    CommandRange range[] = {};

    int commands_len = sizeof(child_commands) / sizeof(child_commands[0]);
    int running = 1;

    while(running){
        char input[1024];
        printf("myshell> $ ");
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



        if(!validate_operators(&argc, argv, &redirect)){
            continue;
        }

        if(argc == 0){
            continue;
        }

        int handled_by_parent = 0;

        for(int i = 0; i < sizeof(parent_commands) / sizeof(parent_commands[0]); i++){
            if(strcmp(argv[0], parent_commands[i].name) == 0){
                running = parent_commands[i].action(argc, argv);
                handled_by_parent = 1;
                break;
            }
        }
        if(handled_by_parent){
            continue;
        }

        pid_t pid = fork();
        
        if(pid < 0){
            perror("fork");
            exit(1);
        }
        if(pid == 0){
            execute_command(argc, argv, redirect, child_commands, commands_len);
        }
        else{
            waitpid(pid, NULL, 0);
        }
    }
}

