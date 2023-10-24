#include <p2c_lib.h>

extern std::vector<std::string> p2c_lib_getCommand()
{
    std::vector<std::string> list={"--dockerfile","-df"};
    return list;
}

extern int p2c_gen_entry(std::string)
{
    return 0;
}