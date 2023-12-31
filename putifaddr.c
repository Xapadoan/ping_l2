#include "putifaddr.h"

void  putifaddr(struct ifaddrs *addr)
{
  printf("\n%s: ", addr->ifa_name);
  if (addr->ifa_flags & IFF_UP)
    printf("UP ");
  if (addr->ifa_flags & IFF_RUNNING)
    printf("RUNNING ");
  if (addr->ifa_flags & IFF_LOOPBACK)
    printf("LOOPBACK ");
  if (addr->ifa_flags & IFF_NOARP)
    printf("NOARP ");
  printf("\n\tinet:\t");
  putsockaddr(addr->ifa_addr);
  if (addr->ifa_netmask)
  {
    printf("\n\tmask:\t");
    putsockaddr(addr->ifa_netmask);
  }
  if (addr->ifa_broadaddr)
  {
    printf("\n\tbroad:\t");
    putsockaddr(addr->ifa_broadaddr);
  }
  if (addr->ifa_dstaddr)
  {
    printf("\n\tdst:\t");
    putsockaddr(addr->ifa_dstaddr);
  }
  printf("\n");
}
