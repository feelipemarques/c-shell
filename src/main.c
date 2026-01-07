#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include "../include/commands.h"
#include "../include/operators.h"


int is_operator(const char *token);
int validate_operators(int *argc, char **argv, RedirectInfo *redirect);

int main(){

    RedirectInfo redirect;
    redirect.type = REDIRECT_NONE;
    redirect.filename = NULL;
    
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

        pid_t pid = fork();
        
        if(pid < 0){
            perror("fork");
            exit(1);
        }
        if(pid == 0){
            int fd = -1;
            if(redirect.type == REDIRECT_IN){
                fd = open(redirect.filename, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                close(fd);
            }else if(redirect.type == REDIRECT_OUT){
                fd = open(redirect.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }else if(redirect.type == REDIRECT_APPEND){
                fd = open(redirect.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }else if(redirect.type == REDIRECT_HEREDOC){
                int pipefd[2];
                pipe(pipefd);

                char *line = NULL;
                size_t len = 0;
                ssize_t read_bytes;

                while(1){
                    printf("> ");
                    read_bytes = getline(&line, &len, stdin);
                    if(read_bytes <= 0) break;
                    line[read_bytes - 1] = '\0';

                    if(strcmp(line, redirect.heredoc_find) == 0){
                        break;
                    }

                    write(pipefd[1], line, strlen(line));
                    write(pipefd[1], "\n", 1);
                }
                free(line);

                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
            }
            for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
                if(strcmp(argv[0], commands[i].name) == 0){
                    running = commands[i].action(argc, argv);
                    exit(0);
                }
            }
            execvp(argv[0], argv);
            close(fd);
            perror("exec");
            exit(1);
        }
        else{
            waitpid(pid, NULL, 0);
        }
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

int validate_operators(int *argc, char **argv, RedirectInfo *redirect){
    int operator_index = -1;

    for(int i = 0; i < *argc; i++){
        if(is_operator(argv[i]) == 1){
            if(i == 0 || i == (*argc - 1) || operator_index != -1){
                printf("Syntax error!");
                return 0;
            }
            operator_index = i;

            if(strcmp(argv[i], ">") == 0){
                redirect->type = REDIRECT_OUT;
                redirect->filename = argv[i + 1];
            } else if(strcmp(argv[i], "<") == 0){
                redirect->type = REDIRECT_IN;
                redirect->filename = argv[i + 1];
            } else if(strcmp(argv[i], ">>") == 0){
                redirect->type = REDIRECT_APPEND;
                redirect->filename = argv[i + 1];
            } else if(strcmp(argv[i], "<<") == 0){
                redirect->type = REDIRECT_HEREDOC;
                redirect->heredoc_find = argv[i + 1];
            } 
            
            break;
        }
    }

    if(operator_index == -1){
        redirect->type = REDIRECT_NONE;
        redirect->filename = NULL;
        return 1;
    }

    for(int j = operator_index; j < *argc -2; j++){
        argv[j] = argv[j + 2];
    }

    *argc -= 2;
    argv[*argc] = NULL;

    return 1;
}