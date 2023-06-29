#include "debug.h"

void  pl2_error(char lvl, const char *scope, int errnum)
{
  if (lvl == PL2_LOG_LVL_ERROR)
    printf("[ERROR] [%s]: %s\n", scope, strerror(errnum));
  else if (lvl == PL2_LOG_LVL_WARN && DEBUG_LVL >= PL2_LOG_LVL_WARN)
    printf("[WARNING] [%s]: %s\n", scope, strerror(errnum));
}

void pl2_log(char lvl, const char *scope, const char *message)
{
  if (lvl == PL2_LOG_LVL_INFO && DEBUG_LVL >= PL2_LOG_LVL_INFO)
    printf("[INFO] [%s]: %s\n", scope, message);
  else if (lvl == PL2_LOG_LVL_DEBUG && DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
    printf("[DEBUG] [%s]: %s\n", scope, message);
}
