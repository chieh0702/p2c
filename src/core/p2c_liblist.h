#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <dirent.h>
#include <cstring>

#ifndef _P2C_ALERTER_H_
#define _P2C_ALERTER_H_
#include "p2c_alerter.h"
#endif
#ifndef _P2C_ARGTABLE_H_
#define _P2C_ARGTABLE_H_
#include "p2c_argtable.h"
#endif

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
    void callFunction(p2c_argtable);
};

p2c_liblist::~p2c_liblist()
{
    // free all library
    for (void *_lib : _core_lib)
        dlclose(_lib);
    for (void *_lib : _mod_lib)
        dlclose(_lib);
}

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
        if ((memcmp(entry->d_name, "p2c_core", 8) == 0) && (memcmp(strchr(entry->d_name, '.'), ".so", 3) == 0))
            this->_core_lib.push_back(dlopen(entry->d_name, RTLD_LAZY));
        else if ((memcmp(entry->d_name, "p2c_mod", 7) == 0) && (memcmp(strchr(entry->d_name, '.'), ".so", 3) == 0))
            this->_mod_lib.push_back(dlopen(entry->d_name, RTLD_LAZY));
        else
            continue;
        if ((_core_lib.back() == NULL))
        {
            _core_lib.pop_back();
            p2c_alerter::alerting(alert_level::ERROR, strcat((char *)"core libaray open failed:", entry->d_name));
        }
        if ((_mod_lib.back() == NULL))
        {
            _mod_lib.pop_back();
            p2c_alerter::alerting(alert_level::WARN, strcat((char *)"module libaray open failed:", entry->d_name));
        }
    }
    closedir(dirp);
}

void p2c_liblist::callFunction(p2c_argtable argtable)
{
    // TODO: definition function name and args
    for (void *_lib : _core_lib);
        //dlclose(_lib);
    for (void *_lib : _mod_lib)
        {
            dlsym(_lib,"main");
        }
}