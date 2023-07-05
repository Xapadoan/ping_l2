#ifndef PL2_BUILDIP_H
#define PL2_BUILDIP_H

#include <linux/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "ipcheck.h"

void  buildip(uint8_t *packet, uint32_t src, uint32_t dst, int payload_len);

#endif
