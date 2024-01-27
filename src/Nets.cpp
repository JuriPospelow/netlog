#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "boost/filesystem.hpp"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/expressions/formatters/csv_decorator.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/predicates/has_attr.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "Nets.hpp"

namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;

using namespace boost::log;
using namespace boost::filesystem;

using namespace std;

// ToDo: use boost::asio for readStatus

Nets::Nets(string fileName)
{
    try
    {
        cout << "read " << "netlog.ini" << "\n";
        read_ini("netlog.ini", app_config);
        int room_nm = app_config.get<int>("log.room_number");
        for (int j{}; j < room_nm; ++j) {
            string room_name{"log.room"};
            room_name += to_string(j+1);
            _rooms.push_back(app_config.get<string>(room_name+"_name"));
        }

        cout << "read " << fileName << "\n";
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

void Nets::printIni() const
{
    for(int j{0}; j < _cnt_nets; ++j) {
        for(int i{0}; i <  nets[j].get_cnt_devs(); ++i) {
            cout << nets[j].devices[i].name() << ": " << nets[j].devices[i].ip() << endl;
        }
    }
}
// ------------------------------------------------------------------------------------------------

void init()
{
    // Construct the sink for console
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
    boost::shared_ptr< text_sink > sink_console = boost::make_shared< text_sink >();
    boost::shared_ptr< std::ostream > stream(&std::clog, boost::null_deleter());
    sink_console->locked_backend()->add_stream(stream);

    // Construct the sink for file
    boost::shared_ptr< sinks::text_file_backend > backend =
        boost::make_shared< sinks::text_file_backend >(
            keywords::file_name = "netlog.csv",
            keywords::open_mode = std::ios_base::out | std::ios_base::app // appendig to file
        );
    backend->auto_flush(true);
    typedef sinks::synchronous_sink< sinks::text_file_backend > sink_t;
    boost::shared_ptr< sink_t > sink_file(new sink_t(backend));
    // we will not write to file the head, if that exists
    sink_file->set_filter(!expr::has_attr("Tag"));
    sink_file->set_formatter
    (
        expr::stream
        // << expr::attr< unsigned int >("LineID") << ","
        // << expr::csv_decor[ expr::stream << expr::attr< std::string >("Tag") ] << ","
        << expr::csv_decor[ expr::stream << expr::message ] << ","
    );

    // Register the sink in the logging core
    core::get()->add_sink(sink_file);
    core::get()->add_sink(sink_console);
}

void Nets::boostLogHead(tm* tm_ptr) const
{
    stringstream _monat {};
     _monat << put_time(tm_ptr, "%B");
    stringstream _jahr {};
    _jahr << put_time(tm_ptr, "%Y");

    std::string s = "\nStatus, des, Testnetzes,,,           ";
    s += _monat.str() + ",,,   ";
    s += _jahr.str();
    BOOST_LOG(_lg) << s;

    string header_adv = ",,";
    for (int i{}; i < _rooms.size(); ++i){
        header_adv += _rooms[i];
        header_adv += ",,,";
    }
    BOOST_LOG(_lg) << header_adv;//",,Testraum 3.1,,," << "\t\t\t" << "Testraum 3.2";

    string tmp_head = "\nDatum,    ";
    for (auto net : nets) {
        for (auto dev : net.devices) {
            tmp_head += ", " + dev.name();
        }
    }
    BOOST_LOG(_lg) << tmp_head;
}

void Nets::logHead(tm* tm_ptr) const
{
// if file exists write head only to console
    if(exists("netlog.csv")) {
        BOOST_LOG_SCOPED_LOGGER_TAG(_lg, "Tag", "Tagged line"); // work only in the scope {}
        boostLogHead(tm_ptr);
    } else {
        boostLogHead(tm_ptr);
    }
}

void Nets::logBody(tm *tm) const
{
    stringstream _tag {};
    _tag << put_time(tm, "%a");

    stringstream _datum {};
    _datum << put_time(tm, "%d.%m.%y");

    string tmp_body = _tag.str() + ", " + _datum.str();
    std::ostringstream tmp;

    for (auto net : nets) {
        for (auto dev : net.devices) {
            tmp << setw(max(dev.name().size(), static_cast<size_t>(7) ));
            tmp_body += tmp.str() + "," + dev.status();
        }
    }
    BOOST_LOG(_lg) << tmp_body;
}

void Nets::printCSV() const
{
    init();

    time_t t = time(NULL);
    tm* tm = localtime(&t);

    logHead(tm);
    logBody(tm);
}
