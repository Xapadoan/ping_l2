#include "bindsock.h"

int bindsock(int *fd, int ifindex, uint16_t proto)
{
  struct sockaddr_ll  ifhwaddr;

  memset(&ifhwaddr, 0, sizeof(struct sockaddr_ll));
  *fd = socket(AF_PACKET, SOCK_RAW, htons(proto));
  if (*fd < 0)
  {
    perror("[bindsock] Socket creation failed");
    return (-1);
  }
  ifhwaddr.sll_family = AF_PACKET;
  ifhwaddr.sll_ifindex = ifindex;
  debug("[bindsock] Binding to index: %d\n", ifindex);
  if (bind(*fd, (struct sockaddr *)&ifhwaddr, sizeof(ifhwaddr)) < 0)
  {
    perror("[bindsock] Socket binding failed");
    close(*fd);
    return (-1);
  }
  return (0);
}
