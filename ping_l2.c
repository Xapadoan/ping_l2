#include "ping_l2.h"

int main(int argc, char **argv)
{
  char        ifname[IFNAMSIZ];
  uint8_t     gw_hwaddr[ETH_ALEN];
  uint32_t    gw_ip;
  const char  dst_ip[8] = "8.8.8.8";

  gw_ip = 0;
  memset(ifname, 0, IFNAMSIZ);
  memset(gw_hwaddr, 0, ETH_ALEN);
  getifname(ifname);
  gw_ip = getgwaddr(ifname);
  sendarp(ifname, gw_ip, gw_hwaddr);
  printf("END: %02x:%02x:%02x:%02x:%02x:%02x\n", gw_hwaddr[0], gw_hwaddr[1], gw_hwaddr[2], gw_hwaddr[3], gw_hwaddr[4], gw_hwaddr[5]);
}
