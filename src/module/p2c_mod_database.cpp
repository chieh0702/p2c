#include "p2c_mod_database.h"

class p2c_mod_database : public p2c_mod
{
private:
public:
    p2c_mod_database()
    {
        p2c_alerter::alerting(DEBUG, "mod database init");
    };
    ~p2c_mod_database(){};
    virtual int entry(std::string, std::string args) override
    {
        int state = 0;
        std::string user = "root", password, database;
        std::stringstream ss(args);
        std::string arg;
        while (ss >> arg)
        {
            if (arg.find("=") != std::string::npos)
            {
                std::string key, value;
                split(arg, "=", &key, &value);
                if (key == "user")
                    user = value;
                else if (key == "password")
                    password = value;
                else if (key == "database")
                    database = value;
                else
                    p2c_alerter::alerting(ERROR, "mod database: unknown argument" + arg);
            }
            else
                p2c_alerter::alerting(ERROR, "mod database: unknown argument" + arg);
        }
        std::vector<std::string> PATH = split_all(getenv("PATH"), ":");
        p2c_alerter::alerting(DEBUG, "mod_database:52: $PATH num:", PATH.size());
        struct stat buffer;
        bool mysql = false, mongodb = false, pg = false, sqlite = false, mariadb = false, redis = false;
        for (std::string path : PATH)
        {
            if (stat((path + "/mysqldump").c_str(), &buffer) == 0 && !mysql)
            {
                mysql_dump(user, password, database);
                mysql = true;
            }
            if (stat((path + "/mongodump").c_str(), &buffer) == 0 && !mongodb)
            {
                mongodb_dump(user, password, database);
                mongodb = true;
            }
            if (stat((path + "/pg_dump").c_str(), &buffer) == 0 && !pg)
            {
                pg_dump(user, password, database);
                pg = true;
            }
            if (stat((path + "/sqlite").c_str(), &buffer) == 0 && !sqlite)
            {
                sqlite3_dump(user, password, database);
                sqlite = true;
            }
            if (stat((path + "/redis-cli").c_str(), &buffer) == 0 && !redis)
            {
                redis_dump(user, password, database);
                redis = true;
            }
        }

        return 0;
    };
    virtual std::vector<std::string> getCommand() override
    {
        std::vector<std::string> cmd{"-db", "--database"};
        return cmd;
    };
};

extern "C" p2c_mod *p2c_create_mod()
{
    return new p2c_mod_database;
}