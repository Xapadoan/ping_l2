#ifndef PL2_BUILDETHER_H
#define PL2_BUILDETHER_H

#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <string.h>

void  buildether(uint8_t *buffer, const uint8_t *src, const uint8_t *dst, uint16_t proto);

#endif
