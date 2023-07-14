#ifndef PL2_IPV6CHECK_H
#define PL2_IPV6CHECK_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ipcheck.h"

uint16_t  ipv6check(uint8_t *packet, size_t payload_len);

#endif
