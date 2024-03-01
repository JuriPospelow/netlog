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

#include <boost/process/system.hpp>
#include <boost/process/io.hpp>
#include <boost/asio/io_service.hpp>

#include "Nets.hpp"

namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;

using namespace boost::log;
using namespace boost::filesystem;

using namespace std;

/* ToDo: formating for console sink
*/

Nets::Nets(string fileName)
{
    try
    {
        cout << "read " << "netlog.ini" << "\n";
        read_ini("netlog.ini", _app_config);
        int room_nm = _app_config.get<int>("log.room_number");
        for (int j{}; j < room_nm; ++j) {
            string room_name{"log.room"};
            room_name += to_string(j+1);
            _rooms.push_back(_app_config.get<string>(room_name+"_name"));
        }
        _cmd_param = _app_config.get<string>("cmd.param");


        cout << "read " << fileName << "\n";
        read_ini(fileName, _config);

        _cnt_nets = _config.get<int>("nets.number");

        for (int j{}; j < _cnt_nets; ++j) {
            string net_name{"net"};
            net_name += to_string(j+1);

            int cnt_dev = _config.get<int>(net_name+".number");
            string tmp_addr = _config.get<string>(net_name+".addr");
            // string tmp_name {net_name+".pc"};

            _nets.push_back(create_net(cnt_dev, net_name+".pc", tmp_addr));
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
        tmp_net.devices.push_back({_config.get<std::string>(name_prefix+"_name"), _config.get<std::string>(name_prefix+"_addr")});
        tmp_net.set_cnt_devs(cnt_dev);
        tmp_net.set_net_adr(tmp_addr);
    }
    return tmp_net;
}

void Nets::readStatus()
{
    namespace bp = boost::process;

    boost::asio::io_service ios[_cnt_nets];
    future<std::string> result [_cnt_nets];
    vector<bp::child> ch_array;

    for(int j{0}; j < _cnt_nets; ++j) {
        string command  = _cmd_param;//{"nmap -sPn --version-light --osscan-limit "};
        command = command + " " + _nets[j].get_net_adr();
        cout << command.c_str() << endl;

        ch_array.push_back(bp::child (command.c_str(), bp::std_out > result[j], ios[j]));
    }

    for(int j{0}; j < _cnt_nets; ++j) {
        ios[j].run();
    }

    for(int j{0}; j < _cnt_nets; ++j) {
        std::string tmp  = result[j].get();
        _nets[j].readStatus(tmp);
        // cout << _nets[j].get_net_adr() << endl;
    }
}

void Nets::printIni() const
{
    for(int j{0}; j < _cnt_nets; ++j) {
        for(int i{0}; i <  _nets[j].get_cnt_devs(); ++i) {
            cout << _nets[j].devices[i].name() << ": " << _nets[j].devices[i].ip() << endl;
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
    for (auto room : _rooms){
        header_adv += room;
        header_adv += ",,,";
    }
    BOOST_LOG(_lg) << header_adv;

    string tmp_head = "\nDatum,";
    for (auto net : _nets) {
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

    for (auto net : _nets) {
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
