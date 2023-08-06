#include "readpacket.h"

static int  extractv4data(uint8_t *buffer, struct packetdata *data)
{
  struct iphdr    *ip;
  struct icmphdr  *icmp;
  struct timeval  *sent;
  struct timeval  now;

  memset(data, 0, sizeof(struct packetdata));
  ip = (struct iphdr*)(buffer + ETH_HLEN);
  if (ip->protocol != IPPROTO_ICMP)
    return (1);
  data->ttl = ip->ttl;
  icmp = (struct icmphdr*)(buffer + ETH_HLEN + ip->ihl * 4);
  data->seq = ntohs(icmp->un.echo.sequence);
  if (inet_ntop(AF_INET, &(ip->saddr), data->from, INET_ADDRSTRLEN) == NULL)
  {
    perror("[extractv4data]: inet_ntop");
    return (-1);
  }
  sent = (struct timeval*)(buffer + ETH_HLEN + ip->ihl * 4 + 8);
  if (gettimeofday(&now, NULL) != 0)
  {
    perror("[extractv4data]: gettimeofday");
    return (-1);
  }
  printf("Sec: %u - %u, USec: %u\n", now.tv_sec, sent->tv_sec, now.tv_usec - sent->tv_usec);
  data->rtt = (now.tv_sec - sent->tv_sec) * 1000 + (double)(now.tv_usec - sent->tv_usec) / 1000;
  return (0);
}

static int  extractv6data(uint8_t *buffer, struct packetdata *data)
{
  struct pl2_ipv6hdr  *ip;
  struct icmphdr  *icmp;
  struct timeval  *sent;
  struct timeval  now;

  memset(data, 0, sizeof(struct packetdata));
  ip = (struct pl2_ipv6hdr*)(buffer + ETH_HLEN);
  if (ip->next != IPPROTO_ICMPV6)
    return (1);
  data->ttl = ip->hop;
  icmp = (struct icmphdr*)(buffer + ETH_HLEN + 40);
  if (icmp->type != 129)
    return (1);
  data->seq = ntohs(icmp->un.echo.sequence);
  if (inet_ntop(AF_INET6, &(ip->src), data->from, INET6_ADDRSTRLEN) == NULL)
  {
    perror("[extractv6data]: inet_ntop");
    return (-1);
  }
  sent = (struct timeval*)(buffer + ETH_HLEN + 40 + 8);
  if (gettimeofday(&now, NULL) != 0)
  {
    perror("[extractv6data]: gettimeofday");
    return (-1);
  }
  data->rtt = (now.tv_sec - sent->tv_sec) * 1000 + (double)(now.tv_usec - sent->tv_usec) / 1000;
  return (0);
}

int readpacket(int fd, uint8_t *buffer, unsigned int len)
{
  int           bytes;
  struct ethhdr *eth;
  struct packetdata data;
  int               ret;

  memset(buffer, 0, len);
  bytes = recv(fd, buffer, len, 0);
  if (bytes < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
    return 0;
  else if (bytes < 0)
  {
    perror("[readpacket]: recv");
    return (-1);
  }
  // Do stuf
  eth = (struct ethhdr*)buffer;
  if (ntohs(eth->h_proto) == ETH_P_IP)
  {
    ret = extractv4data(buffer, &data);
    if (ret < 0)
    {
      error("[readpacket]: Failed to extract ipv4 data\n");
      return (-1);
    } else if (ret > 0) {
      return readpacket(fd, buffer, len);
    }
  } else if (ntohs(eth->h_proto) == ETH_P_IPV6) {
    ret = extractv6data(buffer, &data);
    if (ret < 0)
    {
      error("[readpacket]: Failed to extract ipv6 data\n");
      return (-1);
    } else if (ret > 0) {
      return readpacket(fd, buffer, len);
    }
  } else {
    debug("[readpacket]: Unknown ETH type: %d\n", ntohs(eth->h_proto));
    return readpacket(fd, buffer, len);
  }
  printf("%d bytes from %s: icmp_seq=%u ttl=%u time=%.02fms\n", bytes, data.from, data.seq, data.ttl, data.rtt);
  return bytes;
}
