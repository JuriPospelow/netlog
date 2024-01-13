#include <algorithm>
#include <iostream>

#include "Device.hpp"

using namespace std;

#if 0
#include "exec.hpp"

void Device::readStatusIPMI()
{
    const string on_ipmi = "Chassis Power is on\n";
    // string ping = "ipmitool -I lanplus -U ADMIN -P ADMIN  power status -H ";
    // ping += dev.ip;
    string ping = "ipmitool -I lanplus -H 10.81.3.14 -U ADMIN -P ADMIN  power status";
    string result = exec(ping.c_str());
    string pattern = on_ipmi;
    size_t res = result.find(pattern);
    _status = (res != string::npos) ? "on" : "off";
}

void Device::readStatusPing()
{
    string ping = "ping -c 1 -4 ";
    ping += _ip;
    string result = exec(ping.c_str());
    string pattern = "Fehler";
    size_t res = result.find(pattern,150);
    _status = (res == string::npos) ? "on" : "off";
}
#endif

void Device::readStatus(string_view map)
{
    size_t res = map.find(_ip,100);
    // cout << this->_ip << " " << res << " ";
    _status = (res != string::npos) ? "on" : "off";
    // cout << this->_status << endl;
}
