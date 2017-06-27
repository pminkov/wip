# To deal with the Tabs getting converted to spaces, run vim as "vim -u NONE ./Makefile"
# $@ - left side of rule.
# $^ - right side of rule.

DEPS = threads.h pthread_utils.h

main: main.cc $(DEPS)
	g++ ./main.cc -o ./main -pthread

rw_lock: rw_lock.o
	g++ -o $@ $^

wait_for_threads: wait_for_threads.o
	g++ -o $@ $^

clean:
	rm -rf ./main
	rm -rf ./rw_lock
	rm -rf ./wait_for_threads
	rm -rf ./*.o
