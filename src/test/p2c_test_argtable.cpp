#include <iostream>
#include <p2c_lib.h>

using namespace std;

int main(int argc, char const *argv[])
{
    p2c_argtable args;
    args.initArgs(argc, argv);
    for (string s : args.getArg("command"))
        cout << s << '\n';
    args.addArg("say_hello", "hello tim");
    args.addArg("say_hello", "hello guest");
    vector<string> vector = {"1", "2", "3"};
    args.addArg("vector tese", vector);
    cout << args.getJSON() << '\n';
    return 0;
}
