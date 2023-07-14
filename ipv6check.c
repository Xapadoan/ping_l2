#include "ipv6check.h"

uint16_t ipv6check(uint8_t *packet, size_t payload_len)
{
  uint8_t   *pseudopacket;
  size_t    len = 40 + payload_len;
  uint16_t  sum;

  pseudopacket = NULL;
  if ((pseudopacket = malloc(len)) == NULL)
    return -1;
  memset(pseudopacket, 0, len);
  memcpy(pseudopacket, packet + 8, 16);
  memcpy(pseudopacket + 16, packet + 24, 16);
  memcpy(pseudopacket + 34, packet + 4, 2);
  memcpy(pseudopacket + 39, packet + 6, 1);
  memcpy(pseudopacket + 40, (uint8_t*)packet + 40, payload_len);

  sum = ipcheck(pseudopacket, len);
  free(pseudopacket);
  return sum;
}
