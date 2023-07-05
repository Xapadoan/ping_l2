#ifndef PL2_BINDSOCK_H
#define PL2_BINDSOCK_H

#include <sys/socket.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if_packet.h>
#include "debug.h"

int bindsock(int *fd, int ifindex, uint16_t proto);

#endif
