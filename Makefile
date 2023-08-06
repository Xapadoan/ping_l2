CC=gcc
EXE=ping_l2

OBJS=ping_l2.o putsockaddr.o putifaddr.o sendarp.o getgwaddr.o bindsock.o\
	sendether.o buildether.o getifinfo.o buildip.o ipcheck.o buildicmp.o\
	buildipv6.o ipv6check.o buildicmpv6.o getgwhwaddrv6.o parseargs.o readpacket.o\
	timefromstart.o

$(EXE): $(OBJS)
	$(CC) $^ -o $@

timefromstart.o: timefromstart.c timefromstart.h
readpacket.o: readpacket.c readpacket.h debug.h
parseargs.o: parseargs.c parseargs.h debug.h args.h
getgwhwaddrv6.o: getgwhwaddrv6.c getgwhwaddrv6.h debug.h ipv6check.o buildipv6.o buildether.o sendether.o ipv6opts.h
buildicmpv6.o: buildicmpv6.c buildicmpv6.h ipv6check.o
ipv6check.o: ipv6check.c ipv6check.h ipcheck.o
buildipv6.o: buildipv6.c buildipv6.h ipv6opts.h
buildicmp.o: buildicmp.c buildicmp.h ipcheck.o
ipcheck.o: ipcheck.c ipcheck.h
buildip.o: buildip.c buildip.h ipcheck.o ipv4opts.h
getifinfo.o: getifinfo.c getifinfo.h debug.h
buildether.o: buildether.c buildether.h
sendether.o: sendether.c sendether.h debug.h putsockaddr.o
bindsock.o: bindsock.c bindsock.h debug.h
getgwaddr.o: getgwaddr.c getgwaddr.h debug.h
sendarp.o: sendarp.c sendarp.h debug.h bindsock.o sendether.o buildether.o getifinfo.o
putsockaddr.o: putsockaddr.c putsockaddr.h
putifaddr.o: putifaddr.c putifaddr.h putsockaddr.o
ping_l2.o: ping_l2.c ping_l2.h debug.h getifinfo.o sendarp.o getgwaddr.o bindsock.o buildether.o buildip.o buildicmp.o buildicmpv6.o getgwhwaddrv6.o args.h readpacket.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXE)

re: fclean $(EXE)
