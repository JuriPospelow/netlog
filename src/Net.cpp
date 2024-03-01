#include "Net.hpp"
#include "Device.hpp"

using namespace std;

// #include "exec.hpp"
void Net::readStatus(std::string& n)
{
    for (Device& device : devices) {
        device.readStatus(n);
// debug output
    //     devices[i].printAddr();
    //     cout << " " << devices[i].name() << " ";
    //     cout << devices[i].ip() << " ";
    //     cout << devices[i].status() << endl;
    }
}
