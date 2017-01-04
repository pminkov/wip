# To deal with the Tabs getting converted to spaces, run vim as "vim -u NONE ./Makefile"
# $@ - left side of rule.
# $^ - right side of rule.

DEPS = threads.h pthread_utils.h

main: main.cc $(DEPS)
	g++ ./main.cc -o ./main -pthread

clean:
	rm -rf ./main
	rm -rf ./*.o
