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

clean:
	- cd $(BIN_PATH) && rm $(BIN_FILES)