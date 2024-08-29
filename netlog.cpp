#include <iostream>
#include <chrono>

#include "src/Nets.hpp"

int main(int argc, char** argv)
{
    std::string networkIni {"dummy.ini"};
    std::string appiIni {"netlog.ini"};

    if (argc >= 2 && argc < 4) {
        appiIni = argv[1];
        networkIni = argv[2];
    } else {
        std::cerr <<
            "Usage: netlog <appi ini file>  <network ini file> \n" <<
            "Example:\n" <<
            "    netlog netlog.ini dummy.ini\n";
        return EXIT_FAILURE;
    }
    auto start = std::chrono::high_resolution_clock::now();
    Nets nets(appiIni, networkIni);
    nets.readStatus();
    nets.printCSV();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " ms\n";

return 0;
}
