#include <iostream>
#include <nicamaps.h>

using namespace std;

int main()
{
    try {
        NicaMaps programm;
        programm.benutzerMenu();
    }  catch (...) {
        cerr << "Unexpected Error!" << endl;
    }

    return 0;
}
