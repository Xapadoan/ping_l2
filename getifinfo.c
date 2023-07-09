#include "getifinfo.h"

int pickif(struct ifinfo *info, int family)
{
  struct ifaddrs  *all;
  struct ifaddrs  *i;

  all = NULL;
  i = NULL;
  if (getifaddrs(&all) != 0)
  {
    perror("[pickif] Failed to getifaddrs");
    return (-1);
  }
  if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
  {
    i = all;
    debug("[pickif] Listing interfaces:\n");
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
      debug("[pickif] Chose interface:\n");
      if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
      {
        putifaddr(i);
      }
      memcpy(info->name, i->ifa_name, IFNAMSIZ);
      memcpy(&info->addr, i->ifa_addr, sizeof(struct sockaddr));
      freeifaddrs(all);
      return (0);
    }
    i = i->ifa_next;
  }
  freeifaddrs(all);
  error("[pickif] Found no suitable interface\n");
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
  memcpy(&ifr.ifr_name, info->name, IFNAMSIZ);
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
    "[getifinfo] %s (%u):\n[getifinfo]\thwaddr: %02x:%02x:%02x:%02x:%02x:%02x\n[getifinfo]\taddr: ", \
    info->name, info->index, \
    info->hwaddr[0], info->hwaddr[1], info->hwaddr[2], info->hwaddr[3], info->hwaddr[4], info->hwaddr[5] \
  );
  if (DEBUG_LVL >= PL2_LOG_LVL_DEBUG)
  {
    putsockaddr(&info->addr);
  }
  debug("\n");
  close(fd);
  return (0);
}
