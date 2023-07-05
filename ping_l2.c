#include "ping_l2.h"

int main(int argc, char **argv)
{
  uint8_t     gw_hwaddr[ETH_ALEN];
  uint32_t    gw_ip;
  const char  dst_ip[8] = "8.8.8.8";
  int         sock;
  struct ifinfo local;

  gw_ip = 0;
  memset(gw_hwaddr, 0, ETH_ALEN);
  memset(&local, 0, sizeof(local));
  sock = -1;
  if (getifinfo(&local) != 0)
  {
    error("[ping_l2] getifinfo failed\n");
    return (-1);
  }
  gw_ip = getgwaddr(local.name);
  sendarp(&local, gw_ip, gw_hwaddr);
  debug("[ping_l2] GW_HWADDR: %02x:%02x:%02x:%02x:%02x:%02x\n", gw_hwaddr[0], gw_hwaddr[1], gw_hwaddr[2], gw_hwaddr[3], gw_hwaddr[4], gw_hwaddr[5]);
  return (0);
}
