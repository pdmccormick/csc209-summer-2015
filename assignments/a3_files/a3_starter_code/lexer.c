#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"

/** The lexer is implemented as a small state machine, and these are the possible states
 * it can be in.
 *
 * The `state` field of type `Lexer` will be assigned these values.
 */
enum lexer_state {
    ST_INIT,
    ST_COMMENT,
    ST_BAREWORD,
    ST_STRING,
    ST_STRING_DQ,
    ST_MAYBE_2GT,
    ST_MAYBE_AMP_GT,
};

int lexer_reset(Lexer *ctx)
{
    if (!ctx) {
        return 0;
    }

    // Zero everything out
    memset(ctx, 0, sizeof (*ctx));

    ctx->state = ST_INIT;

    return 1;
}

int lexer_feed(Lexer *ctx, char *input)
{
    if (!ctx) {
        return 0;
    }

    // Mark the beginning and end of this input
    ctx->begin = ctx->cur = input;
    ctx->end = input + strlen(input);

    return 1;
}

int lexer_match(Lexer *ctx, Token *tok)
{
    // Stop matching once we've reached the end
    if (ctx->begin >= ctx->end) {
        return 0;
    }

    // Scan through the current buffer
    while (ctx->cur < ctx->end) {
        char ch = *ctx->cur;
        enum token_kind kind = -1;

        int start_token = 0;
        int end_token = 0;
        int append_token = 0;
        int eat_cur = 1;

        switch ((enum lexer_state) ctx->state) {
        case ST_INIT:
            switch (ch) {
            case EOF:
                kind = TOK_EOF;
                start_token = end_token = 1;
                break;

            case ' ': case '\t':
                // Silently eat through initial leading whitespace
                break;

            case '#':
                ctx->state = ST_COMMENT;
                kind = TOK_COMMENT;
                start_token = 1;
                append_token = 0;
                break;

            case '\n':
                kind = TOK_NEWLINE;
                start_token = append_token = end_token = 1;
                break;

            case ';':
                kind = TOK_SEMI;
                start_token = append_token = end_token = 1;
                break;

            case '|':
                kind = TOK_PIPE;
                start_token = append_token = end_token = 1;
                break;

            case '<':
                kind = TOK_LT;
                start_token = append_token = end_token = 1;
                break;

            case '>':
                kind = TOK_GT;
                start_token = append_token = end_token = 1;
                break;

            case '"':
                ctx->state = ST_STRING_DQ;
                kind = TOK_ARG;
                start_token = 1;
                append_token = 0;
                break;

            case '\'':
                ctx->state = ST_STRING;
                kind = TOK_ARG;
                start_token = 1;
                append_token = 0;
                break;

            case '2':
                // Either a bareword or the start of '2>'
                ctx->state = ST_MAYBE_2GT;
                kind = TOK_2GT;
                start_token = 1;
                append_token = 1;
                break;

            case '&':
                ctx->state = ST_MAYBE_AMP_GT;
                kind = TOK_AMP_GT;
                start_token = 1;
                append_token = 1;
                break;

            default:
                ctx->state = ST_BAREWORD;
                kind = TOK_ARG;
                start_token = append_token = 1;
                break;
            }
            break;

        case ST_COMMENT:
            switch (ch) {
            case '\n':
                ctx->state = ST_INIT;
                end_token = 1;
                eat_cur = 0;
                break;

            case EOF:
                ctx->state = ST_INIT;
                kind = TOK_EOF;
                end_token = 1;
                break;

            default:
                // Ignore everything up to and including the newline
                append_token = 1;
                break;
            }
            break;

        case ST_BAREWORD:
            switch (ch) {
            case ' ': case '\t':
            case '\n':
            case EOF:
                ctx->state = ST_INIT;
                eat_cur = 0;
                end_token = 1;
                break;

            case ';':
            case '|':
            case '<':
            case '>':
                ctx->state = ST_INIT;
                end_token = 1;
                eat_cur = 0;
                break;

            default:
                append_token = 1;
            }
            break;

        case ST_STRING:
            switch (ch) {
            case '\'':
                ctx->state = ST_INIT;
                append_token = 0;
                end_token = 1;
                break;

            default:
                append_token = 1;
                break;
            }
            break;

        case ST_STRING_DQ:
            switch (ch) {
            case '"':
                ctx->state = ST_INIT;
                append_token = 0;
                end_token = 1;
                break;

            default:
                append_token = 1;
                break;
            }
            break;

        case ST_MAYBE_2GT:
            switch (ch) {
            case '>':
                ctx->state = ST_INIT;
                append_token = 1;
                end_token = 1;
                break;

            default:
                // Wasn't "2>" after all...
                ctx->state = ST_BAREWORD;
                kind = TOK_ARG;
            }
            break;

        case ST_MAYBE_AMP_GT:
            switch (ch) {
            case '>':
                ctx->state = ST_INIT;
                append_token = 1;
                end_token = 1;
                break;

            default:
                // Wasn't "2>" after all...
                ctx->state = ST_INIT;

                tok->kind = TOK_AMP;
                end_token = 1;
                eat_cur = 0;
            }
            break;
        }

        if (start_token) {
            tok->kind = kind;
            tok->line = ctx->line;
            tok->column = ctx->column;
            tok->buf = ctx->token.buf;

            // Setup scratch buffer
            ctx->token.stop = ctx->token.buf;
            *ctx->token.stop = '\0';
        }

        if (append_token) {
            assert (ctx->token.stop < ctx->token.end);

            *ctx->token.stop = ch;
            ctx->token.stop++;
            *ctx->token.stop = '\0';
        }

        if (*ctx->cur == '\n') {
            ctx->line++;
            ctx->column = 0;
        }
        else {
            ctx->column++;
        }

        if (eat_cur) {
            ctx->cur++;
        }

        if (end_token) {
            return 1;
        }
    }

    return 0;
}
