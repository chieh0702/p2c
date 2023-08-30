#include <iostream>
#include <vector>
#include <dlfcn.h>

class p2c_modlist
{
private:
    std::vector<void*> _mod_lib;
public:
    p2c_modlist(){};
    ~p2c_modlist(){};
    void loadModule();
};

void p2c_modlist::loadModule()
{

}