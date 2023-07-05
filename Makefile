CC=gcc
EXE=ping_l2

OBJS=ping_l2.o putsockaddr.o putifaddr.o sendarp.o getgwaddr.o bindsock.o\
	sendether.o buildether.o getifinfo.o buildip.o ipcheck.o buildicmp.o

$(EXE): $(OBJS)
	$(CC) $^ -o $@

buildicmp.o: buildicmp.c buildicmp.h ipcheck.o
ipcheck.o: ipcheck.c ipcheck.h
buildip.o: buildip.c buildip.h ipcheck.o
getifinfo.o: getifinfo.c getifinfo.h debug.h
buildether.o: buildether.c buildether.h
sendether.o: sendether.c sendether.h debug.h putsockaddr.o
bindsock.o: bindsock.c bindsock.h debug.h
getgwaddr.o: getgwaddr.c getgwaddr.h debug.h
sendarp.o: sendarp.c sendarp.h debug.h bindsock.o sendether.o buildether.o getifinfo.o
putsockaddr.o: putsockaddr.c putsockaddr.h
putifaddr.o: putifaddr.c putifaddr.h putsockaddr.o
ping_l2.o: ping_l2.c ping_l2.h debug.h getifinfo.o sendarp.o getgwaddr.o bindsock.o buildether.o buildip.o buildicmp.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXE)

re: fclean $(EXE)
