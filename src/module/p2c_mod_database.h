#include <p2c_lib.h>

#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

void mysql_dump(const std::string &user, const std::string &password, const std::string &database)
{
    if (database == "")
        system(("mysqldump -u " + user + " --password=\"" + password + "\" --all-databases" + " > " + database + ".sql").c_str());
    else
        system(("mysqldump -u " + user + " --password=\"" + password + "\" -d" + database + " > " + database + ".sql").c_str());
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
