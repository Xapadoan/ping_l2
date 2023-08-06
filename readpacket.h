#ifndef PL2_READPACKET_H
#define PL2_READPACKET_H

#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "debug.h"
#include "buildipv6.h"

struct packetdata
{
  uint8_t       from[INET6_ADDRSTRLEN];
  uint16_t      seq;
  uint8_t       ttl;
  double        rtt;
};

int readpacket(int fd, uint8_t *buffer, unsigned int len);

#endif
