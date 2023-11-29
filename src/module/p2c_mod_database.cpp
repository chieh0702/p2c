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
        std::string user, password, database;
        std::stringstream ss(args);
        std::string arg;
        while (ss >> arg)
        {
            switch (state)
            {
            case 0:
                if (arg == "-u" || arg == "--user")
                    state = 1;
                else if (arg == "-p" || arg == "--password")
                    state = 2;
                else if (arg == "-d" || arg == "--database")
                    state = 3;
                else
                    p2c_alerter::alerting(ERROR, "mod database: unknown argument" + arg);
                break;
            case 1:
                user = arg;
                state = 0;
                break;
            case 2:
                password = arg;
                state = 0;
                break;
            case 3:
                database = arg;
                state = 0;
                break;
            default:
                p2c_alerter::alerting(ERROR, "mod database: unknown state");
                break;
            }
        }
        if (stat("/etc/init.d/mysql", NULL))
            mysql_dump(user, password, database);
        if (stat("/etc/init.d/mongodb", NULL))
            mongodb_dump(user, password, database);
        if (stat("/etc/init.d/postgresql", NULL))
            pg_dump(user, password, database);
        if (stat("/etc/init.d/sqlite", NULL))
            sqlite3_dump(user, password, database);
        if (stat("/etc/init.d/mariadb", NULL))
            mariadb_dump(user, password, database);
        if (stat("/etc/init.d/redis", NULL))
            redis_dump(user, password, database);
    };
    virtual std::vector<std::string> getCommand() override
    {
        std::vector<std::string> cmd{"--database"};
        return cmd;
    };
};

extern "C" p2c_mod *p2c_create_mod()
{
    return new p2c_mod_database;
}