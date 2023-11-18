#include <p2c_lib.h>

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    argTable = p2c_argtable(argc, argv);
    p2c_liblist libList = p2c_liblist();
    while (libList.callModFunc(argTable.getArg("command")))
    {
        cout<<argTable.getJSON();
    }
    return 0;
}