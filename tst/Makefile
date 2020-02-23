all:
	gcc \
	    -fprofile-arcs \
	    -ftest-coverage \
	    -Wall \
	    -Werror \
	    -I../include \
	    ../src/bitstream.c *.c \
	    -o main
	./main
