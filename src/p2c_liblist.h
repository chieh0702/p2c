#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <dirent.h>
#include <cstring>
#include "p2c_alerter.h"

class p2c_liblist
{
private:
    std::vector<void *> _core_lib;
    std::vector<void *> _mod_lib;

public:
    p2c_liblist() { this->loadModule(); };
    ~p2c_liblist();
    void loadModule();
    // TODO: call dll function
};

void p2c_liblist::loadModule()
{
    DIR *dirp = opendir("./");
    if (!dirp)
    {
        std::cerr << "Open moudule directory failed: " << strerror(errno) << '\n';
        return;
    }
    while (1)
    {
        dirent *entry = readdir(dirp);
        if (!entry)
            break;
        if (memcmp(entry->d_name, "p2c", 3) != 0) // ignore otherfile
            continue;
        // push dll point to vector
        if (memcmp(entry->d_name, "p2c_core", 8) != 0)
            this->_core_lib.push_back(dlopen(entry->d_name, RTLD_LAZY));
        else if (memcmp(entry->d_name, "p2c_mod", 7) == 0)
            this->_mod_lib.push_back(dlopen(entry->d_name, RTLD_LAZY));
        else
            continue;
        if ((_core_lib.back() == NULL))
        {
            _core_lib.pop_back();
            p2c_alerter::alerting(alert_level::ERROR, strcat("core libaray open failed:", entry->d_name));
        }
        if ((_mod_lib.back() == NULL))
        {
            _mod_lib.pop_back();
            p2c_alerter::alerting(alert_level::WARN, strcat("module libaray open failed:", entry->d_name));
        }
    }
    closedir(dirp);
}

p2c_liblist::~p2c_liblist()
{
    // TODO: free all library
}