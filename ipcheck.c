#include "ipcheck.h"

uint16_t  ipcheck(uint8_t *data, size_t length)
{
  uint32_t  acc = 0xffff;
  size_t    i = 0;

  while (i + 1 < length) {
    uint16_t  word;
    memcpy(&word, data + i, 2);
    acc += ntohs(word);
    if (acc > 0xffff) {
      acc -= 0xffff;
    }
    i += 2;
  }

  return htons(~acc);
}
