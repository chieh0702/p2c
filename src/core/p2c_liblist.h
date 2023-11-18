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
#include <p2c_mod.h>

class p2c_liblist
{
private:
    std::map<std::string, p2c_mod *> _mod_map;
    std::map<std::string, p2c_mod *> _gen_map;
    std::vector<void *> _opened_lib;
    std::vector<p2c_mod *> _created_mod;

public:
    p2c_liblist() { this->loadLibrary(); };
    ~p2c_liblist();
    void loadLibrary();
    int callModFunc(std::vector<std::string>);
    int callModFunc(std::string);
    int callGenFunc(std::vector<std::string>);
    int callGenFunc(std::string);
};

p2c_liblist::~p2c_liblist()
{
    // free all library
    for (p2c_mod *mod : _created_mod)
        delete mod;
    for (void *_lib : _opened_lib)
        dlclose(_lib);
}

void p2c_liblist::loadLibrary()
{
    DIR *dirp = opendir("/root/vscode/lib"); // TODO: change to /lib/p2c/module/
    if (!dirp)
    {
        std::cerr << "Open module directory failed: " << strerror(errno) << '\n';
        return;
    }
    while (1)
    {
        dirent *entry = readdir(dirp);
        if (!entry)
            break;
        if (memcmp(entry->d_name, "p2c", 3) != 0) // ignore otherFile
            continue;
        // push dll point to map
        if (((memcmp(entry->d_name, "p2c_mod", 7) == 0) || (memcmp(entry->d_name, "p2c_gen", 7) == 0)) && (memcmp(strchr(entry->d_name, '.'), ".so", 3) == 0))
        {
            void *mod = dlopen(entry->d_name, RTLD_LAZY);
            if (!mod)
            {
                p2c_alerter::alerting(alert_level::WARN, "library load failed:", entry->d_name);
                dlerror();
                continue;
            }
            this->_opened_lib.push_back(mod);
            p2c_create_mod_t *create_mod = (p2c_create_mod_t *)dlsym(mod, "p2c_create_mod");
            if (dlerror())
            {
                p2c_alerter::alerting(alert_level::WARN, "library open failed:", dlerror());
                continue;
            }
            p2c_mod *new_mod = create_mod();
            this->_created_mod.push_back(new_mod);
            for (std::string key : new_mod->getCommand())
            {
                if ((memcmp(entry->d_name, "p2c_mod", 7) == 0))
                    this->_mod_map[key] = new_mod;
                else
                    this->_gen_map[key] = new_mod;
            }
        }
        else
            continue;
    }
    closedir(dirp);
    p2c_alerter::alerting(alert_level::DEBUG, "loaded", _created_mod.size(), "library.");
}

int p2c_liblist::callModFunc(std::vector<std::string> args)
{
    int sum = 0;
    for (std::string arg : args)
        sum += this->callModFunc(arg);
    return sum;
}
int p2c_liblist::callModFunc(std::string arg)
{
    if (this->_mod_map.count(arg))
        return !this->_mod_map[arg]->entry();
    else
        return 0;
}
int p2c_liblist::callGenFunc(std::vector<std::string> args)
{
    for (std::string arg : args)
        this->callGenFunc(arg);
}
int p2c_liblist::callGenFunc(std::string arg)
{
    if (this->_mod_map.count(arg))
        return !this->_gen_map[arg]->entry();
    else
        return 0;
}

#endif