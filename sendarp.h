#ifndef PL2_SENDARP_H
#define PL2_SENDARP_H

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <string.h>
#include "debug.h"
#include "bindsock.h"
#include "sendether.h"
#include "buildether.h"
#include "getifinfo.h"

struct arp
{
  uint16_t  hwtype;
  uint16_t  proto;
  uint8_t   hwaddrlen;
  uint8_t   proto_addrlen;
  uint16_t  op;
  uint8_t   src_hwaddr[ETH_ALEN];
  uint8_t   src_addr[4];
  uint8_t   dst_hwaddr[ETH_ALEN];
  uint8_t   dst_addr[4];
};

int sendarp(const struct ifinfo *local, const uint32_t dst_ip, char *hwaddr);

#endif
