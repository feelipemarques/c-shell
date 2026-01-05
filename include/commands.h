#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct command {
    char name[16];
    int (*action)(char *);
} Commands;

int cmd_exit(char *input);
int cmd_help(char *input);
int cmd_version(char *input);
int cmd_clear(char *input);
int cmd_echo(char *input);
int cmd_cd(char *input);
int cmd_pwd(char *input);
int cmd_ls(char *input);
int cmd_mkdir(char *input);
int cmd_rmdir(char *input);

#endif