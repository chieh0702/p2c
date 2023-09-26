#include <p2c_lib.h>

extern std::vector<std::string> p2c_lib_getCommend()
{
    std::vector<std::string> list={"dockerfile","df"};
    return list;
}

extern int p2c_gen_entry()
{
    return 0;
}