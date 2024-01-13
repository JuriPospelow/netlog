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


#if 1
    for(int j{0}; j < nets.cnt_nets(); ++j) {
        for(int i{0}; i <  nets.nets[j].get_cnt_devs(); ++i) {
            cout << nets.nets[j].devices[i].name() << ": " << nets.nets[j].devices[i].ip() << endl;
        }
    }
#endif
return 0;
}
