#ifndef PL2_PUTIFADDR_H
#define PL2_PUTIFADDR_H

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <linux/if.h>
#include "putsockaddr.h"

void  putifaddr(struct ifaddrs *addr);

#endif
