#include <iostream>
#include <chrono>

#include "src/Nets.hpp"

int main(int argc, char** argv)
{
    std::string fileName {"dummy.ini"};
    if (argc >= 2 && argc < 3) {
        fileName = argv[1];
    } else {

    }
    auto start = std::chrono::high_resolution_clock::now();
    Nets nets(fileName);
    nets.readStatus();
    nets.printCSV();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " ms\n";

#if 0
    print(nets);
    nets.printIni();
#endif
return 0;
}
