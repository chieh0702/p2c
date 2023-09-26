#include <algorithm>

#include <p2c_liblist.h>
#include <p2c_alerter.h>
#include <p2c_argtable.h>

extern std::vector<std::string> p2c_lib_getCommend();
extern int p2c_mod_entry();
extern int p2c_gen_entry();

void runGUI();
bool haveModCmd(p2c_argtable,p2c_liblist);
bool haveGuiCmd(p2c_argtable,p2c_liblist);