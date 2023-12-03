#include <p2c_lib.h>

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    string dir_str = "/etc/nginx/conf.d/";
    string file_str = "/etc/nginx/nginx.conf";
    vector<string> dir_split = split_all(dir_str, "/");
    vector<string> file_split = split_all(file_str, "/");
    for (int i = 0; i < dir_split.size(); i++)
    {
        if (dir_split[i].empty())
            cout << "EMPTY";
        cout << dir_split[i] << '@';
    }
    cout << '\n';
    for (int i = 0; i < file_split.size(); i++)
    {
        if (dir_split[i].empty())
            cout << "EMPTY";
        cout << file_split[i] << '@';
    }
    cout << '\n';
    return 0;
}
