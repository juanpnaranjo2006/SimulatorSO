//
// Created by juanp on 26/02/2026.
//

#ifndef SIMULATORSO_CPU_H
#define SIMULATORSO_CPU_H
#include <string>


class CPU {
private:
    int mar;
    int mdr;
    std::string icr;
    int programCounter;

public:
    CPU() = default;
    int decode();


    // ===== Getters =====
    int getMAR() const;
    int getMDR() const;
    std::string getICR() const;
    int getProgramCounter() const;

    // ===== Setters =====
    void setMAR(int value);
    void setMDR(int value);
    void setICR(const std::string& value);
    void setProgramCounter(int value);
};


#endif //SIMULATORSO_CPU_H