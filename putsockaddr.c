#include "putsockaddr.h"

void putin(struct sockaddr_in *addr)
{
  printf("%u.%u.%u.%u", (ntohl(addr->sin_addr.s_addr) >> 24) & 0x000000ff, (ntohl(addr->sin_addr.s_addr) >> 16) & 0x000000ff, (ntohl(addr->sin_addr.s_addr) >> 8) & 0x000000ff, ntohl(addr->sin_addr.s_addr) & 0x000000ff);
}

void putin6(struct sockaddr_in6 *addr)
{
  unsigned int i;

  i = 0;
  while (i < 16)
  {
    if (i % 2 == 0 && i != 0)
      printf(":");
    printf("%02x", addr->sin6_addr.s6_addr[i]);
    i++;
  }
}

void putll(struct sockaddr_ll *addr)
{
  unsigned int  i;

  i = 0;
  while (i < 7)
  {
    printf("%02x:", addr->sll_addr[i]);
    i++;
  }
  printf("%02x", addr->sll_addr[i]);
}

void  putsockaddr(struct sockaddr *addr)
{
  if (addr->sa_family == AF_INET)
    putin((struct sockaddr_in*)addr);
  else if (addr->sa_family == AF_INET6)
    putin6((struct sockaddr_in6*)addr);
  else if (addr->sa_family == AF_PACKET)
    putll((struct sockaddr_ll*)addr);
}
