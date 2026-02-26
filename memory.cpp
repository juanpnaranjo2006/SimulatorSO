//
// Created by juanp on 26/02/2026.
//

#include "memory.h"

/*
Crea el arreglo que representa la memoria con un tamaño por defecto de
{1024}
 */
MEMORY::MEMORY() {
    memSize = 1024;
    textIndex = 512;
    ramMemory = std::vector<std::string>(memSize, "");
    setEmptyOpcodes();
}

/*Crea el arreglo que representa la memoria con tamaño {size}*/
MEMORY::MEMORY(const int size) {
    memSize = size;
    textIndex = size / 2;
    ramMemory = std::vector<std::string>(memSize, "");
    setEmptyOpcodes();
}

/*Crea el arreglo que representa la memoria con tamaño {size}
e impone un índice para inicio del texto (programas) en {tIndex}.

Si {tIndex} >= {size}, se utiliza la posición de la mitad del arreglo
inicializado {size / 2} como índice para inicio del texto.
*/
MEMORY::MEMORY(const int size, const int tIndex) {
    memSize = size;
    textIndex = (tIndex < size) ? tIndex : (size / 2);
    ramMemory = std::vector<std::string>(memSize, "");
    setEmptyOpcodes();
}

void MEMORY::setEmptyOpcodes() {
    for (int i = 0; i < memSize; i++) {
        ramMemory[i] = (i < textIndex) ? "0" : "NOP";
    }
}

int MEMORY::getMemSize() const {
    return memSize;
}

int MEMORY::getTextIndex() const {
    return textIndex;
}

void MEMORY::write(const int addr, const std::string &value) {
    ramMemory[addr] = value;
}

std::string& MEMORY::read(const int addr) {
    return ramMemory[addr];
}