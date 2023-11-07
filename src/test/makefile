CORE_PATH := /root/vscode/src/core
BIN_PATH := /root/vscode/bin
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
OUT_FILES := $(patsubst %.o,%.out,$(OBJ_FILES))
BIN_FILES := $(patsubst %.o,%,$(OBJ_FILES))

all: $(OUT_FILES)
%.out: %.o
	g++ -rdynamic -o $* $< -ldl
.cpp.o:
	g++ -I $(CORE_PATH) -c $<

argtable: p2c_test_argtable
	./$< -arg1 hello --arg2 ppo oop
	make clean
p2c_test_argtable: p2c_test_argtable.o
	g++ -rdynamic -o $@ $< -ldl

liblist: p2c_test_liblist
	./$<
	make clean
p2c_test_liblist: p2c_test_liblist.o
	g++ -rdynamic -o $@ $< -ldl


clean:
	- rm $(BIN_FILES) $(OBJ_FILES)