#ifndef PL2_BUILDIP_H
#define PL2_BUILDIP_H

#include <linux/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "ipcheck.h"
#include "ipv4opts.h"

void  buildip(uint8_t *packet, uint32_t src, uint32_t dst, struct ipv4opts *opts);

#endif
