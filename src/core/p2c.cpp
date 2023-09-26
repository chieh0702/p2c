#include <p2c_lib.h>

using namespace std;
int main(int argc, char const *argv[])
{
    p2c_argtable argTable = p2c_argtable(argc, argv);
    p2c_liblist libList = p2c_liblist();
    while (haveModCmd(argTable, libList))
    {
        libList.callModFunc(argTable);
        if (haveGuiCmd(argTable))
            runGUI();
    }
    libList.callGenFunc(argTable);
    return 0;
}

bool haveModCmd(p2c_argtable argTable, p2c_liblist libList)
{
    vector<string> modCmd = libList.getModCmd();
    vector<string> curCmd = argTable.getArg("commend");
    for (string cmd : curCmd)
        if (find(modCmd.begin(), modCmd.end(), cmd) != modCmd.end())
            return true;
    return false;
}
bool haveGuiCmd(p2c_argtable argTable)
{
    vector<string> curCmd = argTable.getArg("commend");
    if (find(curCmd.begin(), curCmd.end(), "--gui") != curCmd.end())
        return true;
    return false;
}