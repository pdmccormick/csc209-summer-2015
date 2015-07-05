#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>

#include "parser.h"
#include "command.h"
#include "execute.h"

static int run_interactive(Parser *pares);
static int run_file(Parser *parser, int fd, char *filename);
static int run_string(Parser *parser, char *input);
static int handle_command(Command *cmd);

int main(int argc, char *argv[])
{
    int rc;
    char *cmd = NULL;
    int cmd_flag = 0;

    int opt;
    while ((opt = getopt(argc, argv, "c:")) != -1) {
        switch (opt) {
        case 'c':
            cmd_flag = 1;
            cmd = optarg;
            break;

        default:
            fprintf(stderr, "usage: %s [-c cmd | file]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    Parser parser;

    if (cmd_flag) {
        rc = run_string(&parser, cmd);

        if (rc < 0) {
            printf("ERROR (pos %d): %s\n", parser.lex.column, parser_error);
        }

        return rc;
    }
    else if (optind >= argc) {
        // Only run interactively if there is a TTY
        if (isatty(STDIN_FILENO) == 1) {
            return run_interactive(&parser);
        }
        else {
            return run_file(&parser, STDIN_FILENO, "<stdin>");
        }
    }

    // Attempt to open file
    char *filename = argv[optind];
    int fd = open(filename, O_RDONLY);

    if (fd < 0) {
        perror(filename);
        return EXIT_FAILURE;
    }

    rc = run_file(&parser, fd, filename);

    close(fd);

    return rc;

}

static int run_interactive(Parser *parser)
{
	char cwd[PATH_MAX];
    char prompt_suffix[] = "> ";
    char prompt[PATH_MAX + sizeof (prompt_suffix) + 1];

	while (!feof(stdin)) {
        getcwd(cwd, sizeof (cwd));

        snprintf(prompt, sizeof (prompt), "%s%s", cwd, prompt_suffix);

        char *line = readline(prompt);

        if (line == NULL) {
            break;
        }

        int rc = run_string(parser, line);
        if (rc) {
            printf("ERROR (pos %d): %s\n", parser->lex.column, parser_error);
        }
	}

    return EXIT_SUCCESS;
}

static int run_file(Parser *parser, int fd, char *filename)
{
    char buf[1024];

    parser_reset(parser);

    while (1) {
        ssize_t bytes_read = read(fd, buf, sizeof (buf) - 1);

        if (bytes_read < 0) {
            perror("read");
            return -2;
        }

        if (bytes_read == 0) {
            // EOF encountered
            char eof_input[] = { EOF, '\0' };
            parser_feed(parser, eof_input);
        }
        else {
            buf[bytes_read] = '\0';
            parser_feed(parser, buf);
        }

        Command *cmd;
        int rc;
        while ((rc = parser_match(parser, &cmd)) == 1) {
            if ((rc = handle_command(cmd))) {
                return rc;
            }
        }

        if (rc) {
            fprintf(stderr, "%s: line %d: %s\n", filename, parser->lex.line + 1, parser_error);

            return rc;
        }

        if (bytes_read == 0) {
            break;
        }
    }

    return EXIT_SUCCESS;
}

static int run_string(Parser *parser, char *input)
{
    char eof_input[] = { EOF, '\0' };

    int i;
    for (i = 0; i < 2; i++) {
        switch (i) {
        case 0:
            parser_reset(parser);
            parser_feed(parser, input);
            break;

        case 1:
            parser_feed(parser, eof_input);
            break;
        }

        Command *cmd;
        int rc;
        while ((rc = parser_match(parser, &cmd)) == 1) {
            if ((rc = handle_command(cmd))) {
                return rc;
            }
        }

        if (rc < 0) {
            return rc;
        }
    }

    return 0;
}

static int handle_command(Command *cmd)
{
    int rc = 0;

    rc = execute_command(cmd);

    if (rc) {
        fprintf(stderr, "execute_command() returned %d\n", rc);
    }

    command_cleanup(cmd);

    return 0;
}
