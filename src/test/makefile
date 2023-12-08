CORE_PATH := ../core
BIN_PATH  := ../../bin
SRC_FILES := $(wildcard *.cpp)
BIN_FILES := $(patsubst %.cpp,%,$(SRC_FILES))
COLOR_GREEN := @printf "\e[1;32m"
COLOR_BLUE  := @printf "\e[1;34m"
COLOR_RESET := @printf "\e[0m"

all: argtable liblist split mod_website mod_normal gen_dockerfile mod_database

.cpp.o:
	g++ -I $(CORE_PATH) -c $<

argtable: p2c_test_argtable
	$(COLOR_GREEN)
	- ./$< -arg1 hello --arg2 ppo oop
	$(COLOR_RESET)
	make clean

liblist: p2c_test_liblist
	$(COLOR_GREEN)
	- ./$<
	$(COLOR_RESET)
	make clean

split: p2c_test_split
	$(COLOR_GREEN)
	- ./$<
	$(COLOR_RESET)
	make clean

mod_website: p2c_test_mod_website
	$(COLOR_GREEN)
	- ./$<
	$(COLOR_RESET)
	make clean

mod_normal: p2c_test_mod_normal
	$(COLOR_GREEN)
	- ./$< --website --dockerfile -f debian -c /bin:/bin -a /root/p2c:/root --env "PATH=/bin" -m "curl ifconfig.me >pubip.info" -r "apt update;apt install curl" -p 8080/TCP
	$(COLOR_RESET)
	make clean	

gen_dockerfile: p2c_test_gen_dockerfile
	$(COLOR_GREEN)
	- ./$<
	$(COLOR_BLUE)
	@echo "\nDockerfile generated:\n"
	@cat Dockerfile
	$(COLOR_RESET)
	make clean

mod_database: p2c_test_mod_database
	$(COLOR_GREEN)
	- ./$<
	$(COLOR_RESET)
	make clean

mod_compatibility: p2c_test_mod_compatibility
	$(COLOR_GREEN)
	- ./$<
	$(COLOR_RESET)
	-@ read -p "Press any key to continue clean..." var
	make clean

TARGETS := p2c_test_argtable p2c_test_liblist p2c_test_split \
           p2c_test_mod_website p2c_test_gen_dockerfile \
           p2c_test_mod_normal p2c_test_mod_database \
		   p2c_test_mod_compatibility

$(TARGETS): %: %.o
	g++ -rdynamic $< -o $@ -ldl
	rm $<

clean:
	-@ rm $(BIN_FILES) ./*.o export.sql Dockerfile 2>/dev/null
	-@ rm -rd ./p2c_test ./p2c_export