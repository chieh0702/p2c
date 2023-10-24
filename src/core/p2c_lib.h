#include <algorithm>

#include <p2c_liblist.h>
#include <p2c_alerter.h>
#include <p2c_argtable.h>
#include <p2c_gui.h>

extern std::vector<std::string> p2c_lib_getCommand();
typedef std::vector<std::string> p2c_lib_getCommand_t();
extern int p2c_mod_entry(std::string);
typedef int p2c_mod_entry_t(std::string);
extern int p2c_gen_entry(std::string);
typedef int p2c_gen_entry_t(std::string);

bool haveModCmd(p2c_argtable, p2c_liblist);
bool haveGuiCmd(p2c_argtable);