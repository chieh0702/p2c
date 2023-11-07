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

class p2c_mod
{
private:
public:
    p2c_mod(){};
    ~p2c_mod(){};
    virtual int entry() { return entry(""); };
    virtual int entry(std::string){};
    virtual std::vector<std::string> getCommand(){};
};

extern p2c_mod *p2c_create_mod();
typedef p2c_mod *p2c_create_mod_t();
extern void p2c_destroy(p2c_mod *entity);
typedef void p2c_destroy_t(p2c_mod);

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
    // TODO: call dll function
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
        // push dll point to map
        if (((memcmp(entry->d_name, "p2c_mod", 7) == 0) || (memcmp(entry->d_name, "p2c_gen", 7) == 0)) && (memcmp(strchr(entry->d_name, '.'), ".so", 3) == 0))
        {
            void *mod = dlopen(entry->d_name, RTLD_LAZY);
            if (!mod)
            {
                p2c_alerter::alerting(alert_level::WARN, strcat((char *)"libaray load failed:", entry->d_name));
                dlerror();
                continue;
            }
            this->_opened_lib.push_back(mod);
            p2c_create_mod_t *create_mod = (p2c_create_mod_t *)dlsym(mod, "p2c_create_mod");
            if (dlerror())
            {
                p2c_alerter::alerting(alert_level::WARN, strcat((char *)"libaray open failed:", dlerror()));
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
}

int p2c_liblist::callModFunc(std::vector<std::string> args)
{
    for (std::string arg : args)
        this->_mod_map[arg]->entry();
}
int p2c_liblist::callModFunc(std::string arg)
{
    this->_mod_map[arg]->entry();
}
int p2c_liblist::callGenFunc(std::vector<std::string> args)
{
    for (std::string arg : args)
        this->_gen_map[arg]->entry();
}
int p2c_liblist::callGenFunc(std::string arg)
{
    this->_gen_map[arg]->entry();
}

#endif