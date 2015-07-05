#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"

char *parser_error = NULL;

enum parser_state {
    ST_INIT,
    ST_LINE,
    ST_REDIRECT_OUT,
    ST_REDIRECT_IN,
    ST_REDIRECT_ERR,
    ST_REDIRECT_OUT_ERR,
    ST_PIPE_TO,
};

int parser_reset(Parser *ctx)
{
    memset(ctx, 0, sizeof (*ctx));

    if (!lexer_reset(&ctx->lex)) {
        return 0;
    }

    ctx->state = ST_INIT;
    ctx->eat_next = 1;
    parser_error = NULL;

    return 1;
}

int parser_feed(Parser *ctx, char *input)
{
    return lexer_feed(&ctx->lex, input);
}

int parser_match(Parser *ctx, Command **cmd)
{
    parser_error = NULL;
    Token *tok = &ctx->cur_tok;

    while (1) {
        if (ctx->eat_next) {
            if (!lexer_match(&ctx->lex, tok)) {
                return 0;
            }
        }

        ctx->eat_next = 1;

        int reset_args = 0;
        int append_arg = 0;
        int start_command = 0;
        int end_command = 0;
        int finalize_sub = 0;

        switch ((enum parser_state) ctx->state) {
        case ST_INIT:
            switch (tok->kind) {
            case TOK_EOF:
                return 0;

            case TOK_COMMENT:
                // Ignore comments outright
                break;

            case TOK_PIPE:
            case TOK_GT:
            case TOK_2GT:
            case TOK_LT:
            case TOK_AMP:
            case TOK_AMP_GT:
                parser_error = "Command cannot begin with an operator";
                return -1;

            case TOK_NEWLINE:
            case TOK_SEMI:
                // Ignore a blank line
                break;

            case TOK_ARG:
                ctx->state = ST_LINE;
                reset_args = 1;
                append_arg = 1;
                start_command = 1;
                break;
            }
            break;

        case ST_LINE:
            switch (tok->kind) {
            case TOK_COMMENT:
                break;

            case TOK_NEWLINE:
            case TOK_SEMI:
            case TOK_EOF:
                ctx->state = ST_INIT;
                finalize_sub = 1;
                end_command = 1;
                break;

            case TOK_ARG:
                append_arg = 1;
                break;

            case TOK_PIPE:
                ctx->state = ST_PIPE_TO;
                finalize_sub = 1;
                reset_args = 1;

                ctx->cmds.cur->pipe_to = ctx->cmds.cur + 1;
                break;

            case TOK_GT:
                ctx->state = ST_REDIRECT_OUT;
                break;

            case TOK_LT:
                ctx->state = ST_REDIRECT_IN;
                break;

            case TOK_2GT:
                ctx->state = ST_REDIRECT_ERR;
                break;

            case TOK_AMP_GT:
                ctx->state = ST_REDIRECT_OUT_ERR;
                break;

            case TOK_AMP:
                parser_error = "The process background operator '&' is not supported";
                return -1;
            }
            break;

        case ST_REDIRECT_OUT:
            switch (tok->kind) {
            case TOK_COMMENT:
                break;

            case TOK_ARG:
                ctx->state = ST_LINE;

                if (ctx->cmds.cur->out_filename != NULL) {
                    free(ctx->cmds.cur->out_filename);
                }

                ctx->cmds.cur->out_filename = strdup(tok->buf);
                break;

            case TOK_EOF:
            case TOK_PIPE:
            case TOK_NEWLINE:
            case TOK_SEMI:
            case TOK_GT:
            case TOK_2GT:
            case TOK_LT:
            case TOK_AMP:
            case TOK_AMP_GT:
                parser_error = "Expecting argument after '>'";
                return -1;
            }
            break;

        case ST_REDIRECT_OUT_ERR:
            switch (tok->kind) {
            case TOK_COMMENT:
                break;

            case TOK_ARG:
                ctx->state = ST_LINE;

                if (ctx->cmds.cur->out_filename != NULL) {
                    free(ctx->cmds.cur->out_filename);
                }

                if (ctx->cmds.cur->err_filename != NULL) {
                    free(ctx->cmds.cur->err_filename);
                }

                // Double `strdup` because they will be individually free'd
                ctx->cmds.cur->out_filename = strdup(tok->buf);
                ctx->cmds.cur->err_filename = strdup(tok->buf);
                break;

            case TOK_EOF:
            case TOK_PIPE:
            case TOK_NEWLINE:
            case TOK_SEMI:
            case TOK_GT:
            case TOK_2GT:
            case TOK_LT:
            case TOK_AMP:
            case TOK_AMP_GT:
                parser_error = "Expecting argument after '>'";
                return -1;
            }
            break;

        case ST_REDIRECT_IN:
            switch (tok->kind) {
            case TOK_COMMENT:
                break;

            case TOK_ARG:
                ctx->state = ST_LINE;

                if (ctx->cmds.cur->in_filename != NULL) {
                    free(ctx->cmds.cur->in_filename);
                }

                ctx->cmds.cur->in_filename = strdup(tok->buf);
                break;

            case TOK_NEWLINE:
            case TOK_SEMI:
            case TOK_EOF:
            case TOK_PIPE:
            case TOK_GT:
            case TOK_2GT:
            case TOK_LT:
            case TOK_AMP:
            case TOK_AMP_GT:
                parser_error = "Expecting argument after '<'";
                return -1;
            }
            break;

        case ST_REDIRECT_ERR:
            switch (tok->kind) {
            case TOK_COMMENT:
                break;

            case TOK_ARG:
                ctx->state = ST_LINE;

                if (ctx->cmds.cur->err_filename != NULL) {
                    free(ctx->cmds.cur->err_filename);
                }

                ctx->cmds.cur->err_filename = strdup(tok->buf);
                break;

            case TOK_NEWLINE:
            case TOK_SEMI:
            case TOK_EOF:
            case TOK_PIPE:
            case TOK_GT:
            case TOK_2GT:
            case TOK_LT:
            case TOK_AMP:
            case TOK_AMP_GT:
                parser_error = "Expecting argument after '2>'";
                return -1;
            }
            break;

        case ST_PIPE_TO:
            switch (tok->kind) {
            case TOK_COMMENT:
                break;

                return -1;

            case TOK_ARG:
                ctx->state = ST_LINE;
                ctx->eat_next = 0;
                break;

            case TOK_EOF:
            case TOK_NEWLINE:
            case TOK_SEMI:
            case TOK_PIPE:
            case TOK_GT:
            case TOK_2GT:
            case TOK_LT:
            case TOK_AMP:
            case TOK_AMP_GT:
                parser_error = "Missing command after '|'";
                return -1;
            }
            break;
        }

        if (finalize_sub) {
            Command *cur_cmd = ctx->cmds.cur;

            int argc = ctx->args.num;
            cur_cmd->argc = argc;

            // Duplicate the `argv` array
            size_t nbytes = (argc + 1) * sizeof (char *);
            cur_cmd->argv = malloc(nbytes);
            assert (cur_cmd->argv != NULL);
            memcpy(cur_cmd->argv, ctx->args.vec, nbytes);

            // Advance to the next sub-command
            ctx->cmds.cur++;
            memset(ctx->cmds.cur, 0, sizeof (*ctx->cmds.cur));
        }

        if (reset_args) {
            ctx->args.cur = ctx->args.vec;
            ctx->args.num = 0;
        }

        if (append_arg) {
            assert (ctx->args.cur < ctx->args.end);

            ctx->args.num++;

            *ctx->args.cur = strdup(tok->buf);
            ctx->args.cur++;
            *ctx->args.cur = (char *) NULL;
        }

        if (start_command) {
            ctx->cmds.cur = ctx->cmds.vec;
            memset(ctx->cmds.cur, 0, sizeof (*ctx->cmds.cur));
        }

        if (end_command) {
            *cmd = &ctx->cmds.vec[0];

            return 1;
        }
    }

    return 0;
}
