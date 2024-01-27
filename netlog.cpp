#include <iostream>

#include "src/Nets.hpp"

using namespace std;

#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "boost/filesystem.hpp"
using namespace boost::filesystem;
// #define Release
string head{"\nStatus des Testnetzes"};

void print(Nets& nets)
{
#ifdef Release
	bool file_exists = exists("/media/sf_GO_vbox/scan_net.csv");
	// cout << "file_status: " << std::boolalpha << file_status << endl;
	std::ofstream log ("/media/sf_GO_vbox/scan_net.csv", std::ofstream::app);
#else
	bool file_exists = exists("scan_net.csv");
	std::ofstream log ("scan_net.csv", std::ofstream::app);
#endif

	time_t t = time(NULL);
	tm tm = *localtime(&t);

	if(log.is_open()) {
		stringstream _monat {};
		 _monat << put_time(&tm, "%B");

		stringstream _jahr {};
		_jahr << put_time(&tm, "%Y");

		cout << head << "\t\t\t" << _monat.str() << "\t\t\t"
			 << _jahr.str() << endl;
		if(!file_exists) log << head << ",,," << _monat.str() << ",,,"
			 << _jahr.str() << endl;
		cout << "Testraum 3.1" << "\t\t\t" << "Testraum 3.2" << endl;
		if(!file_exists) log << "Testraum 3.1" << ",,,,,,," << "Testraum 3.2" << endl;

		cout << "\nDatum       ";
		if(!file_exists) log << "\nDatum,";
		for (auto net : nets.nets) {
			for (auto dev : net.devices) {
				cout << " " << dev.name();
				if(!file_exists) log << "," << dev.name();
			}
		}
		cout << endl;
		if(!file_exists) log << endl;

		stringstream _tag {};
		_tag << put_time(&tm, "%a");

		stringstream _datum {};
		_datum << put_time(&tm, "%d.%m.%y");

		cout << _tag.str() << " " << _datum.str();
		log << _tag.str() << ", " << _datum.str();
		cout << setfill(' ');
		log << setfill(',');
		for (auto net : nets.nets) {
			for (auto dev : net.devices) {
				cout << setw(max(dev.name().size(), static_cast<size_t>(7) ))
				<< dev.status();
				log << ","
				<< dev.status();
			}
		}
		cout << endl << endl;
		if (_tag.str() == "Sun") log << endl;
		log << endl;
		log.close();
	}
	 else cout << "Unable to open file";
}

int main(int argc, char** argv)
{
    std::string fileName {"dummy.ini"};
    if (argc >= 2 && argc < 3) {
        fileName = argv[1];
    } else {

    }

    Nets nets(fileName);
    nets.readStatus();
    nets.printCSV();

#if 0
    print(nets);
    nets.printIni();
#endif
return 0;
}
