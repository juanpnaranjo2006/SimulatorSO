#include <iostream>
#include <vector>
#include <string>
#include <map>


std::vector <std::string> memoria(1024);
std::map <std::string, int> decodificador;
std::string acumulador = "0";
int mar;
std::string mdr;
std::string icr;
int programCounter;

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
    std::string thirdArgument;
    std::string fourthArgument;
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
        //LDR
        firstArgument = instruction.substr(instruction.find(" ") + 1, instruction.length() - instruction.find(" "));
        firstArgument = firstArgument.substr(0, firstArgument.find(" "));
        address = decodificar(firstArgument);
        acumulador = memoria[address];
        //std::cout << acumulador << std::endl;
    }
    else if (opCode == 2) {
        //ADD
        firstArgument = instruction.substr(instruction.find(" ") + 1, instruction.length() - instruction.find(" "));
        secondArgument = firstArgument.substr(firstArgument.find(" ") + 1, firstArgument.length() - firstArgument.find(" "));
        firstArgument = firstArgument.substr(0, firstArgument.find(" "));
        thirdArgument = secondArgument.substr(secondArgument.find(" ") + 1, secondArgument.length() - secondArgument.find(" "));
        secondArgument = secondArgument.substr(0, secondArgument.find(" "));
        thirdArgument = thirdArgument.substr(0, thirdArgument.find(" "));
        if (secondArgument == "NULL") {
            address = decodificar(firstArgument);
            acumulador = std::to_string(stoi(memoria[address]) + stoi(acumulador));
        }
        else if (thirdArgument == "NULL") {
            address = decodificar(firstArgument);
            acumulador = memoria[address];
            address = decodificar(secondArgument);
            acumulador = std::to_string(stoi(memoria[address]) + stoi(acumulador));
        }
        else {
            address = decodificar(firstArgument);
            acumulador = memoria[address];
            address = decodificar(secondArgument);
            acumulador = std::to_string(stoi(memoria[address]) + stoi(acumulador));
            address = decodificar(thirdArgument);
            memoria[address] = acumulador;
        }
    }
    else if (opCode == 3) {
        //INC
    }
    else if (opCode == 4) {
        //DEC
    }
    else if (opCode == 5) {
        //STR
    }
    else if (opCode == 6) {
        //SHW
    }
    else if (opCode == 7) {
        //PAUSE
    }
    else if (opCode == 8) {
        //END
    }
    else {}
}



int main() {

    for (int i = 0; i < 1024; i++) {
        decodificador[("D" + std::to_string(i))] = i;
    }

    std::string instruction("ADD D10 D11 NULL NULL");
    memoria[10] = std::string("Hola");
    execute(2, instruction);


    return 0;
}
