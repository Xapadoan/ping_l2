#ifndef PUT_SOCKADDR_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>

void  put_sockaddr(struct sockaddr *addr);

#endif
