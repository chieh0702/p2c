#include <p2c_lib.h>

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>

void mysql_dump(const std::string &user, const std::string &password, const std::string &database)
{
    p2c_alerter::alerting(DEBUG, "mod database: mysql dump");
    int status = 0;
    if (database == "")
        status = system(("mysqldump -u " + user + " --password=\"" + password + "\" --all-databases" + " > " + "export.sql").c_str());
    else
        status = system(("mysqldump -u " + user + " --password=\"" + password + "\" -d" + database + " > " + "export.sql").c_str());
    argTable->addArg("ADD", "./export.sql", "/export.sql");
    argTable->addArg("RUN", "apt-get update; apt-get install -y mariadb-server; service mariadb start; mysql < /export.sql; rm /export.sql");
}

void mongodb_dump(const std::string &user, const std::string &password, const std::string &database)
{
    // implementation goes here
}

void pg_dump(const std::string &user, const std::string &password, const std::string &database)
{
    // implementation goes here
}

void sqlite3_dump(const std::string &user, const std::string &password, const std::string &database)
{
    // implementation goes here
}

void mariadb_dump(const std::string &user, const std::string &password, const std::string &database)
{
    // implementation goes here
}

void redis_dump(const std::string &user, const std::string &password, const std::string &database)
{
    // implementation goes here
}
