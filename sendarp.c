#include "sendarp.h"

int getifinfo(const char *ifname, uint32_t *ip, char *mac, int *ifindex)
{
  struct ifreq  ifr;
  int           fd;

  strcpy(ifr.ifr_name, ifname);
  fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
  if (fd <= 0)
  {
    perror("[getifinfo] Failed to open socket\n");
    return (-1);
  }
  if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1)
  {
    perror("[getifinfo] Failed to get index\n");
    close(fd);
    return (-1);
  }
  *ifindex = ifr.ifr_ifindex;
  if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1)
  {
    perror("[getifinfo] Failed to get hw address\n");
    close(fd);
    return (-1);
  }
  memcpy(mac, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
  if (ioctl(fd, SIOCGIFADDR, &ifr) == -1)
  {
    perror("[getifinfo] Failed to get address\n");
    close(fd);
    return (-1);
  }
  if (ifr.ifr_addr.sa_family != AF_INET)
  {
    error("[getifinfo] Interface has no AF_INET addr\n");
    close(fd);
    return (-1);
  }
  *ip = ((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr.s_addr;
  
  debug("Local Ip: %02x.%02x.%02x.%02x\n", *ip >> 24 & 0x000000ff, *ip >> 16 & 0x000000ff, *ip >> 8 & 0x000000ff, *ip & 0x000000ff);
  close(fd);
  return (0);
}

int init_arp_socket(int *fd, int ifindex)
{
  struct sockaddr_ll  ifhwaddr;

  memset(&ifhwaddr, 0, sizeof(struct sockaddr_ll));
  *fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
  if (*fd < 0)
  {
    perror("[init_arp_socket] Socket creation failed:\n");
    return (-1);
  }
  ifhwaddr.sll_family = AF_PACKET;
  ifhwaddr.sll_ifindex = ifindex;
  debug("[init_arp_socket] Binding to index: %d\n", ifindex);
  if (bind(*fd, (struct sockaddr *)&ifhwaddr, sizeof(ifhwaddr)) < 0)
  {
    perror("[init_arp_socket] Socket binding failed:\n");
    close(*fd);
    return (-1);
  }
  return (0);
}

int sendpacket(const char *src_mac, uint32_t src_ip, uint32_t dst_ip, int ifindex, int fd)
{
  uint8_t             buffer[42];
  struct ethhdr       *req;
  struct arp          *arp;
  struct sockaddr_ll  addr;
  unsigned int        bsent;

  memset(buffer, 0, 60);
  req = (struct ethhdr *)buffer;
  arp = (struct arp *)(buffer + ETH_HLEN);
  memset(req->h_dest, 0xff, ETH_ALEN);
  memcpy(req->h_source, src_mac, ETH_ALEN);
  req->h_proto = htons(ETH_P_ARP);
  arp->hwtype = htons(ARPHRD_ETHER);
  arp->proto = htons(ETH_P_IP);
  arp->hwaddrlen = ETH_ALEN;
  arp->proto_addrlen = 4;
  arp->op = htons(1);
  memcpy(arp->src_hwaddr, src_mac, ETH_ALEN);
  memcpy(arp->src_addr, &src_ip, 4);
  memset(arp->dst_hwaddr, 0, ETH_ALEN);
  memcpy(arp->dst_addr, &dst_ip, 4);
  addr.sll_family = AF_PACKET;
  addr.sll_protocol = htons(ETH_P_ARP);
  addr.sll_ifindex = ifindex;
  addr.sll_hatype = htons(ARPHRD_ETHER);
  addr.sll_pkttype = htons(PACKET_BROADCAST);
  addr.sll_halen = htons(ETH_ALEN);
  memset(addr.sll_addr, 0, 8);
  memcpy(addr.sll_addr, src_mac, ETH_ALEN);
  debug("Send packet to: %d\n", fd);
  if ((bsent = sendto(fd, buffer, ETH_HLEN + sizeof(struct arp), 0, (struct sockaddr*)&addr, sizeof(addr))) == -1)
  {
    perror("[sendpacket] Failed to send packet: \n");
    return (-1);
  }
  debug("[sendpacket]: Sent %d bytes\n", bsent);
  return (0);
}

int readpacket(int fd, char *hwaddr)
{
  uint8_t       buffer[60];
  struct ethhdr *res;
  struct arp    *arp;

  debug("Reading on: %d\n", fd);
  if (recvfrom(fd, buffer, 60, 0, NULL, NULL) == -1)
  {
    perror("[readpacket]: Failed to read\n");
    return (-1);
  }
  res = (struct ethhdr*)buffer;
  if (res->h_proto != htons(ETH_P_ARP))
  {
    debug("[readpacket]: Got non arp packet\n");
    return (0);
  }
  arp = (struct arp*)(buffer + ETH_HLEN);
  if (arp->op != htons(2))
  {
    debug("[readpacket]: Got arp but not a reply\n");
    return (0);
  }
  memcpy(hwaddr, &(arp->src_hwaddr), ETH_ALEN);
  return (1);
}

int sendarp(const char *ifname, const char *dst_ip, char *hwaddr)
{
  uint32_t  local_ip;
  char      local_mac[ETH_ALEN];
  int       ifindex;
  int       sock_fd;
  int       read_ret;

  read_ret = 0;
  local_ip = 0;
  memset(local_mac, 0, ETH_ALEN);
  if (getifinfo(ifname, &local_ip, local_mac, &ifindex) != 0)
  {
    error("[sendarp]: getifinfo failed\n");
    return (-1);
  }
  debug("[sendarp]: getifinfo OK\n");
  if (init_arp_socket(&sock_fd, ifindex) != 0)
  {
    error("[sendarp]: init_arp_sock failed\n");
    return (-1);
  }
  debug("[sendarp]: init_arp_socket OK\n");
  if (sendpacket(local_mac, local_ip, inet_addr(dst_ip), ifindex, sock_fd) != 0)
  {
    error("[sendarp]: sendpacket failed\n");
    close(sock_fd);
    return (-1);
  }
  debug("[sendarp]: sendpacket OK\n");
  while (read_ret == 0)
  {
    debug("[sendarp]: reading packet\n");
    read_ret = readpacket(sock_fd, hwaddr);
  }
  if (read_ret == -1)
  {
    error("[sendarp]: readpacket failed\n");
    close(sock_fd);
    return (-1);
  }
  return (0);
}
