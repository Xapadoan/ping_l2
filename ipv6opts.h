#ifndef PL2_IPV6OPTS_H
#define PL2_IPV6OPTS_H

#include <stdint.h>

struct ipv6opts
{
  uint8_t       tc;
  uint32_t      flow;
  unsigned int  plen;
  uint8_t       hop;
};

#endif
