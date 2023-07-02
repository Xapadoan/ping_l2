#ifndef PL2_GETGWADDR_H
#define PL2_GETGWADDR_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"

#define DEFAULT_GWADDR 0xfe00a8c0

uint32_t  getgwaddr(const char *ifname);

#endif
