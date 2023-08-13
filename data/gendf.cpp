#include "gendf.h"
using namespace std;
int main(int argc, char const *argv[])
{
    ifstream fin;
    ofstream fout;
    if ((argc <= 1) || (argv[1] == "-h") || (argv[1] == "--help"))
    {
        fin.open("help_info");
        if (fin.is_open())
            cout << fin.rdbuf();
        fin.close();
        return 1;
    }
    string dockerfile;
    vector<string> tokens;
    for (int i = 1; i <= argc; i++)
        tokens.push_back(argv[i]);
    Generator generator = Generator(tokens);
    while (!generator.is_EOF())
        dockerfile += generator.getline();
    if(!generator.getOutput().empty())
    {
        fout.open(generator.getOutput());
        fout<<dockerfile;
    }
    return 0;
}
