#include "parseargs.h"

static int  autodetectfamily(char *target)
{
  int i;
  int len;

  i = 0;
  len = strlen(target);
  while (i < len)
  {
    if (target[i] == '.')
      return (AF_INET);
    else if (target[i] == ':')
      return (AF_INET6);
    i++;
  }
  return (-1);
}

static void putargs(struct args *args)
{
  debug("[parseargs] Got args:\n");
  debug("[parseargs]\tTarget: %s\n", args->target);
  debug("[parseargs]\tInterface: %s\n", args->interface);
  debug("[parseargs]\tCount: %d, Deadline %u, Timeout %u\n", args->count, args->deadline, args->timeout);
  if (args->family == AF_INET)
  {
    debug("[parseargs]\tFamily: AF_INET\n");
    debug("[parseargs]\tTOS: %02x, TTL: %u, len: %u\n", args->ipopts.v4.tos, args->ipopts.v4.ttl, args->ipopts.v4.len);
    debug("[parseargs]\tRecord: %s\n", args->ipopts.v4.record != 0 ? "true" : "false");
  } else if (args->family == AF_INET6) {
    debug("[parseargs]\tFamily: AF_INET6\n");
    debug("[parseargs]\tTC: %02x, Flow: %08x (%08x)\n", args->ipopts.v6.tc, args->ipopts.v6.flow, htonl(args->ipopts.v6.flow));
    debug("[parseargs]\tPlen: %u, HOP: %u\n", args->ipopts.v6.plen, args->ipopts.v6.hop);
  }
}

int parseargs(int argc, char **argv, struct args *args)
{
  int i;
  int flag_pos;
  int arg_pos;
  int arg_len;
  struct ipv4opts v4;
  struct ipv6opts v6;

  i = 1;
  memset(args, 0, sizeof(struct args));
  // default
  args->count = -1;
  args->deadline = 0;
  args->timeout = 0;
  args->interval = 1000000;
  args->size = 40;
  v4.tos = 0;
  v6.tc = 0;
  v4.ttl = 64;
  v6.hop = 64;
  v4.record = 0;
  v6.flow = 0x4000;
  while (i < argc)
  {
    debug("[parseargs] Parsing: %s\n", argv[i]);
    if (argv[i][0] == '-')
    {
      arg_len = strlen(argv[i]);
      flag_pos = 1;
      arg_pos = 1;
      while (flag_pos < arg_len)
      {
        if (argv[i][flag_pos] == '4')
        {
          arg_pos -= 1;
          args->family = AF_INET;
        }
        else if (argv[i][flag_pos] == '6')
        {
          arg_pos -= 1;
          args->family = AF_INET6;
        }
        else if (argv[i][flag_pos] == 'c')
          args->count = atoi(argv[i + arg_pos]);
        else if (argv[i][flag_pos] == 'I')
          memcpy(args->interface, argv[i + arg_pos], strlen(argv[i + arg_pos]));
        else if (argv[i][flag_pos] == 's')
          args->size = atoi(argv[i + arg_pos]);
        else if (argv[i][flag_pos] == 'Q')
        {
          v4.tos = atoi(argv[i + arg_pos]);
          v6.tc = atoi(argv[i + arg_pos]);
        }
        else if (argv[i][flag_pos] == 't')
        {
          v4.ttl = atoi(argv[i + arg_pos]);
          v6.hop = atoi(argv[i + arg_pos]);
        }
        else if (argv[i][flag_pos] == 'w')
          args->deadline = atoi(argv[i + arg_pos]);
        else if (argv[i][flag_pos] == 'W')
          args->timeout = atoi(argv[i + arg_pos]);
        else if (argv[i][flag_pos] == 'R')
        {
          arg_pos -= 1;
          v4.record = 1;
        }
        else if (argv[i][flag_pos] == 'F')
          v6.flow = atoi(argv[i + arg_pos]);
        else if (argv[i][flag_pos] == 'i')
          args->interval = atoi(argv[i + arg_pos]) * 1000000;
        arg_pos++;
        flag_pos++;
      }
      i += arg_len;
    } else {
      memcpy(args->target, argv[i], strlen(argv[i]));
    }
    i++;
  }
  if (strlen(args->target) < 1)
  {
    error("[parseargs]: usage error: Destination address requiered\n");
    return (-1);
  }
  if (args->family == 0)
  {
    args->family = autodetectfamily(args->target);
    if (args->family == -1)
    {
      error("[parseargs]: Not a valid target\n");
      return (-1);
    }
  }
  v4.len = sizeof (struct iphdr) + sizeof(struct icmphdr) + args->size;
  v6.plen = sizeof (struct icmphdr) + args->size;
  if (args->family == AF_INET)
    memcpy(&args->ipopts.v4, &v4, sizeof(struct ipv4opts));
  else if (args->family == AF_INET6)
    memcpy(&args->ipopts.v6, &v6, sizeof(struct ipv6opts));
  if (args->ipopts.v4.record != 0)
    args->ipopts.v4.len += 40;
  putargs(args);
  return (0);
}
