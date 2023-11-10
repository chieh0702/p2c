#include <p2c_lib.h>

#include <iostream>
#include <sstream>

std::vector<std::string> split(std::string str, std::string pattern)
{
    std::vector<std::string> result;
    while (str.find(pattern) != std::string::npos)
    {
        std::size_t pos = str.find(pattern);
        result.push_back(str.substr(0, pos));
        str = str.substr(pos + pattern.size());
    }
    result.push_back(str);
    return result;
}

class p2c_mod_normal : public p2c_mod
{
private:
    /* data */
public:
    p2c_mod_normal(){};
    ~p2c_mod_normal(){};
    virtual int entry(std::string args) override;
    virtual std::vector<std::string> getCommand() override;
};

extern p2c_mod *p2c_create_mod()
{
    return new p2c_mod_normal;
}

int p2c_mod_normal::entry(std::string args)
{
    std::stringstream ss;
    ss.str(args);
    std::string token;
    ss >> token;
    if (token == "-a" || token == "--add")
    {
    }
    else if (token == "-c" || token == "--copy")
    {
    }
    else if (token == "-e" || token == "--env")
    {
    }
    else if (token == "-f" || token == "--from")
    {
    }
    else if (token == "-h" || token == "--help")
    {
    }
    else if (token == "-i" || token == "--ignore")
    {
    }
    else if (token == "-m" || token == "--cmd")
    {
    }
    else if (token == "-n" || token == "--entrypoint")
    {
    }
    else if (token == "-o" || token == "--output")
    {
    }
    else if (token == "-p" || token == "--expose")
    {
    }
    else if (token == "-r" || token == "--run")
    {
    }
    else
    {
    }
    return 0;
}

std::vector<std::string> p2c_mod_normal::getCommand()
{
    std::vector<std::string> cmd{
        "-a", "--add",
        "-c", "--copy",
        "-e", "--env",
        "-f", "--from",
        "-h", "--help",
        "-i", "--ignore",
        "-m", "--cmd",
        "-n", "--entrypoint",
        "-o", "--output",
        "-p", "--expose",
        "-r", "--run"};
}
