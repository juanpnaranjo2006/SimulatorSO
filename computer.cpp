#include "computer.h"
#include <fstream>
#include <stdexcept>
#include <exception>
#include <iostream>

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

int COMPUTER::convertAddr(const std::string &addr) {
    return std::stoi(addr.substr(1)); //Quita la D al inicio de cada posicion en formato string
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
            throw std::length_error("El programa en " + path + " no cabe en el espacio de memoria reservado para programas (MemSize: " + std::to_string(maxAddr) + ")");
        }
    }

    if (!file.eof()) {
        throw std::runtime_error("Error al leer el archivo: " + path);
    }
}

void COMPUTER::readMemoryData() {
    if (processor.getMAR() >= memory.getMemSize()) {
        throw std::out_of_range("Rango por fuera de la memoria. Posicion de Lectura: " + std::to_string(processor.getMAR()) + ", MemSize: " + std::to_string(memory.getMemSize()));
    }
    else if (processor.getMAR() >= memory.getTextIndex()) {
        throw std::out_of_range("Se intentan leer datos del Text. Posicion de Lectura: " + std::to_string(processor.getMAR()) + ", TextIndex: " + std::to_string(memory.getTextIndex()));
    }

    processor.setMDR(std::stoi(memory.read(processor.getMAR())));
}

void COMPUTER::readMemoryText() {
    if (processor.getMAR() >= memory.getMemSize()) {
        throw std::out_of_range("Rango por fuera de la memoria. Posicion de Lectura: " + std::to_string(processor.getMAR()) + ", MemSize: " + std::to_string(memory.getMemSize()));
    }
    else if (processor.getMAR() < memory.getTextIndex()) {
        throw std::out_of_range("Se intentan leer instrucciones por fuera del Text. Posicion de Lectura: " + std::to_string(processor.getMAR()) + ", TextIndex: " + std::to_string(memory.getTextIndex()));
    }

    processor.setICR(memory.read(processor.getMAR()));
}

void COMPUTER::writeMemoryData() {
    if (processor.getMAR() >= memory.getMemSize()) {
        throw std::out_of_range("Rango por fuera de la memoria. Posicion de Lectura: " + std::to_string(processor.getMAR()) + ", MemSize: " + std::to_string(memory.getMemSize()));
    }
    else if (processor.getMAR() >= memory.getTextIndex()) {
        throw std::out_of_range("Se intentan modificar datos del Text. Posicion de Modificacion: " + std::to_string(processor.getMAR()) + ", TextIndex: " + std::to_string(memory.getTextIndex()));
    }

    memory.write(processor.getMAR(), std::to_string(processor.getAccumulator()));
}

void COMPUTER::execute() {
    const int oC = processor.getOpCode();

    if (oC == 1) {
        /*
        SET - MEM - SET D1 X NULL NULL, Store X value in D1 memory address.
        where X is an immediate, direct or constant value. When SET
        instruction is read the X value is stored in Memory without
        processor execution.
        */
        processor.setMAR(convertAddr(processor.getArguments()[0]));
        processor.setAccumulator(std::stoi(processor.getArguments()[1]));
        writeMemoryData();
    }
    if (oC == 2) {
        /*
        LDR - LOAD - LDR D3 NULL NULL Load the value in D3 memory address
        and puts in accumulator register
        */
        processor.setMAR(convertAddr(processor.getArguments()[0]));
        readMemoryData();
        processor.setAccumulator(processor.getMDR());
    }
    if (oC == 3) {
        /*
        ADD - ADDITION - There are three ways: ADD D1 NULL NULL, adds the
        value in D1 memory address to loaded value in accumulator
        register. ADD D1 D3 NULL Load the value in D1 memory address in the
        accumulator register and add to found value in D3 memory address.
        ADD D1 D3 D4 same that ADD D1 D3 but puts the result in D4
        */

        if (processor.getArguments()[1] == "NULL") {
            processor.setMAR(convertAddr(processor.getArguments()[0]));
            readMemoryData();
            processor.setRegisterA(processor.getMDR());
            processor.aluOP();
        }
        else if (processor.getArguments()[2] == "NULL") {
            processor.setMAR(convertAddr(processor.getArguments()[0]));
            readMemoryData();
            processor.setAccumulator(processor.getMDR());

            processor.setMAR(convertAddr(processor.getArguments()[1]));
            readMemoryData();
            processor.setRegisterA(processor.getMDR());

            processor.aluOP();
        }
        else {
            processor.setMAR(convertAddr(processor.getArguments()[0]));
            readMemoryData();
            processor.setAccumulator(processor.getMDR());

            processor.setMAR(convertAddr(processor.getArguments()[1]));
            readMemoryData();
            processor.setRegisterA(processor.getMDR());

            processor.aluOP();
            processor.setMAR(convertAddr(processor.getArguments()[2]));
            writeMemoryData();
        }
    }
    if (oC == 4) {
        /*
        INC - INCREMENT - INC D3 NULL NULL Load the value in D3 memory
        address adds 1 and store in same address
        */
        processor.setMAR(convertAddr(processor.getArguments()[0]));
        readMemoryData();
        processor.setAccumulator(processor.getMDR());
        processor.aluOP();
    }
    if (oC == 5) {
        /*
        DEC - DECREMENT - DEC D3 NULL NULL Load the value in D3 memory
        address adds 1 and store in same address
        */
        processor.setMAR(convertAddr(processor.getArguments()[0]));
        readMemoryData();
        processor.setAccumulator(processor.getMDR());
        processor.aluOP();
    }
    if (oC == 6) {
        /*
        STR - STORE - STR D3 NULL NULL Read the value in accumulator
        register and puts in D3 memory address
        */
        processor.setMAR(convertAddr(processor.getArguments()[0]));
        writeMemoryData();
    }
    if (oC == 7) {
        /*
        SHW - SHOW - SHW D2 NULL NULL
        SHW D2 NULL NULL: Displays the value at memory address D2.
        SHW ACC: Displays the value in the accumulator register.
        SHW ICR: Displays the value in the Instruction Counter Register.
        SHW MAR: Displays the value in the Memory Address Register.
        SHW MDR: Displays the value in the Memory Data Register.
        SHW UC: Displays the state of the Control Unit.
        */
        if (processor.getArguments()[0] == "ACC") {
            std::cout << processor.getAccumulator() << std::endl;
        }
        else if (processor.getArguments()[0] == "ICR") {
            std::cout << processor.getICR() << std::endl;
        }
        else if (processor.getArguments()[0] == "MAR") {
            std::cout << processor.getMAR() << std::endl;
        }
        else if (processor.getArguments()[0] == "MDR") {
            std::cout << processor.getMDR() << std::endl;
        }
        else if (processor.getArguments()[0] == "UC") {
            std::cout << "opCode: " << processor.getOpCode() << std::endl;
        }
        else {
            //Memory addrress
            int addr = std::stoi(processor.getArguments()[0]);
            std::cout << "Address: " << addr  << "\n Value: "<< memory.read(addr) << std::endl;
        }
    }
}

void COMPUTER::basicInstructionCycle() {
    //Fetch
    processor.setMAR(processor.getProgramCounter());
    readMemoryText(); //Pone la instruccion en el ICR
    processor.setProgramCounter(processor.getProgramCounter() + 1); //Program Counter + 1

    //Decode
    processor.setArguments(); //Decode + Argumentos para poder ejecutar

    //Execute
    execute();

    //Next
}

CPU& COMPUTER::getProcessor() {
    return processor;
}

MEMORY& COMPUTER::getMemory() {
    return memory;
}