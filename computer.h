#ifndef SIMULATORSO_COMPUTER_H
#define SIMULATORSO_COMPUTER_H
#include "cpu.h"
#include "memory.h"


class COMPUTER {
private:
    CPU processor;
    MEMORY memory;
public:
    COMPUTER();
    COMPUTER(int memSize);
    COMPUTER(int memSize, int textIndex);
    ~COMPUTER() = default;

    // == Métodos Principales ==
    void loadProgram(const std::string &path);

    // == Getters ==
    CPU& getProcessor();
    MEMORY& getMemory();
};


#endif //SIMULATORSO_COMPUTER_H