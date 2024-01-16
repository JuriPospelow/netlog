#include <iostream>

#include "src/Nets.hpp"

using namespace std;

int main(int argc, char** argv)
{
    std::string fileName {"dummy.ini"};
    if (argc >= 2 && argc < 3) {
        fileName = argv[1];
    } else {

    }

    cout << "read " << fileName << "\n";

    Nets nets(fileName);
    nets.readStatus();

#if 0
    nets.printIni();
#endif
return 0;
}
