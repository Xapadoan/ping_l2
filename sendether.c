#include "sendether.h"

int sendether(int fd, int ifindex, uint8_t *packet, int len, uint8_t pktype)
{
  struct ethhdr       *hdr;
  struct sockaddr_ll  addr;
  int                 bsent;

  bsent = 0;
  hdr = (struct ethhdr*)packet;
  addr.sll_family = AF_PACKET;
  addr.sll_protocol = hdr->h_proto;
  addr.sll_ifindex = ifindex;
  addr.sll_hatype = htons(ARPHRD_ETHER);
  addr.sll_pkttype = htons(pktype);
  addr.sll_halen = htons(ETH_ALEN);
  memset(addr.sll_addr, 0, 8);
  memcpy(addr.sll_addr, hdr->h_source, ETH_ALEN);
  debug("[sendether] Sending to ");
  if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
  {
    putsockaddr((struct sockaddr*)&addr);
  }
  debug("\n[sendether]\tprotocol: %02x\tpktype: %02x\n", addr.sll_protocol, addr.sll_pkttype);
  bsent = sendto(fd, packet, len, 0, (struct sockaddr*)&addr, sizeof(addr));
  if (bsent == -1)
  {
    perror("[sendether] Failed to send packet");
    return (-1);
  }
  debug("[sendether] Send %u bytes out of %u\n", bsent, len);
  return (0);
}
