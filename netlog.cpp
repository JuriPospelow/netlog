#include <iostream>
#include "src/Nets.hpp"

int main(int argc, char** argv)
{
    std::string fileName {"dummy.ini"};
    if (argc >= 2 && argc < 3) {
        fileName = argv[1];
    } else {

    }

    Nets nets(fileName);
    nets.readStatus();
    nets.printCSV();

#if 0
    print(nets);
    nets.printIni();
#endif
return 0;
}
