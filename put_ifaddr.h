#ifndef PUT_IFADDR_H
#define PUT_IFADDR_H

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <net/if.h>
#include "put_sockaddr.h"

void  put_ifaddr(struct ifaddrs *addr);

#endif
