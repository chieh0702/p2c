#include <p2c_lib.h>

int main(int argc, char const *argv[])
{
    p2c_liblist libList = p2c_liblist();
    libList.loadLibrary();
    return 0;
}
