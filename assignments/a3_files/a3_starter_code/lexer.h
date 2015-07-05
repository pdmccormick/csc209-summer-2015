#ifndef __LEXER_H
#define __LEXER_H

typedef struct {
    int state;

    char *begin;
    char *cur;
    char *end;

    int line;
    int column;

    struct {
        char buf[128];
        char end[1];
        char *stop;
    } token;
} Lexer;

enum token_kind {
    TOK_ARG     = 1,

    TOK_NEWLINE,

    TOK_SEMI,
    TOK_PIPE,
    TOK_LT,
    TOK_GT,
    TOK_2GT,
    TOK_AMP,
    TOK_AMP_GT,

    TOK_COMMENT,

    TOK_EOF,
};

typedef struct {
    enum token_kind kind;

    int line;
    int column;
    char *buf;
} Token;

int lexer_reset(Lexer *ctx);
int lexer_feed(Lexer *ctx, char *input);
int lexer_match(Lexer *ctx, Token *tok);

#endif /* __LEXER_H */
