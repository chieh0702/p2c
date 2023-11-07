#include <p2c_lib.h>

using namespace std;

int main(int argc, char const *argv[])
{
    argTable = p2c_argtable(argc, argv);
    p2c_liblist libList = p2c_liblist();
    while (libList.callModFunc(argTable.getArg("command")))
    {
        if (haveGuiCmd(argTable))
            runGUI();
    }
    libList.callGenFunc(argTable.getArg("command"));
    return 0;
}

bool haveGuiCmd(p2c_argtable argTable)
{
    vector<string> curCmd = argTable.getArg("command");
    if (find(curCmd.begin(), curCmd.end(), "--gui") != curCmd.end())
        return true;
    return false;
}

