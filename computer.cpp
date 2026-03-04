#include "computer.h"
#include <fstream>
#include <stdexcept>
#include <exception>

COMPUTER::COMPUTER() {
    memory = MEMORY();
    processor = CPU();
}

COMPUTER::COMPUTER(int memSize) {
    memory = MEMORY(memSize);
    processor = CPU();
}

COMPUTER::COMPUTER(int memSize, int textIndex) {
    memory = MEMORY(memSize, textIndex);
    processor = CPU();
}

void COMPUTER::loadProgram(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + path);
    }

    std::string instruction;
    int addr = memory.getTextIndex();
    const int maxAddr = memory.getMemSize();
    while (file >> instruction) {
        if (addr < maxAddr) {
            memory.write(addr, instruction);
            addr += 1;
        }
        else {
            throw std::length_error("El programa en " + path + " no cabe en el espacio de memoria reservado para programas");
        }
    }

    if (!file.eof()) {
        throw std::runtime_error("Error al leer el archivo: " + path);
    }
}

CPU& COMPUTER::getProcessor() {
    return processor;
}

MEMORY& COMPUTER::getMemory() {
    return memory;
}