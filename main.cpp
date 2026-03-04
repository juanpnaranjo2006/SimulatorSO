#include <iostream>
#include <ostream>

#include "computer.h"

int main(int argc, char* argv[]) {
    std::string filePath;
    if (argc >= 2) {
        filePath = argv[1];
    }
    else {
        std::cout << "Introduzca la ruta al archivo del programa (.txt):" << std::endl;
        std::cin >> filePath;
    }

    COMPUTER mainComputer;
    try {
        mainComputer.loadProgram(filePath);
        mainComputer.runProgram();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
