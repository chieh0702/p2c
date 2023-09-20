BIN_PATH := /root/vscode/bin

all: p2c

p2c: p2c.o
	g++ -rdynamic p2c.o -o $(BIN_PATH)/p2c -ldl
.cpp.o:
	g++ -c $<

clean:
	rm *.o p2c