#include "buildipv6.h"

void  buildipv6(uint8_t *packet, uint8_t src[16], uint8_t dst[16], struct ipv6opts *opts)
{
  const uint8_t       v = 6;
  struct pl2_ipv6hdr  *hdr;


  hdr = (struct pl2_ipv6hdr*)packet;
  hdr->start[0] = (v << 4 & 0xf0) | (opts->tc >> 4 & 0x0f);
  hdr->start[1] = (opts->tc << 4 & 0xf0) | (opts->flow >> 16 & 0x0000f);
  hdr->start[2] = opts->flow >> 8 & 0x000ff;
  hdr->start[3] = opts->flow & 0x000ff;
  hdr->len = htons(opts->plen);
  hdr->next = IPPROTO_ICMPV6;
  hdr->hop = opts->hop;
  memcpy(&(hdr->src), src, 16);
  memcpy(&(hdr->dst), dst, 16);
}
