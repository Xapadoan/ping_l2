#include "getgwaddr.h"

uint32_t  getgwaddr(const char *ifname)
{
  FILE      *f;
  char      line[100];
  int       dest_offset;
  int       gw_offset;
  char      gw_str[9];
  uint32_t  gwaddr;

  gwaddr = 0;
  memset(gw_str, 0, 9);
  dest_offset = strlen(ifname) + 1;
  gw_offset = strlen(ifname) + 10;
  f = fopen("/proc/net/route", "r");
  if (f == NULL)
  {
    warn("[getgwaddr] Couln't open /proc/net/route, falling back on default gateway adress: %08x\n", DEFAULT_GWADDR);
    return 0x0000fea9;
  }
  while (fgets(line, 100, f))
  {
    if (strncmp(line, ifname, strlen(ifname)) == 0 && strncmp(line + dest_offset, "00000000", 8) == 0)
    {
      memcpy(gw_str, line + gw_offset, 8);
      debug("[getgwaddr] Got gwaddr %s as string\n", gw_str);
      gwaddr = strtol(gw_str, NULL, 16);
      debug("[getgwaddr] Got gwaddr %08x as number\n", gwaddr);
      fclose(f);
      return (gwaddr);
    }
  }
  warn("[getgwaddr] Couldn't find gateway address, falling back on default: %08x\n", DEFAULT_GWADDR);
}
