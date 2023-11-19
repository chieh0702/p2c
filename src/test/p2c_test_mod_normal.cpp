#define _ALERT_LEVEL_ 0

#include <p2c_lib.h>

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    p2c_liblist libList;
    argTable = p2c_argtable(argc, argv);
    cout << argTable.getJSON() << '\n';
    while (argTable.getArg("command").size())
    {
        libList.callModFunc(argTable.getArg("command"));
        cout << argTable.getJSON();
    }
    cout << argTable.getJSON() << '\n';
    p2c_alerter::alerting(DEBUG, "Test done");
    return 0;
}