#include <iostream>
#include <vector>
#include <string>
#include <map>


std::vector <std::string> memoria(1024);
std::map <std::string, int> decodificador;

int decodificar(std::string &strAddr) {
    return decodificador[strAddr];
}

void decode(std::string &instruction) {
    int opCode = -1;
    std::string instructType = instruction.substr(0, instruction.find(" "));

    if (instructType == "SET") {
        opCode = 0;
    }
    else if (instructType == "LDR") {
        opCode = 1;
    }
    else if (instructType == "ADD") {
        opCode = 2;
    }
    else if (instructType == "INC") {
        opCode = 3;
    }
    else if (instructType == "DEC") {
        opCode = 4;
    }
    else if (instructType == "STR") {
        opCode = 5;
    }
    else if (instructType == "SHW") {
        opCode = 6;
    }
    else if (instructType == "PAUSE") {
        opCode = 7;
    }
    else if (instructType == "END") {
        opCode = 8;
    }
    
    return opCode;
}



int main() {

    for (int i = 0; i < 1024; i++) {
        decodificador[("D" + std::to_string(i))] = i;
    }


    return 0;
}
