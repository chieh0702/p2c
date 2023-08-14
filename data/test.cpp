#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
std::vector<std::string> split(std::string, std::string);
int main(int argc, char const *argv[])
{
    vector<string> v = split("edr 123:::f: 1:2:", ":");
    cout << argc << '\n'
         << v.size();
    for (string s : v)
        cout << s << '\n';
    if (argc <= 1)
    {
        cout << "No args\n";
        return 0;
    }
    // ofstream fout("output.txt");
    for (int i = 0; i < argc; i++)
    {
        // fout << argv[i] << '\n';
        cout << argv[i] << '\n';
    }
    // fout.close();
    return 0;
}
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