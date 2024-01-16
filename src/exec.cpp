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
#if 0
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
#endif
}
