#ifndef PL2_PUTSOCKADDR_H
#define PL2_PUTSOCKADDR_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>

void  putsockaddr(struct sockaddr *addr);

#endif
