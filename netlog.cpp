#include <iostream>

#include "Device.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;

int main(int argc, char** argv)
{
    std::string fileName {"dummy.ini"};
    if (argc >= 2 && argc < 3) {
        fileName = argv[1];
    } else {

    }

    cout << "read " << fileName << "\n";

    boost::property_tree::ptree config;
    vector<Device> v_dev;
    int cnt{};

    try
    {
        read_ini(fileName, config);
        // cout << config.get<std::string>("net1.pc1_name") << ": " << config.get<std::string>("net1.pc1_addr") <<endl;
        Device dev1(config.get<std::string>("net1.pc1_name"), config.get<std::string>("net1.pc1_addr"));
        cout << dev1.name() << ": " << dev1.ip() << endl;
        Device dev2(config.get<std::string>("net1.pc2_name"), config.get<std::string>("net1.pc2_addr"));
        cout << dev2.name() << ": " << dev2.ip() << endl;

        // string name {"net1.pc1_"};
        // v_dev.push_back({config.get<std::string>(name+"name"), config.get<std::string>("net1.pc1_addr")});
        // v_dev.push_back(dev2);

        cnt = config.get<int>("net1.number");
        string name_prefix {"net1.pc"};

        for(int i{0}; i < cnt; ++i) {
            name_prefix += to_string(i+1);
            v_dev.push_back({config.get<std::string>(name_prefix+"_name"), config.get<std::string>(name_prefix+"_addr")});
            name_prefix = "net1.pc";
        }
    }
    catch (boost::property_tree::ini_parser_error& error)
    {
        std::cout
            << error.message() << ": "
            << error.filename() << ", line "
            << error.line() << std::endl;
    }

    for(int i{0}; i < cnt; ++i) {
        cout << v_dev[i].name() << ": " << v_dev[i].ip() << endl;
    }


return 0;
}
