//
// Created by juanp on 26/02/2026.
//

#include "cpu.h"
#include <sstream>

void CPU::decode(const std::string &instructName) {
    opCode = 0; //NOP instruction

    if (instructName == "SET") {
        opCode = 1;
    }
    else if (instructName == "LDR") {
        opCode = 2;
    }
    else if (instructName == "ADD") {
        opCode = 3;
    }
    else if (instructName == "INC") {
        opCode = 4;
    }
    else if (instructName == "DEC") {
        opCode = 5;
    }
    else if (instructName == "STR") {
        opCode = 6;
    }
    else if (instructName == "SHW") {
        opCode = 7;
    }
    else if (instructName == "PAUSE") {
        opCode = 8;
    }
    else if (instructName == "END") {
        opCode = 9;
    }
}

void CPU::setArguments() {
    //Manipula el ICR con substrings para poder tener los argumentos de la instrucción separados
    std::istringstream iss(icr);
    std::string instructName;
    iss >> instructName;
    decode(instructName);

    for (int i = 0; i < 3; ++i) {
        arguments[i] = "";
        iss >> arguments[i];
    }
}

// ===== Getters =====
int CPU::getMAR() const {
    return mar;
}

int CPU::getMDR() const {
    return mdr;
}

std::string CPU::getICR() const {
    return icr;
}

int CPU::getProgramCounter() const {
    return programCounter;
}

std::vector<std::string> CPU::getArguments() const {
    return arguments;
}

int CPU::getOpCode() const {
    return opCode;
}

// ===== Setters =====
void CPU::setMAR(int value) {
    mar = value;
}

void CPU::setMDR(int value) {
    mdr = value;
}

void CPU::setICR(const std::string& value) {
    icr = value;
}

void CPU::setProgramCounter(int value) {
    programCounter = value;
}

void CPU::setArguments(const std::vector<std::string>& args) {
    arguments = args;
}

void CPU::setOpCode(int value) {
    opCode = value;
}