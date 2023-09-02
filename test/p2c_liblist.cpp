#include "../src/p2c_liblist.h"

int main(int argc, char const *argv[])
{
    p2c_liblist libList = p2c_liblist();
    libList.loadModule();
    return 0;
}
