//
// Created by juanp on 26/02/2026.
//

#ifndef SIMULATORSO_MEMORY_H
#define SIMULATORSO_MEMORY_H
#include <string>
#include <vector>

class MEMORY {
private:
    int memSize;
    int textIndex;
    std::vector<std::string> ramMemory;

    // === Métodos Privados ===
    void setEmptyOpcodes();

public:
    MEMORY();
    MEMORY(int size);
    MEMORY(int size, int tIndex);
    ~MEMORY() = default;

    // === Métodos Públicos Principales ===
    void write(int addr, const std::string &value);
    std::string& read(int addr);

    // === Getters ===
    int getMemSize() const;
    int getTextIndex() const;
};


#endif //SIMULATORSO_MEMORY_H