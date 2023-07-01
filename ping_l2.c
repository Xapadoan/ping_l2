#include "ping_l2.h"

int main(int argc, char **argv)
{
  char        ifname[IFNAMSIZ];
  uint8_t     gw_hwaddr[ETH_ALEN];
  const char  dst_ip[8] = "8.8.8.8";

  memset(ifname, 0, IFNAMSIZ);
  memset(gw_hwaddr, 0, ETH_ALEN);
  getrecvif(ifname);
  sendarp(ifname, "192.168.0.254", gw_hwaddr);
  printf("END: %02x:%02x:%02x:%02x:%02x:%02x\n", gw_hwaddr[0], gw_hwaddr[1], gw_hwaddr[2], gw_hwaddr[3], gw_hwaddr[4], gw_hwaddr[5]);
}
