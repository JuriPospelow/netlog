#pragma once

#include <string>
#include <vector>

#include "Device.hpp"

class Net {
public:
    Net(std::string_view n)
    : name {n} {}
    void readStatus(std::string_view);
    void set_cnt_devs(int cnt_dev) { cnt_devs = cnt_dev; }
    int get_cnt_devs() { return cnt_devs; }

    std::string name{};
    std::vector <Device> devices{};
    std::string net_map{};

    int cnt_devs{};
};
