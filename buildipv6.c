#include "buildipv6.h"
#include "putsockaddr.h"

void  buildipv6(uint8_t *packet, uint8_t src[16], uint8_t dst[16], uint16_t payload_len)
{
  const uint8_t       v = 6;
  const uint8_t       tc = 0;
  const uint32_t      flow = 0;
  struct pl2_ipv6hdr  *hdr;


  hdr = (struct pl2_ipv6hdr*)packet;
  hdr->start[0] = (v << 4 & 0xf0) | (tc >> 4 & 0x0f);
  hdr->start[1] = (tc << 4 & 0xf0) | (flow >> 16 & 0x0000f);
  hdr->start[2] = flow >> 8 & 0x000ff;
  hdr->start[3] = flow & 0x000ff;
  hdr->len = htons(payload_len);
  hdr->next = IPPROTO_ICMPV6;
  hdr->hop = 255;
  printf("bld:\n");
  memcpy(&(hdr->src), src, 16);
  memcpy(&(hdr->dst), dst, 16);
  int i = 0;
  while (i < 16)
  {
    printf("%02x", dst[i]);
    i++;
  }
}
