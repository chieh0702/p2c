#define _ALERT_LEVEL_ 0

#include <p2c_lib.h>

using namespace std;

int main(int argc, char const *argv[])
{
    p2c_liblist libList;
    cout << libList.mod_count("-h") << '\n';
    cout << libList.gen_count("-h") << '\n';
    cout << libList.getHelp();
    return 0;
}
