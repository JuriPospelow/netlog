#pragma once

#include <string>
#include <vector>
class Device;

class Net {
public:
    Net(std::string_view n)
    : name {n} {}
    void readStatus(std::string_view);

    std::string name{};
    std::vector <Device> devices{};
    std::string net_map{};
};
