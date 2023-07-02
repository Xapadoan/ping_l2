#ifndef PL2_DEBUG_H
#define PL2_DEBUG_H

#define PL2_LOG_LVL_ERROR 0
#define PL2_LOG_LVL_WARN 1
#define PL2_LOG_LVL_INFO 2
#define PL2_LOG_LVL_DEBUG 3
#define DEBUG_LVL 3

#include <stdio.h>

#define debug(...) (DEBUG_LVL >= PL2_LOG_LVL_DEBUG ? printf(__VA_ARGS__) : (void)0)
#define info(...) (DEBUG_LVL >= PL2_LOG_LVL_INFO ? printf(__VA_ARGS__) : (void)0)
#define warn(...) (DEBUG_LVL >= PL2_LOG_LVL_WARN ? printf(__VA_ARGS__) : (void)0)
#define error(...) (DEBUG_LVL >= PL2_LOG_LVL_ERROR ? printf(__VA_ARGS__) : (void)0)

#endif
