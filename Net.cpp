#include "Net.hpp"
#include "Device.hpp"

using namespace std;

#if 0
#include "exec.hpp"
void Net::readStatus(string_view ip)
{
    string command {"nmap -sPn --version-light --osscan-limit "};
    command += ip;
    net_map = exec(command.c_str());
    for (size_t i{}; i<devices.size(); ++i) {
        devices[i].readStatus(net_map);
        // devices[i].printAddr();
        // cout << " " << devices[i].name() << " ";
        // cout << devices[i].ip() << " ";
        // cout << devices[i].status() << endl;
    }
}
#endif
