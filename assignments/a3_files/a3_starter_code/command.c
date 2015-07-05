#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

static void maybe_quote(char *arg)
{
    // FIXME What if `arg` contains a single or double quote?

    if (strchr(arg, ' ')) {
        printf("\"%s\"", arg);
    }
    else {
        printf("%s", arg);
    }
}

void command_dump(Command *cmd)
{
    int i;
    for (i = 0; i < cmd->argc; i++) {
        maybe_quote(cmd->argv[i]);
        printf(" ");
    }

    if (cmd->out_filename) {
        printf("> %s ", cmd->out_filename);
    }

    if (cmd->err_filename) {
        printf("2> %s ", cmd->err_filename);
    }

    if (cmd->in_filename) {
        printf("< %s ", cmd->in_filename);
    }

    if (cmd->pipe_to) {
        printf("| ");
        command_dump(cmd->pipe_to);
    }
    else {
        printf("\n");
    }
}

void command_cleanup(Command *cmd)
{
    if (cmd == NULL) {
        return;
    }

    // Free all `argv` entries
    char **cur = cmd->argv;

    while (*cur) {
        free(*cur);
        cur++;
    }

    free(cmd->argv);

    if (cmd->in_filename) {
        free(cmd->in_filename);
    }

    if (cmd->out_filename) {
        free(cmd->out_filename);
    }

    if (cmd->err_filename) {
        free(cmd->err_filename);
    }

    if (cmd->pipe_to) {
        command_cleanup(cmd->pipe_to);
    }
}
