#include "ping_l2.h"

int main(int argc, char **argv)
{
  uint8_t     gw_hwaddr[ETH_ALEN];
  uint32_t    gw_ip;
  const char  dst_ip[8] = "8.8.8.8";
  // const char  dst_ip[20] = "2001:4860:4860::8888";
  const int   family = AF_INET;
  int         sock;
  uint8_t     packet[60];
  struct ifinfo local;

  gw_ip = 0;
  memset(gw_hwaddr, 0, ETH_ALEN);
  memset(&local, 0, sizeof(local));
  sock = -1;
  if (getifinfo(&local, family) != 0)
  {
    error("[ping_l2] getifinfo failed\n");
    return (-1);
  }
  if (family == AF_INET)
  {
    gw_ip = getgwaddr(local.name);
    sendarp(&local, gw_ip, gw_hwaddr);
  }
  debug("[ping_l2] GW_HWADDR: %02x:%02x:%02x:%02x:%02x:%02x\n", gw_hwaddr[0], gw_hwaddr[1], gw_hwaddr[2], gw_hwaddr[3], gw_hwaddr[4], gw_hwaddr[5]);
  memset(packet, 0, 60);
  if (family == AF_INET)
  {
    bindsock(&sock, local.index, ETH_P_IP);
    buildether(packet, local.hwaddr, gw_hwaddr, ETH_P_IP);
    buildicmp(packet + ETH_HLEN + 20, 8, 1, 20);
    buildip(packet + ETH_HLEN, ((struct sockaddr_in *)&local.addr)->sin_addr.s_addr, inet_addr(dst_ip), 20);
    sendether(sock, local.index, packet, 60, PACKET_OUTGOING);
  }
  return (0);
}
