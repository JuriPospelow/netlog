#include "Net.hpp"
#include "Device.hpp"

using namespace std;


#include "exec.hpp"
void Net::readStatus(std::string& n)
{
    string command  = n;//{"nmap -sPn --version-light --osscan-limit "};
    command = command + " " + _net_adr;
    cout << command.c_str() << endl;
    _net_map = exec(command.c_str());
    for (size_t i{}; i<devices.size(); ++i) {
        devices[i].readStatus(_net_map);
#if 1
        devices[i].printAddr();
        cout << " " << devices[i].name() << " ";
        cout << devices[i].ip() << " ";
        cout << devices[i].status() << endl;
#endif
    }
}

