#include "getifinfo.h"

int pickif(struct ifinfo *info, int family)
{
  struct ifaddrs  *all;
  struct ifaddrs  *i;
  int             addr_len;

  addr_len = 0;
  all = NULL;
  i = NULL;
  if (family == AF_INET)
    addr_len = sizeof(struct sockaddr_in);
  else if (family == AF_INET6)
    addr_len = sizeof(struct sockaddr_in6);
  if (getifaddrs(&all) != 0)
  {
    perror("[getifname] Failed to getifaddrs");
    return (-1);
  }
  if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
  {
    i = all;
    debug("[getifname] Listing interfaces:\n");
    while (i != NULL)
    {
      putifaddr(i);
      i = i->ifa_next;
    }
  }
  i = all;
  while (i != NULL)
  {
    if ((i->ifa_flags & IFF_UP && i->ifa_flags & IFF_RUNNING) && !(i->ifa_flags & (IFF_LOOPBACK | IFF_NOARP)) && i->ifa_addr->sa_family == family)
    {
      debug("[getifname] Chose interface:\n");
      if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
      {
        putifaddr(i);
      }
      memcpy(info->name, i->ifa_name, IFNAMSIZ);
      if (family == AF_INET)
        info->in_addr = ((struct sockaddr_in*)i->ifa_addr)->sin_addr.s_addr;
      else if (family == AF_INET6)
        memcpy(&(info->in6_addr), ((struct sockaddr_in6*)i->ifa_addr)->sin6_addr.s6_addr, 16);
      freeifaddrs(all);
      return (0);
    }
    i = i->ifa_next;
  }
  freeifaddrs(all);
  error("[getifname] Found no suitable interface\n");
  return (-1);
}

int getifinfo(struct ifinfo *info, int family)
{
  struct ifreq  ifr;
  int           fd;

  memset(info, 0, sizeof(struct ifinfo));
  if (pickif(info, family) != 0)
  {
    error("[getifinfo] getifname failed\n");
    return (-1);
  }
  strcpy(ifr.ifr_name, info->name);
  fd = socket(AF_PACKET, SOCK_RAW, 0);
  if (fd <= 0)
  {
    perror("[getifinfo] Failed to open socket");
    return (-1);
  }
  if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1)
  {
    perror("[getifinfo] Failed to get index");
    close(fd);
    return (-1);
  }
  info->index = ifr.ifr_ifindex;
  if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1)
  {
    perror("[getifinfo] Failed to get hw address");
    close(fd);
    return (-1);
  }
  memcpy(info->hwaddr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
  
  debug(\
    "[getifinfo] %s (%u):\n[getifinfo]\thwaddr: %02x:%02x:%02x:%02x:%02x:%02x\n[getifinfo]\tin_addr: %u.%u.%u.%u\n", \
    info->name, info->index, \
    info->hwaddr[0], info->hwaddr[1], info->hwaddr[2], info->hwaddr[3], info->hwaddr[4], info->hwaddr[5], \
    ntohl(info->in_addr) >> 24 & 0x000000ff, ntohl(info->in_addr) >> 16 & 0x000000ff, ntohl(info->in_addr) >> 8 & 0x000000ff, ntohl(info->in_addr) & 0x000000ff\
  );
  debug("[getifinfo]\tin6_addr: ");
  int i = 0;
  while (i < 16)
  {
    printf("%02x", info->in6_addr[i]);
    i++;
  }
  debug("\n");
  close(fd);
  return (0);
}
