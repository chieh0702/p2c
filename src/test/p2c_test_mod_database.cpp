#define _ALERT_LEVEL_ 0

#include <p2c_lib.h>

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    p2c_liblist liblist;
    argTable = new p2c_argtable;
    liblist.callModFunc("-db password=owaspbwa");
    cout << argTable->getJSON() << '\n';
    return 0;
}
