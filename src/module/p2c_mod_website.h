#include <p2c_lib.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <dlfcn.h>
#include <dirent.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

std::set<std::string> findPath(std::string path, std::string str, int offset)
{
    std::set<std::string> result;
    if (path[path.size() - 1] != '/')
        path += '/';
    DIR *dirp = opendir(path.c_str());
    if (!dirp)
        p2c_alerter::alerting(ERROR, "Open", path, "failed: ", strerror(errno));
    while (1)
    {
        dirent *entry = readdir(dirp);
        if (!entry)
            break;
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
        {
            std::set<std::string> temp = findPath(path + entry->d_name + '/', str, offset);
            result.insert(temp.begin(), temp.end());
        }
        if (entry->d_type == DT_REG)
        {
            std::ifstream file(path + entry->d_name);
            if (file.fail())
            {
                closedir(dirp);
                p2c_alerter::alerting(ERROR, "Open", path + entry->d_name, "failed: ", strerror(errno));
            }
            std::string token;
            while (file >> token)
            {
                if (token[0] == '#')
                {
                    std::getline(file, token);
                    continue;
                }
                if (token == str)
                {
                    for (int i = 0; i < offset; i++)
                        file >> token;
                    if (token[0] == '"')
                        token = token.substr(1);
                    if (token[token.size() - 1] == '"')
                        token = token.substr(0, token.size() - 1);
                    struct stat buffer;
                    stat(token.c_str(), &buffer);
                    if (S_ISDIR(buffer.st_mode) && token[token.size() - 1] != '/')
                        token += '/';
                    result.insert(token);
                    p2c_alerter::alerting(DEBUG, "mod_website find", str, ":", token, "in", path + entry->d_name);
                }
            }
            file.close();
        }
    }
    closedir(dirp);
    return result;
}

void parser_Apache()
{
    const char apache_path[] = "/etc/apache2/";
    p2c_alerter::alerting(DEBUG, "start parser apache.", "apache path:", apache_path);
    argTable->addArg("RUN", "cd /etc/apache2/mods-enabled/;for file in *;do rm $file; ln -s /etc/apache2/mods-available/$file $file; done");
    argTable->addArg("RUN", "cd /etc/apache2/sites-enabled/;for file in *;do rm $file; ln -s /etc/apache2/sites-available/$file $file; done");
    system("apt-get update;apt-get install -o DPkg::Options::=\"--force-confold\" -y apache2");
    // system("apt-get update;apt-get install -y dpkg-repack;dpkg-repack $(apt-cache depends apache2 |awk '{print $2}') apache2 >dpkg-repack.log");
    // std::ifstream file("dpkg-repack.log");
    // std::string token;
    // while (file >> token)
    // {
    //     if (token == "in")
    //     {
    //         file >> token;
    //         std::string temp = token.substr(1, token.size() - 3);
    //         argTable->addArg("COPY", temp, "/");
    //         argTable->addArg("RUN", "apt-get install -o DPkg::Options::=\"--force-confold\" /" + temp.substr(temp.find_last_of('/') + 1) + " -y");
    //     }
    // }
    // file.close();
    // remove("./dpkg-repack.log");
    argTable->addArg("COPY", apache_path, apache_path);
    std::set<std::string> pathSet = findPath(apache_path, "DocumentRoot", 1);
    std::set<std::string> temp = findPath(apache_path, "LoadModule", 2);
    pathSet.insert(temp.begin(), temp.end());
    temp = findPath(apache_path, "LoadFile", 1);
    pathSet.insert(temp.begin(), temp.end());
    // temp = findPath(apache_path, "Include", 1);
    // pathSet.insert(temp.begin(), temp.end());
    // temp = findPath(apache_path, "IncludeOptional", 1);
    // pathSet.insert(temp.begin(), temp.end());
    temp = findPath(apache_path, "Alias", 2);
    pathSet.insert(temp.begin(), temp.end());
    temp = findPath(apache_path, "ScriptAlias", 2);
    pathSet.insert(temp.begin(), temp.end());
    temp = findPath(apache_path, "PassengerRuby", 1);
    pathSet.insert(temp.begin(), temp.end());
    temp = findPath(apache_path, "SSLCertificateFile", 1);
    pathSet.insert(temp.begin(), temp.end());
    temp = findPath(apache_path, "SSLCertificateKeyFile", 1);
    pathSet.insert(temp.begin(), temp.end());
    // TODO: remove include path, use tree structure
    for (std::string fullpath : pathSet)
    {
        std::string path = fullpath;
        std::size_t pos = fullpath.find_last_of('/');
        if (pos != std::string::npos)
            path = fullpath.substr(0, pos + 1);
        argTable->addArg("COPY", fullpath);
        argTable->addArg("COPY", path);
    }
}
