#ifndef __SIGNAL2STR_H
#define __SIGNAL2STR_H

#include <stdio.h>
#include <signal.h>

static const char *signal2str(int signum);

static const char *signal2str(int signum)
{
#   define SIGNAL2STR_DEF(id)  [SIG ## id] = #id
    static char *num2str[] = {
        SIGNAL2STR_DEF(HUP),
        SIGNAL2STR_DEF(INT),
        SIGNAL2STR_DEF(QUIT),
        SIGNAL2STR_DEF(ILL),
        SIGNAL2STR_DEF(TRAP),
        SIGNAL2STR_DEF(ABRT),
        SIGNAL2STR_DEF(BUS),
        SIGNAL2STR_DEF(FPE),
        SIGNAL2STR_DEF(KILL),
        SIGNAL2STR_DEF(USR1),
        SIGNAL2STR_DEF(SEGV),
        SIGNAL2STR_DEF(USR2),
        SIGNAL2STR_DEF(PIPE),
        SIGNAL2STR_DEF(ALRM),
        SIGNAL2STR_DEF(TERM),
        SIGNAL2STR_DEF(CHLD),
        SIGNAL2STR_DEF(CONT),
        SIGNAL2STR_DEF(STOP),
        SIGNAL2STR_DEF(TSTP),
        SIGNAL2STR_DEF(TTIN),
        SIGNAL2STR_DEF(TTOU),
        SIGNAL2STR_DEF(URG),
        SIGNAL2STR_DEF(XCPU),
        SIGNAL2STR_DEF(XFSZ),
        SIGNAL2STR_DEF(VTALRM),
        SIGNAL2STR_DEF(PROF),
        SIGNAL2STR_DEF(WINCH),
        SIGNAL2STR_DEF(SYS),
        SIGNAL2STR_DEF(INFO),

#       ifdef __linux__
        SIGNAL2STR_DEF(STKFLT),
        SIGNAL2STR_DEF(POLL),
        SIGNAL2STR_DEF(PWR),
#       endif
    };

    const int len = sizeof (num2str) / sizeof (num2str[0]);

    if (!(0 < signum && signum < len) || !num2str[signum]) {
        return "???";
    }

    return num2str[signum];
}

#endif /* __SIGNAL2STR_H */
