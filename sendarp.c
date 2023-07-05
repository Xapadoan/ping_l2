#include "sendarp.h"

int sendpacket(const char *src_mac, uint32_t src_ip, uint32_t dst_ip, int ifindex, int fd)
{
  uint8_t             buffer[42];
  uint8_t             ifbroadaddr[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  struct ethhdr       *req;
  struct arp          *arp;
  struct sockaddr_ll  addr;
  unsigned int        bsent;
  int                 ret;

  ret = -1;
  memset(buffer, 0, 42);
  buildether(buffer, src_mac, ifbroadaddr, ETH_P_ARP);
  arp = (struct arp *)(buffer + ETH_HLEN);
  arp->hwtype = htons(ARPHRD_ETHER);
  arp->proto = htons(ETH_P_IP);
  arp->hwaddrlen = ETH_ALEN;
  arp->proto_addrlen = 4;
  arp->op = htons(1);
  memcpy(arp->src_hwaddr, src_mac, ETH_ALEN);
  memcpy(arp->src_addr, &src_ip, 4);
  memset(arp->dst_hwaddr, 0, ETH_ALEN);
  memcpy(arp->dst_addr, &dst_ip, 4);
  ret = sendether(fd, ifindex, buffer, 42, PACKET_BROADCAST);
  if (ret != 0)
  {
    error("[sendpacket] sendether failed\n");
    return (-1);
  }
  return (0);
}

int readpacket(int fd, char *hwaddr)
{
  uint8_t       buffer[60];
  struct ethhdr *res;
  struct arp    *arp;

  debug("[readpacket] Reading on: %d\n", fd);
  if (recvfrom(fd, buffer, 60, 0, NULL, NULL) == -1)
  {
    perror("[readpacket] Failed to read\n");
    return (-1);
  }
  res = (struct ethhdr*)buffer;
  if (res->h_proto != htons(ETH_P_ARP))
  {
    debug("[readpacket] Got non arp packet\n");
    return (0);
  }
  arp = (struct arp*)(buffer + ETH_HLEN);
  if (arp->op != htons(2))
  {
    debug("[readpacket] Got arp but not a reply\n");
    return (0);
  }
  memcpy(hwaddr, &(arp->src_hwaddr), ETH_ALEN);
  return (1);
}

int sendarp(const struct ifinfo *local, const uint32_t dst_ip, char *hwaddr)
{
  int           sock_fd;
  int           read_ret;

  read_ret = 0;
  if (bindsock(&sock_fd, local->index, ETH_P_ARP) != 0)
  {
    error("[sendarp] bindsock failed\n");
    return (-1);
  }
  if (sendpacket(local->hwaddr, local->addr, dst_ip, local->index, sock_fd) != 0)
  {
    error("[sendarp] sendpacket failed\n");
    close(sock_fd);
    return (-1);
  }
  debug("[sendarp] sendpacket OK\n");
  while (read_ret == 0)
  {
    debug("[sendarp] reading packet\n");
    read_ret = readpacket(sock_fd, hwaddr);
  }
  if (read_ret == -1)
  {
    error("[sendarp] readpacket failed\n");
    close(sock_fd);
    return (-1);
  }
  return (0);
}
