#ifndef PL2_BUILDIPV6_H
#define PL2_BUILDIPV6_H

#include <arpa/inet.h>
#include <string.h>
#include <stdint.h>

struct pl2_ipv6hdr
{
  uint8_t   start[4];
  uint16_t  len;
  uint8_t   next;
  uint8_t   hop;
  uint8_t   src[16];
  uint8_t   dst[16];
};

void  buildipv6(uint8_t *packet, uint8_t src[16], uint8_t dst[16], uint16_t payload_len);

#endif
