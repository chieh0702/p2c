#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char const *argv[])
{
    cout << argc << '\n';
    if (argc <= 1)
    {
        cout << "No args\n";
        return 0;
    }
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << '\n';
    }
    return 0;
}