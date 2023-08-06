#ifndef PL2_BUILDICMPV6_H
#define PL2_BUILDICMPV6_H

#include <sys/time.h>
#include <linux/icmp.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "ipv6check.h"

void  buildicmpv6(uint8_t *packet, uint8_t type, uint16_t seq, int len);

#endif
