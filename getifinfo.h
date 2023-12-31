#ifndef PL2_GETIFINFO_H
#define PL2_GETIFINFO_H

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <ifaddrs.h>
#include "debug.h"
#include "putifaddr.h"

struct ifinfo {
  int       index;
  char      name[IFNAMSIZ];
  uint8_t   hwaddr[ETH_ALEN];
  uint32_t  in_addr;
  uint8_t   in6_addr[16];
};

int getifinfo(struct ifinfo *info, int family);

#endif
