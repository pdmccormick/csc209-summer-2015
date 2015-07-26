#include <stdio.h>
#include <string.h>

#include "util.h"

/**
 * Split "/command args" formatted strings, extracting the pieces into
 * `*command` and `*rest`.
 *
 * Returns 1 (true) if `buf` is a command string, otherwise 0 (false).
 */
int parse_command(char *buf, char **command, char **rest)
{
    char *start = buf;

    /*
     * Ignore any leading spaces:
     *
     *   buf  : "   /command foobar"
     *   start:    "/command foobar"
     */
    while (*start == ' ') {
        start++;
    }

    /*
     * If, after any spaces, we don't see a '/', then this isn't a command
     *
     *   buf  : "   hello world!"
     *   start:    "hello world!"
     *
     * Conclusion: This isn't a command...
     */
    if (start[0] != '/') {
        return 0;
    }

    /*
     *   buf     : "   /command foobar"
     *   start   :    "/command foobar"
     *   *command:     "command foobar"
     */
    *command = start + 1;

    /*
     *   buf     : "   /command foobar"
     *   start   :    "/command foobar"
     *   *command:     "command foobar"
     *   delim   :            " foobar"
     */
    char *delim = strchr(start, ' ');


    if (delim == NULL) {
        /*
         * If there is no space after command, then the `rest` is an empty string
         *
         *   buf     : "   /command"
         *   start   :    "/command"
         *   *command:     "command"
         *   *rest   :            ""
         */
        *rest = strchr(start, '\0');
    }
    else {
        /*
         * There is at least one space after the command.
         *
         *   buf     : "   /command foo"
         *   start   :    "/command foo"
         *   *command:     "command foo"
         *   delim   :            " foo"
         */

        /*
         * NUL terminate `command`.
         *
         * Before:
         *   *command: "command    baz foo"
         *
         * After:
         *   *command: "command"
         *   delim   :         "   baz foo"
         */
        delim[0] = '\0';
        delim++;

        /*
         * Remove an extra delimiting spaces.
         *
         *   *command: "command"
         *   delim   :            "baz foo"
         */
        while (*delim == ' ') {
            delim++;
        }

        *rest = delim;
    }

    return 1;
}


void strip_trailing_newlines(char *buf)
{
    // `end` points to the last non-NULL character in the buffer
    char *end = buf + strlen(buf) - 1;
    char *cur = end;

    /* While there are newline characters at the end of the buffer, shorten the
     * string by stripping them off */
    while (cur >= buf) {
        if (*cur == '\n' || *cur == '\r') {
            *cur = '\0';
        }
        else {
            break;
        }

        cur--;
    }
}
