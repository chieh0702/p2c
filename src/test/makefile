CORE_PATH := /root/vscode/src/core
BIN_PATH := /root/vscode/bin
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
OUT_FILES := $(patsubst %.o,%.out,$(OBJ_FILES))
BIN_FILES := $(patsubst %.o,%,$(OBJ_FILES))
COLOR_GREEN := echo "\e[1;32m"
COLOR_RESET := echo "\e[0m"

all: argtable liblist 
%.out: %.o
	g++ -rdynamic -o $* $< -ldl
.cpp.o:
	g++ -I $(CORE_PATH) -c $<

argtable: p2c_test_argtable
	@ $(COLOR_GREEN)
	- ./$< -arg1 hello --arg2 ppo oop
	@ $(COLOR_RESET)
	@ make clean
p2c_test_argtable: p2c_test_argtable.o
	g++ -rdynamic -o $@ $< -ldl

liblist: p2c_test_liblist
	@ $(COLOR_GREEN)
	- ./$<
	@ $(COLOR_RESET)
	@ make clean
p2c_test_liblist: p2c_test_liblist.o
	g++ -rdynamic -o $@ $< -ldl

mod_normal: p2c_test_mod_normal
	@ $(COLOR_GREEN)
	- ./$< -f debian -c /bin:/bin
	@ $(COLOR_RESET)
	@ make clean	
p2c_test_mod_normal: p2c_test_mod_normal.o
	g++ -rdynamic $< -o $@ -ldl
	rm $<

clean:
	-@ rm $(BIN_FILES) $(OBJ_FILES) 2>/dev/null