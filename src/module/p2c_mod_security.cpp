#include <p2c_lib.h>

class p2c_mod_security : public p2c_mod
{
public:
    p2c_mod_security()
    {
        p2c_alerter::alerting(DEBUG, "mod security init");
    };
    ~p2c_mod_security(){};
    virtual int entry(std::string, std::string) override
    {
        argTable->addArg("RUN", "cd /etc/apache2;rm apache2.conf;ln -s /etc/apache2/apache2-modsecurity-crs-block.conf apache2.conf");
        return 0;
    };
    virtual std::vector<std::string> getCommand() override
    {
        std::vector<std::string> cmd{"--security"};
        return cmd;
    };
};

extern "C" p2c_mod *p2c_create_mod()
{
    return new p2c_mod_security;
}