//
// Created by juanp on 26/02/2026.
//

#ifndef SIMULATORSO_CPU_H
#define SIMULATORSO_CPU_H
#include <string>
#include <vector>


class CPU {
private:
    int mar;
    int mdr;
    std::string icr;
    int programCounter;
    int registerA;
    int accumulator;

    // ===== Variables Auxiliares =====
    std::vector <std::string> arguments{3};
    int opCode;

    // ===== Métodos privados =====
    void decode(const std::string &instructName);
    void setArguments();

public:
    CPU() = default;
    ~CPU() = default;

    // ===== Métodos principales =====
    void aluOP();


    // ===== Getters =====
    int getMAR() const;
    int getMDR() const;
    std::string getICR() const;
    int getProgramCounter() const;
    std::vector<std::string> getArguments() const;
    int getOpCode() const;
    int getAccumulator() const;
    int getRegisterA() const;

    // ===== Setters =====
    void setMAR(int value);
    void setMDR(int value);
    void setICR(const std::string& value);
    void setProgramCounter(int value);
    void setArguments(const std::vector<std::string>& args);
    void setOpCode(int value);
    void setAccumulator(int value);
    void setRegisterA(int value);
};


#endif //SIMULATORSO_CPU_H