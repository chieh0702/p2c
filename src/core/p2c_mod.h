#ifndef _P2C_MOD_H_
#define _P2C_MOD_H_

#include <iostream>
#include <vector>

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

#endif