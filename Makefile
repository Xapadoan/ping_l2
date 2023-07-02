CC=gcc
EXE=ping_l2

OBJS=ping_l2.o putsockaddr.o putifaddr.o getifname.o debug.o sendarp.o getgwaddr.o

$(EXE): $(OBJS)
	$(CC) $^ -o $@

getgwaddr.o: getgwaddr.c getgwaddr.h
sendarp.o: sendarp.c sendarp.h
putsockaddr.o: putsockaddr.c putsockaddr.h
debug.o: debug.c debug.h
getifname.o: getifname.c getifname.h
putifaddr.o: putifaddr.c putifaddr.h
ping_l2.o: ping_l2.c ping_l2.h

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXE)

re: fclean $(EXE)
