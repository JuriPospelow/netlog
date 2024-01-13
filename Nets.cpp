#include <iostream>

#include <boost/property_tree/ini_parser.hpp>

#include "Nets.hpp"

using namespace std;

Nets::Nets(string fileName)
{
    try
    {
        read_ini(fileName, config);

        _cnt_nets = config.get<int>("nets.number");

        for (int j{}; j < _cnt_nets; ++j) {
            string net_name{"net"};
            net_name += to_string(j+1);

            int cnt_dev = config.get<int>(net_name+".number");
            string tmp_addr = config.get<string>(net_name+".addr");
            // string tmp_name {net_name+".pc"};

            nets.push_back(create_net(cnt_dev, net_name+".pc", tmp_addr));
            net_name = "net";
        }
    }
    catch (boost::property_tree::ini_parser_error& error)
    {
        std::cout
            << error.message() << ": "
            << error.filename() << ", line "
            << error.line() << std::endl;
    }
}

Net Nets::create_net(int cnt_dev, const string& tmp_name, const string& tmp_addr)
{
    Net tmp_net("tmp_net");
    for(int i{0}; i < cnt_dev; ++i) {
        string name_prefix = tmp_name + to_string(i+1);
        tmp_net.devices.push_back({config.get<std::string>(name_prefix+"_name"), config.get<std::string>(name_prefix+"_addr")});
        tmp_net.set_cnt_devs(cnt_dev);
        tmp_net.set_net_adr(tmp_addr);
        name_prefix = tmp_name;
    }
    return tmp_net;
}

void Nets::readStatus()
{
    for(int j{0}; j < _cnt_nets; ++j) {
        nets[j].readStatus();
        // cout << nets[j].get_net_adr() << endl;
    }
}
