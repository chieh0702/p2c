#include <p2c_lib.h>

#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

class p2c_mod_compatibility : public p2c_mod
{
private:
public:
    p2c_mod_compatibility(){};
    ~p2c_mod_compatibility(){};
    virtual int entry(std::string, std::string)
    {
        system("mkdir p2c_export");
        std::queue<std::string> *add = argTable->getArg("ADD");
        std::queue<std::string> *copy = argTable->getArg("COPY");
        int add_size = add->size();
        for (int i = 0; i < add_size; i++)
        {
            p2c_alerter::alerting(DEBUG, "mod compatibility: add " + add->front());
            if (i % 2 == 0)
            {
                std::string path = add->front();
                std::vector<std::string> path_split = split_all(path, "/");
                std::string filename = path_split[path_split.size() - 1];
                if (filename.empty())
                    filename = path_split[path_split.size() - 2];
                system(("cp -r " + add->front() + " ./p2c_export").c_str());
                add->pop();
                add->push("./p2c_export/" + filename);
            }
            else
            {
                add->push(add->front());
                add->pop();
            }
        }
        int copy_size = copy->size();
        for (int i = 0; i < copy_size; i++)
        {
            p2c_alerter::alerting(DEBUG, "mod compatibility: copy " + copy->front());
            if (i % 2 == 0)
            {
                std::vector<std::string> path_split = split_all(copy->front(), "/");
                std::string filename = path_split[path_split.size() - 1];
                if (filename.empty())
                    filename = path_split[path_split.size() - 2];
                system(("tar chvf ./p2c_export/" + filename + ".tar -C " + copy->front() + " .").c_str());
                argTable->addArg("ADD", "./p2c_export/" + filename + ".tar");
                copy->pop();
            }
            else
            {
                argTable->addArg("ADD", copy->front());
                copy->pop();
            }
        }

        return 0;
    };
    virtual std::vector<std::string> getCommand()
    {
        std::vector<std::string> cmd{"-cmp", "--compatibility"};
        return cmd;
    };
    virtual std::string getHelp()
    {
        return "\
\n\
p2c mod compatibility\n\
Usage:\n\
    p2c -cmp\n\
    p2c --compatibility\n\
\n";
    };
};

extern "C" p2c_mod *p2c_create_mod() { return new p2c_mod_compatibility; }
