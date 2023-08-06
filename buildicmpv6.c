#include "buildicmpv6.h"

void  buildicmpv6(uint8_t *packet, uint8_t type, uint16_t seq, int len)
{
  struct icmphdr  *hdr;
  struct timeval  *tv;

  hdr = (struct icmphdr *)(packet + 40);
  tv = (struct timeval*)(packet + 40 + 8);
  hdr->type = type;
  hdr->code = 0;
  hdr->checksum = 0;
  hdr->un.echo.id = htons(rand());
  hdr->un.echo.sequence = htons(seq);
  gettimeofday(tv, NULL);
  hdr->checksum = ipv6check(packet, len);
}
