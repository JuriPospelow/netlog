#pragma once

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/log/sources/logger.hpp>

#include "Net.hpp"

class Nets {
public:
    explicit Nets(std::string fileName);
    void readStatus();
    void printIni() const;
    int cnt_nets() const { return _cnt_nets; }
    void printCSV() const;
    std::vector<Net> nets{};

private:
    int _cnt_nets{};
    boost::property_tree::ptree config;
    mutable boost::log::sources::logger _lg;

    Net create_net(int cnt_dev, const std::string& tmp_name, const std::string& );
    void logHead(tm* tm_ptr) const;
    void boostLogHead(tm* tm_ptr) const;
    void logBody(tm *tm) const;
};
