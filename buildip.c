#include "buildip.h"

void  buildip(uint8_t *packet, uint32_t src, uint32_t dst, struct ipv4opts *opts)
{
  struct iphdr  *hdr;

  hdr = (struct iphdr*)packet;
  hdr->ihl = 5;
  hdr->version = 4;
  hdr->tos = opts->tos;
  hdr->tot_len = htons(opts->len);
  hdr->id = htons(rand());
  hdr->frag_off = htons(0x4000);
  hdr->ttl = opts->ttl;
  hdr->protocol = IPPROTO_ICMP;
  hdr->check = 0;
  hdr->saddr = src;
  hdr->daddr = dst;
  if (opts->record != 0)
  {
    packet[sizeof(struct iphdr)] = 1;
    packet[sizeof(struct iphdr) + 1] = 7;
    packet[sizeof(struct iphdr) + 2] = 39;
    packet[sizeof(struct iphdr) + 3] = 8;
    memcpy((uint32_t *)(packet + sizeof(struct iphdr) + 4), &src, 4);
    hdr->ihl += 10;
  }
  hdr->check = ipcheck(packet, opts->len);
}
