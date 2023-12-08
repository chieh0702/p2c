#define _ALERT_LEVEL_ 0

#include <p2c_lib.h>

#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char const *argv[])
{
    p2c_liblist liblist;
    argTable = new p2c_argtable;
    system("mkdir p2c_test");
    system("echo 'Hello World!' > p2c_test/hello.txt");
    argTable->addArg("ADD", "./p2c_test/hello.txt","/");
    argTable->addArg("COPY", "./p2c_test/","/");
    liblist.callModFunc("-cmp");
    cout << argTable->getJSON() << '\n';
    return 0;
}
