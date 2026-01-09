#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/commands.h"
#include "../include/operators.h"

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

    CommandRange ranges[10];
    int num_cmds = 0;
    int commands_len = sizeof(child_commands) / sizeof(child_commands[0]);
    int running = 1;

    while(running){
        char *input = readline("myshell> $ ");
        char *argv[10];
        int argc = 0;
        char *cmd_argv[10];

        if (input == NULL) {
            printf("\n");
            break;
        }
        if (*input == '\0') {
            free(input);
            continue;
        }   
        add_history(input);
        parse_input(input, &argc, argv);

        if(!validate_pipe(&argc, argv, ranges, &num_cmds)){ continue; }

        int pipes[num_cmds - 1][2];

        for(int i = 0; i < num_cmds - 1; i++){
            if(pipe(pipes[i]) < 0){
                perror("pipe");
                continue;
            }
        }

        for(int i = 0; i < num_cmds; i++){
            int start = ranges[i].start;
            int end   = ranges[i].end;
            int cmd_argc = 0;

            for (int j = start; j <= end; j++) {
                cmd_argv[cmd_argc++] = argv[j];
            }

            cmd_argv[cmd_argc] = NULL;

            redirect.type = REDIRECT_NONE;
            redirect.filename = NULL;

            if(!validate_operators(&cmd_argc, cmd_argv, &redirect)){ continue; }
            if(argc == 0){ continue; }

            int handled_by_parent = 0;

            for(int i = 0; i < sizeof(parent_commands) / sizeof(parent_commands[0]); i++){
                if(strcmp(cmd_argv[0], parent_commands[i].name) == 0){
                    running = parent_commands[i].action(cmd_argc, cmd_argv);
                    handled_by_parent = 1;
                    break;
                }
            }
            if(handled_by_parent){ continue; }

            pid_t pid = fork();
            
            if(pid < 0){
                perror("fork");
                exit(1);
            }
            if(pid == 0){ 
                if (i > 0) { dup2(pipes[i - 1][0], STDIN_FILENO); }
                if (i < num_cmds - 1) { dup2(pipes[i][1], STDOUT_FILENO); }
                
                for (int j = 0; j < num_cmds - 1; j++) {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }

                execute_command(cmd_argc, cmd_argv, redirect, child_commands, commands_len); 
                exit(1);
            }
        }
        for (int i = 0; i < num_cmds - 1; i++) {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        for (int i = 0; i < num_cmds; i++) { wait(NULL); }
        free(input);
    }
}