#include <string>
#include <array>
#include <memory>
#include <stdexcept>

#include <boost/process/system.hpp>
#include <boost/process/io.hpp>
#include <boost/asio/io_service.hpp>

// namespace bp = boost::process;


std::string exec(const char* cmd)
{
    boost::asio::io_service ios;
    std::future<std::string> result;
    boost::process::system(cmd, boost::process::std_out > result, ios);

    std::string res = result.get();
    return res;
}
