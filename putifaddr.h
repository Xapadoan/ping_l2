#ifndef PUTIFADDR_H
#define PUTIFADDR_H

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <net/if.h>
#include "putsockaddr.h"

void  putifaddr(struct ifaddrs *addr);

#endif
