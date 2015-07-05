#ifndef __EXECUTE_H
#define __EXECUTE_H

#include "command.h"

/**
 * Execute a Command (with or without pipes.)
 */
int execute_command(Command *cmd);

#endif /* __EXECUTE_H */
