#include <p2c_lib.h>

class p2c_gen_dockerfile:public p2c_mod
{
private:
    
public:
    int entry(std::string);

};


extern p2c_mod *p2c_create_mod()
{
    return new p2c_gen_dockerfile;
}