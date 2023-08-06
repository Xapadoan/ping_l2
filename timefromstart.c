#include "timefromstart.h"

int timefromstart(struct timeval *start)
{
  struct timeval  now;

  if (gettimeofday(&now, NULL) != 0)
  {
    perror("[remainingtime]: gettimeofday");
    return (-1);
  }
  return ((now.tv_sec - start->tv_sec) * 1000000 + (now.tv_usec - start->tv_usec));
}
