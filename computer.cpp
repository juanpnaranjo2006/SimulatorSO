#include "computer.h"

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

CPU& COMPUTER::getProcessor() {
    return processor;
}

MEMORY& COMPUTER::getMemory() {
    return memory;
}