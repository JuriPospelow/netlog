#include <iostream>

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
    try
    {
        read_ini(fileName, config);
        cout << config.get<std::string>("net1.pc1_name") << ": " << config.get<std::string>("net1.pc1_addr") <<endl;
    }
    catch (boost::property_tree::ini_parser_error& error)
    {
        std::cout
            << error.message() << ": "
            << error.filename() << ", line "
            << error.line() << std::endl;
    }

return 0;
}
