#include "../include/DataProcessor.h"
#include <iostream>
#include <stdexcept>


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <display_ip> <processor_port> <display_port>" << std::endl;
        return 1;
    }

    try {
        DataProcessor dp(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
        dp.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
