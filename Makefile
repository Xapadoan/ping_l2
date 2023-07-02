CC=gcc
EXE=ping_l2

OBJS=ping_l2.o put_sockaddr.o put_ifaddr.o getrecvif.o debug.o sendarp.o getgwaddr.o

$(EXE): $(OBJS)
	$(CC) $^ -o $@

getgwaddr.o: getgwaddr.c getgwaddr.h
sendarp.o: sendarp.c sendarp.h
put_sockaddr.o: put_sockaddr.c put_sockaddr.h
debug.o: debug.c debug.h
getrecvif.o: getrecvif.c getrecvif.h
put_ifaddr.o: put_ifaddr.c put_ifaddr.h
ping_l2.o: ping_l2.c ping_l2.h

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXE)

re: fclean $(EXE)
