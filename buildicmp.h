#ifndef PL2_BUILDICMP_H
#define PL2_BUILDICMP_H

#include <linux/icmp.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "ipcheck.h"

void  buildicmp(uint8_t *packet, uint8_t type, uint16_t seq, int len);

#endif
