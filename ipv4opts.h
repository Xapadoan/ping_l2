#ifndef PL2_IPV4OPTS_H
#define PL2_IPV4OPTS_H

#include <stdint.h>

struct ipv4opts
{
  uint8_t       tos;
  uint8_t       ttl;
  unsigned int  len;
  uint8_t       record;
};

#endif
