#ifndef __COMMAND_H
#define __COMMAND_H

typedef struct _command Command;

struct _command {
    /** Argument count */
    int argc;

    /** Argument vector (NULL-terminated array) */
    char **argv;

    /** Filename to redirect STDIN from */
    char *in_filename;

    /** Filename to redirect STDOUT to */
    char *out_filename;

    /** Filename to redirect STDERR to */
    char *err_filename;

    /** Pipe the STDOUT of this command to the STDIN of the `pipe_to` command */
    Command *pipe_to;
};

/**
 * Print out the contents of this command.
 */
void command_dump(Command *cmd);

/**
 * Release resources associated with this command.
 */
void command_cleanup(Command *cmd);

#endif /* __COMMAND_H */
