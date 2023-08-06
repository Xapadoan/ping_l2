#ifndef PL2_ARGS_H
#define PL2_ARGS_H

#include "ipv4opts.h"
#include "ipv6opts.h"

struct args
{
  char          target[100];
  uint8_t       family;
  int           count;
  char          interface[20];
  unsigned int  size;
  union {
    struct ipv4opts v4;
    struct ipv6opts v6;
  } ipopts;
  unsigned int  deadline;
  unsigned int  timeout;
  unsigned int  interval;
};

#endif
