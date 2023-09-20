#include "p2c_lib.h"

int main(int argc, char const *argv[])
{
    p2c_argtable argTable = p2c_argtable(argc, argv);
    p2c_liblist libList = p2c_liblist();
    // TODO: call mod function
    libList.callFunction(argTable);
    return 0;
}
