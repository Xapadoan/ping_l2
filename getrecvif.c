#include "getrecvif.h"

struct ifaddrs *getrecvif()
{
  struct ifaddrs *all;
  struct ifaddrs *i;

  all = NULL;
  i = NULL;
  if (getifaddrs(&all) != 0)
  {
    pl2_error(PL2_LOG_LVL_ERROR, "getrecvif", errno);
    return NULL;
  }
  i = all;
  pl2_log(PL2_LOG_LVL_DEBUG, "getrecvif", "Listing interfaces:");
  while (i != NULL)
  {
    if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
    {
      put_ifaddr(i);
    }
    i = i->ifa_next;
  }
  freeifaddrs(all);
  return NULL;
}
