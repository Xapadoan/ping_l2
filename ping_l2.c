#include "ping_l2.h"

int main(int argc, char **argv)
{
  char  ifname[IFNAMSIZ];

  memset(ifname, 0, IFNAMSIZ);
  getrecvif(ifname);
  printf("END: %s\n", ifname);
}
