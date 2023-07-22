#ifndef PL2_PARSEARGS_H
#define PL2_PARSEARGS_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "args.h"

int parseargs(int argc, char **argv, struct args *args);

#endif
