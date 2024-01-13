#pragma once

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "Net.hpp"

class Nets {
public:
    explicit Nets(std::string fileName);
    void readStatus();
    int cnt_nets() const { return _cnt_nets; }
    std::vector<Net> nets{};
private:
    Net create_net(int cnt_dev, const std::string& tmp_name, const std::string& );
    int _cnt_nets{};
    boost::property_tree::ptree config;
};
