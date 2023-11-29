#ifndef _P2C_SPLIT_H_
#define _P2C_SPLIT_H_

#include <iostream>
#include <vector>

std::vector<std::string> split_all(std::string str, const std::string &pattern)
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

int split(const std::string &str, const std::string &pattern, std::string *p1, std::string *p2)
{
    if (str.find(pattern) != std::string::npos)
    {
        std::size_t pos = str.find(pattern);
        if (p1)
            *p1 = str.substr(0, pos);
        if (p2)
            *p2 = str.substr(pos + pattern.size());
        return 0;
    }
    return 1;
}

#endif