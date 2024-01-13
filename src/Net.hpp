#pragma once

#include <string>
#include <vector>

#include "Device.hpp"

class Net {
public:
    Net(std::string_view n)
    : name {n} {}
    void readStatus();

    void set_cnt_devs(int cnt_dev) { _cnt_devs = cnt_dev; }
    int get_cnt_devs() const { return _cnt_devs; }
    void set_net_adr(std::string net_adr) { _net_adr = net_adr; }
    std::string get_net_adr() const { return _net_adr; }

    std::string name{};
    std::vector <Device> devices{};
    std::string net_map{};

    int _cnt_devs{};
    std::string _net_adr{};
};
