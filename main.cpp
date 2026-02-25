#include <iostream>
#include <vector>
#include <string>
#include <map>


std::vector <std::string> memoria(1024);
std::map <std::string, int> decodificador;

int decodificar(std::string &strAddr) {
    return decodificador[strAddr];
}

int decode(std::string &instruction) {
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

void execute(int opCode, std::string &instruction) {
    std::string firstArgument;
    std::string secondArgument;
    int address;
    int result;
    if (opCode == 0) {
        //SET
        firstArgument = instruction.substr(instruction.find(" ") + 1, instruction.length() - instruction.find(" "));
        secondArgument = firstArgument.substr(firstArgument.find(" ") + 1, firstArgument.length() - firstArgument.find(" "));
        firstArgument = firstArgument.substr(0, firstArgument.find(" "));
        secondArgument = secondArgument.substr(0, secondArgument.find(" "));
        address = decodificar(firstArgument);
        memoria[address] = secondArgument;
        //std::cout << memoria[address] << std::endl;
    }
    else if (opCode == 1) {

    }
    else if (opCode == 2) {

    }
    else if (opCode == 3) {

    }
    else if (opCode == 4) {

    }
    else if (opCode == 5) {

    }
    else if (opCode == 6) {

    }
    else if (opCode == 7) {

    }
    else if (opCode == 8) {

    }
    else {}
}



int main() {

    for (int i = 0; i < 1024; i++) {
        decodificador[("D" + std::to_string(i))] = i;
    }

    std::string instruction("SET D10 15 NULL NULL");
    execute(0, instruction);


    return 0;
}
