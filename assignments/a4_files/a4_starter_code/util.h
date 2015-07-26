#ifndef __UTIL_H
#define __UTIL_H

int parse_command(char *buf, char **command, char **rest);
void strip_trailing_newlines(char *buf);

#endif /* __UTIL_H */
