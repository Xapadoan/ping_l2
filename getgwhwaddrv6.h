#ifndef PL2_GETGWHWADDRV6_H
#define PL2_GETGWHWADDRV6_H

#include <linux/icmp.h>
#include <linux/if_ether.h>
#include <string.h>
#include "debug.h"
#include "getifinfo.h"
#include "buildether.h"
#include "buildipv6.h"
#include "ipv6check.h"
#include "sendether.h"
#include "ipv6opts.h"

int getgwhwaddrv6(int fd, struct ifinfo *local, uint8_t gw_addr[ETH_ALEN]);

#endif
