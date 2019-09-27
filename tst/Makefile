all:
	gcc \
	    -fprofile-arcs \
	    -ftest-coverage \
	    -Wall \
	    -Werror \
	    -I.. \
	    ../bitstream.c *.c \
	    -o main
	./main
