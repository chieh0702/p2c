#include "gendf.h"
using namespace std;
int main(int argc, char const *argv[])
{
    if (argc <= 1)
        showHelp();
    string dockerfile;
    vector<string> tokens;
    for (int i = 1; i < argc; i++)
        tokens.push_back(argv[i]);
    Generator generator = Generator(tokens);
    while (!generator.is_EOF())
        dockerfile += generator.getline();
    ofstream fout;
    if (!generator.getOutput().empty())
        fout.open(generator.getOutput());
    else
        fout.open("Dockerfile");
    fout << dockerfile;// TODO:commend order
    fout.close();
    return 0;
}
