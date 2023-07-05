#include "buildicmp.h"

void  buildicmp(uint8_t *packet, uint8_t type, uint16_t seq, int len)
{
  struct icmphdr *hdr;

  hdr = (struct icmphdr *)packet;
  hdr->type = type;
  hdr->code = 0;
  hdr->checksum = 0;
  hdr->un.echo.id = htons(rand());
  hdr->un.echo.sequence = htons(seq);
  hdr->checksum = ipcheck(packet, len);
}
