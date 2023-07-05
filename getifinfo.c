#include "getifinfo.h"

int getifname(char *ifname)
{
  struct ifaddrs  *all;
  struct ifaddrs  *i;

  all = NULL;
  i = NULL;
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
    if ((i->ifa_flags & IFF_UP && i->ifa_flags & IFF_RUNNING) && !(i->ifa_flags & (IFF_LOOPBACK | IFF_NOARP)))
    {
      debug("[getifname] Chose interface:\n");
      if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
      {
        putifaddr(i);
      }
      memcpy(ifname, i->ifa_name, IFNAMSIZ);
      freeifaddrs(all);
      return (0);
    }
    i = i->ifa_next;
  }
  freeifaddrs(all);
  error("[getifname] Found no suitable interface\n");
  return (-1);
}

int getifinfo(struct ifinfo *info)
{
  struct ifreq  ifr;
  int           fd;

  memset(info, 0, sizeof(struct ifinfo));
  if (getifname(info->name) != 0)
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
  if (ioctl(fd, SIOCGIFADDR, &ifr) == -1)
  {
    perror("[getifinfo] Failed to get address");
    close(fd);
    return (-1);
  }
  if (ifr.ifr_addr.sa_family != AF_INET)
  {
    error("[getifinfo] Interface has no AF_INET addr");
    close(fd);
    return (-1);
  }
  info->addr = ((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr.s_addr;
  
  debug(\
    "[getifinfo] %s (%u):\n[getifinfo]\thwaddr: %02x:%02x:%02x:%02x:%02x:%02x\n[getifinfo]\taddr: %02x.%02x.%02x.%02x\n", \
    info->name, info->index, \
    info->hwaddr[0], info->hwaddr[1], info->hwaddr[2], info->hwaddr[3], info->hwaddr[4], info->hwaddr[5], \
    info->addr >> 24 & 0x000000ff, info->addr >> 16 & 0x000000ff, info->addr >> 8 & 0x000000ff, info->addr & 0x000000ff\
  );
  close(fd);
  return (0);
}
