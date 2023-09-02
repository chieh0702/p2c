#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <dirent.h>
#include <cstring>

class p2c_liblist
{
private:
    std::vector<void *> _core_lib;
    std::vector<void *> _mod_lib;

public:
    p2c_liblist(){this->loadModule();};
    ~p2c_liblist(){};
    void loadModule();
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
        if (strncmp(entry->d_name, "p2c", 3) != 0) // ignore otherfile
            continue;
        // TODO: push dll point to vector
        // void *mod = dlopen("mod.so", RTLD_LAZY);
        if (strstr(entry->d_name, "p2c_core") != NULL)
            std::cout << "core:" << entry->d_name << '\n';
        else if (strstr(entry->d_name, "p2c_mod") != NULL)
            std::cout << "mod:" << entry->d_name << '\n';
        else
            std::cout << "other:" << entry->d_name << '\n';
    }
    closedir(dirp);
}