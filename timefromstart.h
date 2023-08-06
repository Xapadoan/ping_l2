#ifndef PL2_TIMEFROMSTART_H
#define PL2_TIMEFROMSTART_H

#include <sys/time.h>
#include <errno.h>
#include <stddef.h>

int timefromstart(struct timeval *start);

#endif
