#include <stdio.h>
#include "../include/commands.h"
#include <unistd.h>
#include <fcntl.h>

void execute_command(int argc, char **argv, RedirectInfo redirect, Commands *commands, int commands_len){

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
    for(int i = 0; i < commands_len; i++){
        if(strcmp(argv[0], commands[i].name) == 0){
            commands[i].action(argc, argv);
            exit(0);
        }
    }
    execvp(argv[0], argv);
    close(fd);
    perror("exec");
    exit(1);
}