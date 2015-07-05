#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.h"
#include "command.h"

extern char *parser_error;

typedef struct {
    int state;

    Lexer lex;
    Token cur_tok;
    int eat_next;

    struct {
        char *vec[64];
        char *end[0];

        int num;
        char **cur;
    } args;

    struct {
        Command vec[64];
        Command end[0];

        int num;
        Command *cur;
    } cmds;
} Parser;

int parser_reset(Parser *ctx);
int parser_feed(Parser *ctx, char *input);
int parser_match(Parser *ctx, Command **cmd);

#endif /* __PARSER_H */
