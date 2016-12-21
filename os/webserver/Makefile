# To deal with the Tabs getting converted to spaces, run vim as "vim -u NONE ./Makefile"

DEPS = threads.h


%.o: %.c $(DEPS)
	gcc -c -o $@ $<


server: server.o
	gcc -o server server.c

clean:
	rm -rf ./server
	rm -rf ./*.o
