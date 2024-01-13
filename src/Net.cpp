#include "Net.hpp"
#include "Device.hpp"

using namespace std;


// #include "exec.hpp"
void Net::readStatus()
{
    string command {"nmap -sPn --version-light --osscan-limit "};
    command += _net_adr;
    // net_map = exec(command.c_str());
    for (size_t i{}; i<devices.size(); ++i) {
        devices[i].readStatus(_net_map);
#if 0
        devices[i].printAddr();
        cout << " " << devices[i].name() << " ";
        cout << devices[i].ip() << " ";
        cout << devices[i].status() << endl;
#endif
    }
}

