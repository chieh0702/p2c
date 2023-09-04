all: main

main: p2c.o
	g++ -rdynamic p2c.o -o p2c -ldl
.cpp.o:	
	g++ -c $<

clean:
	rm *.o p2c