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
    virtual int entry(std::string, std::string)
    {
        p2c_alerter::alerting(ERROR, "mod entry undefine");
        return 1;
    };
    virtual std::vector<std::string> getCommand()
    {
        p2c_alerter::alerting(ERROR, "mod getCommand() undefine");
        std::vector<std::string> null;
        return null;
    };
    virtual std::string getHelp()
    {
        p2c_alerter::alerting(ERROR, "mod getHelp() undefine");
        return "";
    };
};

typedef p2c_mod *p2c_create_mod_t();
// extern "C" p2c_mod *p2c_create_mod() { return new p2c_mod; }

#endif