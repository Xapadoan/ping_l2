CC=gcc
EXE=ping_l2

OBJS=ping_l2.o putsockaddr.o putifaddr.o getifname.o sendarp.o getgwaddr.o

$(EXE): $(OBJS)
	$(CC) $^ -o $@

getgwaddr.o: getgwaddr.c getgwaddr.h debug.h
sendarp.o: sendarp.c sendarp.h debug.h
putsockaddr.o: putsockaddr.c putsockaddr.h
getifname.o: getifname.c getifname.h debug.h putifaddr.o
putifaddr.o: putifaddr.c putifaddr.h putsockaddr.o
ping_l2.o: ping_l2.c ping_l2.h getifname.o sendarp.o getgwaddr.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXE)

re: fclean $(EXE)
