#ifndef PL2_GETRECVIF_H
#define PL2_GETRECVIF_H

#include <ifaddrs.h>
#include "debug.h"
#include "put_ifaddr.h"

struct ifaddrs *getrecvif(void);

#endif
