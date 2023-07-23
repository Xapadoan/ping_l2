#include "ping_l2.h"

int main(int argc, char **argv)
{
  uint8_t     gw_hwaddr[ETH_ALEN];
  uint32_t    gw_ip;
  const char  dst_ip[8] = "8.8.8.8";
  int         family = AF_INET;
  int         sock;
  uint8_t     packet[1500];
  struct ifinfo local;
  uint8_t     broad_hwaddr[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  struct sockaddr_in6 dst;
  struct args args;

  if (parseargs(argc, argv, &parsed) != 0)
  {
    error("[ping_l2] parseargs failed\n");
    return (-1);
  }
  /*
  gw_ip = 0;
  memset(gw_hwaddr, 0, ETH_ALEN);
  memset(&local, 0, sizeof(local));
  memset(&dst, 0, sizeof(dst));
  memset(packet, 0, 1500);
  sock = -1;
  if (strlen(args.interface))
    memcpy(local.name, args.interface, 20);
  printf("%s: %d\n", local.name, strlen(local.name));
  if (getifinfo(&local, args.family) != 0)
  {
    error("[ping_l2] getifinfo failed\n");
    return (-1);
  }
  if (family == AF_INET6)
  {
    dst.sin6_family = AF_INET6;
    if (inet_pton(family, "2001:4860:4860::8888", &dst.sin6_addr) != 1)
    {
      error("[ping_l2] inet_pton failed\n");
      return (-1);
    }
    if (bindsock(&sock, local.index, ETH_P_IPV6) != 0)
    {
      error("[ping_l2] bindsock failed\n");
      return (-1);
    }
    if (getgwhwaddrv6(sock, &local, gw_hwaddr) != 0)
    {
      error("[ping_l2] gatewayinfo failed\n");
      return (-1);
    }
  } else if (family == AF_INET) {
    if (bindsock(&sock, local.index, ETH_P_IP) != 0)
    {
      error("[ping_l2] bindsock failed\n");
      return (-1);
    }
    gw_ip = getgwaddr(local.name);
    if (sendarp(&local, gw_ip, gw_hwaddr) != 0)
    {
      error("[ping_l2] sendarp failed\n");
      return (-1);
    }
  }
  debug("[ping_l2] GW_HWADDR: %02x:%02x:%02x:%02x:%02x:%02x\n", gw_hwaddr[0], gw_hwaddr[1], gw_hwaddr[2], gw_hwaddr[3], gw_hwaddr[4], gw_hwaddr[5]);
  if (family == AF_INET6)
  {
    buildether(packet, local.hwaddr, gw_hwaddr, ETH_P_IPV6);
    buildipv6(packet + ETH_HLEN, local.in6_addr, dst.sin6_addr.s6_addr, 20);
    buildicmpv6(packet + ETH_HLEN, 128, 1, 20);
    sendether(sock, local.index, packet, 74, PACKET_OUTGOING);
  }
  if (family == AF_INET)
  {
    buildether(packet, local.hwaddr, gw_hwaddr, ETH_P_IP);
    buildip(packet + ETH_HLEN, local.in_addr, inet_addr(dst_ip), 20);
    buildicmp(packet + ETH_HLEN + 20, 8, 1, 20);
    sendether(sock, local.index, packet, 54, PACKET_OUTGOING);
  }
  */
  return (0);
}
