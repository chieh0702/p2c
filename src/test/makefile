CORE_PATH := /root/vscode/src/core
BIN_PATH := /root/vscode/bin
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
OUT_FILES := $(patsubst %.o,%.out,$(OBJ_FILES))
BIN_FILES := $(patsubst %.o,%,$(OBJ_FILES))

all: $(OUT_FILES)
%.out: %.o
	g++ -rdynamic -o $(BIN_PATH)/$* $< -ldl
.cpp.o:
	g++ -I $(CORE_PATH) -c $<

argtable: p2c_test_argtable
	$(BIN_PATH)/$< -arg1 hello --arg2 ppo oop
	rm $(BIN_PATH)/$<
p2c_test_argtable: p2c_test_argtable.o
	g++ -rdynamic -o $(BIN_PATH)/$@ $< -ldl
	rm $<

clean:
	- cd $(BIN_PATH) && rm $(BIN_FILES)