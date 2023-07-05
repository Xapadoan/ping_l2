#include "buildip.h"

void  buildip(uint8_t *packet, uint32_t src, uint32_t dst, int payload_size)
{
  struct iphdr  *hdr;

  hdr = (struct iphdr*)packet;
  hdr->ihl = 5;
  hdr->version = 4;
  hdr->tos = 0;
  hdr->tot_len = htons(sizeof(struct iphdr) + payload_size);
  hdr->id = htons(rand());
  hdr->frag_off = htons(0x4000);
  hdr->ttl = 255;
  hdr->protocol = IPPROTO_ICMP;
  hdr->check = 0;
  hdr->saddr = src;
  hdr->daddr = dst;
  hdr->check = ipcheck(packet, sizeof(struct iphdr) + payload_size);
}
