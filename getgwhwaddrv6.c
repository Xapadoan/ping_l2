#include "getgwhwaddrv6.h"

int sendroutersol(int fd, struct ifinfo *local)
{
  uint8_t             packet[62];
  uint8_t             broad_hwaddr[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  struct sockaddr_in6 gw_addr;
  struct icmphdr      *icmp;

  memset(packet, 0, 62);
  if (inet_pton(AF_INET6, "ff02::2", &gw_addr.sin6_addr) != 1)
  {
    error("[sendroutersol] inet_pton failed\n");
    return (-1);
  }
  buildether(packet, local->hwaddr, broad_hwaddr, ETH_P_IPV6);
  buildipv6(packet + ETH_HLEN, local->in6_addr, gw_addr.sin6_addr.s6_addr, 8);
  icmp = (struct icmphdr*)(packet + 40 + ETH_HLEN);
  icmp->type = 133;
  icmp->code = 0;
  icmp->checksum = 0;
  icmp->checksum = ipv6check(packet + ETH_HLEN, 8);
  if (sendether(fd, local->index, packet, 62, PACKET_OUTGOING) != 0)
  {
    error("[sendroutersol] sendether failed\n");
    return (-1);
  }
  return (0);
}

int readrouterad(int fd, uint8_t  hwaddr[ETH_ALEN])
{
  int nbytes;
  uint8_t buffer[1500];
  uint8_t hwaddropt[8];
  int     hwopti;
  struct icmphdr  *icmp;

  memset(buffer, 0, 1500);
  nbytes = recvfrom(fd, buffer, 1500, 0, NULL, NULL);
  if (nbytes < 0)
  {
    perror("[readrouterad] recvfrom");
    return (-1);
  }
  icmp = (struct icmphdr*)(buffer + ETH_HLEN + 40);
  if (icmp->type != 134)
  {
    debug("[readrouterad] not a router advertisement\n");
    return (readrouterad(fd, hwaddr));
  }
  hwopti = ETH_HLEN + 40 + 8;
  while (buffer[hwopti] != 1 && hwopti < 1500)
  {
    hwopti += (8 * buffer[hwopti + 1]);
    if (buffer[hwopti] == 0)
      hwopti += 8;
  }
  memcpy(hwaddr, buffer + hwopti + 2, ETH_ALEN);
  debug("[readrouterad] Got hwaddr: %02x:%02x:%02x:%02x:%02x:%02x\n", hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);
  return (0);
}

int getgwhwaddrv6(int fd, struct ifinfo *local, uint8_t hwaddr[ETH_ALEN])
{
  if (sendroutersol(fd, local) != 0)
  {
    error("[gatewayinfo] sendroutersol failed\n");
    return (-1);
  }
  if (readrouterad(fd, hwaddr) != 0)
  {
    error("[gatewayinfo] readrouterad failed\n");
    return (-1);
  }
  return (0);
}
