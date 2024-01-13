#pragma once

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "Net.hpp"

class Nets {
public:
    explicit Nets(std::string fileName);
    void readStatus();
    void printIni() const;
    int cnt_nets() const { return _cnt_nets; }

private:
    int _cnt_nets{};
    boost::property_tree::ptree config;
    std::vector<Net> nets{};
    Net create_net(int cnt_dev, const std::string& tmp_name, const std::string& );
};
