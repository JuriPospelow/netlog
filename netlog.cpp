#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "Device.hpp"
#include "Net.hpp"

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

    int cnt{};

    vector<Net> nets{};

    // Net nr1("n1");
    // Net nr2("n2");

    try
    {
        read_ini(fileName, config);

        for (int j{}; j < config.get<int>("nets.number"); ++j) {
            string net_name{"net"};
            net_name += to_string(j+1);

            Net tmp_net("tmp_net");

            cnt = config.get<int>(net_name+".number");
            string name_prefix {net_name+".pc"};

            for(int i{0}; i < cnt; ++i) {
                name_prefix += to_string(i+1);
                tmp_net.devices.push_back({config.get<std::string>(name_prefix+"_name"), config.get<std::string>(name_prefix+"_addr")});

                name_prefix = net_name +".pc";
            }

            nets.push_back(tmp_net);
            net_name = "net";
            tmp_net.devices.clear();
        }

        // net_name = "net";
        // net_name += to_string(2);

        // cnt = config.get<int>(net_name+".number");
        // name_prefix = net_name+".pc";

        // for(int i{0}; i < cnt; ++i) {
            // name_prefix += to_string(i+1);
            // nr2.devices.push_back({config.get<std::string>(name_prefix+"_name"), config.get<std::string>(name_prefix+"_addr")});

            // name_prefix = net_name +".pc";
        // }

        // nets.push_back(nr2);


    }
    catch (boost::property_tree::ini_parser_error& error)
    {
        std::cout
            << error.message() << ": "
            << error.filename() << ", line "
            << error.line() << std::endl;
    }
#if 1
    for(int j{0}; j < 2; ++j) {
        for(int i{0}; i < cnt; ++i) {
            cout << nets[j].devices[i].name() << ": " << nets[j].devices[i].ip() << endl;
        }
    }
#endif
return 0;
}
