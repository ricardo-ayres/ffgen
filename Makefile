default: ffgen

ffgen: ff.o sierp.o geom.o

clean:
	rm ffgen *.o 

