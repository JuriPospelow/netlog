#include "Net.hpp"
#include "Device.hpp"

using namespace std;

// #include "exec.hpp"
void Net::readStatus(std::string& n)
{
    for (size_t i{}; i<devices.size(); ++i) {
        devices[i].readStatus(n);
#if 0
        devices[i].printAddr();
        cout << " " << devices[i].name() << " ";
        cout << devices[i].ip() << " ";
        cout << devices[i].status() << endl;
#endif
    }
}

