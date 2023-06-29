#ifndef PL2_DEBUG_H
#define PL2_DEBUG_H

#define PL2_LOG_LVL_ERROR 0
#define PL2_LOG_LVL_WARN 1
#define PL2_LOG_LVL_INFO 2
#define PL2_LOG_LVL_DEBUG 3
#define DEBUG_LVL 3

#include <stdio.h>
#include <errno.h>
#include <string.h>

void  pl2_log(char lvl, const char *scope, const char *message);
void  pl2_error(char lvl, const char *scope, int errnum);

#endif
