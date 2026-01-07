#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include "../include/commands.h"
#include "../include/operators.h"


int is_operator(const char *token);
int validate_operators(int argc, char **argv);

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
        {"cp", cmd_cp},
        {"touch", cmd_touch},
        {"cat", cmd_cat},
        {"rm", cmd_rm}
    };

    int found = 0;
    int running = 1;
    int operators = 0;

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
        
        if(!validate_operators(argc, argv)){
            continue;
        }

        if(argc == 0){
            continue;
        }

        for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
            if(strcmp(argv[0], commands[i].name) == 0){
                found = 1;
                running = commands[i].action(argc, argv);
                break;
            }
        }

        if(found == 0){
            pid_t pid = fork();
            if(pid < 0){
                perror("fork");
            }
            if(pid == 0){
                execvp(argv[0], argv);
                perror("exec");
                exit(1);
            }
            else{
                waitpid(pid, NULL, 0);
            }
            
        }

        found = 0;
    }
}

int is_operator(const char *token){
    for(int i = 0; OPERATORS[i] != NULL; i++){
        if(strcmp(token, OPERATORS[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int validate_operators(int argc, char **argv){
    int operators = 0;

    for(int i = 0; i < argc; i++){
        if(is_operator(argv[i]) == 1){
            if(i == 0 || i == (argc - 1) || operators > 0){
                printf("Syntax error!");
                return 0;
            }
            operators = 1;
        
        }
    }
    return 1;
}