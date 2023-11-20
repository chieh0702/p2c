#include <p2c_lib.h>

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    p2c_liblist libList;
    argTable = new p2c_argtable;
    argTable->initArgs(argc, argv);
    queue<string> *command = argTable->getArg("command");
    if (command)
        while (!command->empty()) // TODO:What if 'command' leaves something like --gui, -h, gen_cmd etc...
        {
            if (command->front() == "--gui")
                runGUI();
            else
                libList.callModFunc(command->front());
            command->pop();
        }
    //libList.callGenFunc(argTable->getArg("command")); //TODO
    return 0;
}
