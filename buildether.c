#include "buildether.h"

void  buildether(uint8_t *buffer, const uint8_t *src, const uint8_t *dst, uint16_t proto)
{
  struct ethhdr *hdr;

  hdr = (struct ethhdr *)buffer;
  memcpy(hdr->h_source, src, ETH_ALEN);
  memcpy(hdr->h_dest, dst, ETH_ALEN);
  hdr->h_proto = htons(proto);
}
