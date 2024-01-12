#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "Device.hpp"
#include "Net.hpp"

using namespace std;

// ToDo: push_back, smart_ptr


class Nets {
public:
    explicit Nets(string fileName);
    int cnt_nets() const { return _cnt_nets; }
    vector<Net> nets{};
private:
    Net create_net(int cnt_dev, const string& tmp_name);
    int _cnt_nets{};
    boost::property_tree::ptree config;
};

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
            // string tmp_name {net_name+".pc"};

            nets.push_back(create_net(cnt_dev, net_name+".pc"));
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

Net Nets::create_net(int cnt_dev, const string& tmp_name)
{
    Net tmp_net("tmp_net");
    for(int i{0}; i < cnt_dev; ++i) {
        string name_prefix = tmp_name + to_string(i+1);
        tmp_net.devices.push_back({config.get<std::string>(name_prefix+"_name"), config.get<std::string>(name_prefix+"_addr")});
        tmp_net.set_cnt_devs(cnt_dev);
        name_prefix = tmp_name;
    }
    return tmp_net;
}

int main(int argc, char** argv)
{
    std::string fileName {"dummy.ini"};
    if (argc >= 2 && argc < 3) {
        fileName = argv[1];
    } else {

    }

    cout << "read " << fileName << "\n";

    Nets nets(fileName);

#if 1
    for(int j{0}; j < nets.cnt_nets(); ++j) {
        for(int i{0}; i <  nets.nets[j].get_cnt_devs(); ++i) {
            cout << nets.nets[j].devices[i].name() << ": " << nets.nets[j].devices[i].ip() << endl;
        }
    }
#endif
return 0;
}
