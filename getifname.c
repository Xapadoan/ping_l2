#include "getifname.h"

void  getifname(char *ifname)
{
  struct ifaddrs  *all;
  struct ifaddrs  *i;

  all = NULL;
  i = NULL;
  if (getifaddrs(&all) != 0)
  {
    perror("[getrecvif] Failed to getifaddrs");
    return;
  }
  if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
  {
    i = all;
    debug("[getrecvif] Listing interfaces:\n");
    while (i != NULL)
    {
      putifaddr(i);
      i = i->ifa_next;
    }
  }
  i = all;
  while (i != NULL)
  {
    if ((i->ifa_flags & IFF_UP && i->ifa_flags & IFF_RUNNING) && !(i->ifa_flags & (IFF_LOOPBACK | IFF_NOARP)))
    {
      debug("[getrecvif] Chose interface:\n");
      if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
      {
        putifaddr(i);
      }
      memcpy(ifname, i->ifa_name, IFNAMSIZ);
      freeifaddrs(all);
      return;
    }
    i = i->ifa_next;
  }
  freeifaddrs(all);
  return;
}
