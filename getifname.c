#include "getifname.h"

void  getifname(char *ifname)
{
  struct ifaddrs  *all;
  struct ifaddrs  *i;

  all = NULL;
  i = NULL;
  if (getifaddrs(&all) != 0)
  {
    pl2_error(PL2_LOG_LVL_ERROR, "getrecvif", errno);
    return;
  }
  if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
  {
    i = all;
    pl2_log(PL2_LOG_LVL_DEBUG, "getrecvif", "Listing interfaces:");
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
      pl2_log(PL2_LOG_LVL_DEBUG, "getrecvif", "Chose interface:");
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
