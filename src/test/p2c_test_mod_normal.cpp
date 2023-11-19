#define _ALERT_LEVEL_ 0

#include <p2c_lib.h>

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) // TODO:reply to p2c.cpp
{
    p2c_liblist libList;
    p2c_argtable argTable = p2c_argtable(argc, argv);
    cout << argTable.getJSON() << '\n';
    queue<string> *command = argTable.getArg("command");
    while (!command->empty())
    {
        p2c_alerter::alerting(DEBUG, "Test...");
        libList.callModFunc(command->front());
        command->pop();
        cout << argTable.getJSON() << '\n';
    }
    p2c_alerter::alerting(DEBUG, "Test done");
    return 0;
}