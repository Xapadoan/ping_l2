#ifndef PL2_SENDETHER_H
#define PL2_SENDETHER_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <string.h>
#include "debug.h"
#include "putsockaddr.h"

int sendether(int fd, int ifindex, uint8_t *packet, int len, uint8_t pktype);

#endif
