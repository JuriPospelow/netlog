#include <algorithm>
#include <iostream>

#include "Device.hpp"

using namespace std;

// вариант сканирования сети с использванием  утилиты nmap
// время сканирования всей сети с использованием nmap занимает столько же
// сколько и одного pc с помощью ping
void Device::readStatus(string_view map)
{
    size_t res = map.find(_ip,100);
    // cout << this->_ip << " " << res << " ";
    _status = (res != string::npos) ? "on" : "off";
    // cout << this->_status << endl;
}
