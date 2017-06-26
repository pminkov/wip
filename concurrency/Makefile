# To deal with the Tabs getting converted to spaces, run vim as "vim -u NONE ./Makefile"
# $@ - left side of rule.
# $^ - right side of rule.

DEPS = threads.h pthread_utils.h

main: main.cc $(DEPS)
	g++ ./main.cc -o ./main -pthread

rw_lock: rw_lock.cc $(DEPS)
	g++ ./rw_lock.cc -o ./rw_lock -pthread

clean:
	rm -rf ./main
	rm -rf ./*.o
