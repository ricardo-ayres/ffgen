CFLAGS=-g -O0 -lm

default: ffgen

ffgen: ff.o chaos.o geom.o

install:
	cp -v ffgen ~/Desktop/ffgen-samples/ffgen

clean:
	rm ffgen *.o 

