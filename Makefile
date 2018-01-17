CFLAGS="-lm"

default: ffgen

ffgen: ff.o chaos.o geom.o

clean:
	rm ffgen *.o 

