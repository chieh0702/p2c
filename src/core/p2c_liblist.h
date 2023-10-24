#ifndef _P2C_LIBLIST_H_
#define _P2C_LIBLIST_H_

#include <iostream>
#include <vector>
#include <map>
#include <dlfcn.h>
#include <dirent.h>
#include <cstring>

#include <p2c_alerter.h>
#include <p2c_argtable.h>

class p2c_liblist
{
private:
    std::vector<void *> _mod_lib;
    std::vector<void *> _gen_lib;
    std::map<std::string, void *> _mod_map;
    std::map<std::string, void *> _gen_map;

public:
    p2c_liblist() { this->loadLibrary(); };
    ~p2c_liblist();
    void loadLibrary();
    // TODO: call dll function
    int callModFunc(std::vector<std::string>);
    int callModFunc(std::string);
    int callGenFunc(std::vector<std::string>);
    int callGenFunc(std::string);
    std::vector<std::string> getModCmd();
    std::vector<std::string> getGenCmd();
};

p2c_liblist::~p2c_liblist()
{
    // free all library
    for (void *_lib : _gen_lib)
        dlclose(_lib);
    for (void *_lib : _mod_lib)
        dlclose(_lib);
}

void p2c_liblist::loadLibrary()
{
    DIR *dirp = opendir("./"); // TODO: change to /lib/p2c/modure/
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
            this->_gen_lib.push_back(dlopen(entry->d_name, RTLD_LAZY));
        else if ((memcmp(entry->d_name, "p2c_mod", 7) == 0) && (memcmp(strchr(entry->d_name, '.'), ".so", 3) == 0))
            this->_mod_lib.push_back(dlopen(entry->d_name, RTLD_LAZY));
        else
            continue;
        if ((_gen_lib.back() == NULL))
        {
            _gen_lib.pop_back();
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

int p2c_liblist::callModFunc(std::vector<std::string> args)
{
    // dlclose(_lib);
    for (void *_lib : _mod_lib)
    {
        dlsym(_lib, "p2c_mod_entry");
    }
}
int p2c_liblist::callGenFunc(std::vector<std::string> args)
{
    for (void *_lib : _gen_lib)
        dlsym(_lib, "p2c_gen_entry");
}

std::vector<std::string> p2c_liblist::getModCmd() //TODO:merge to init
{
    for (void *_lib : _mod_lib)
    {
        p2c_lib_getCommand_t *getcmd = (p2c_lib_getCommand_t *)dlsym(_lib, "p2c_lib_getCommand");
        p2c_mod_entry_t *entry = (p2c_mod_entry_t *)dlsym(_lib,"p2c_mod_entry");
        //TODO:error handle
        for (std::string key : getcmd())
            this->_mod_map[key] = entry;
    }
}
std::vector<std::string> p2c_liblist::getGenCmd()
{

}

#endif