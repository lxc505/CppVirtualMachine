#include <iostream>
#include <cstdint>

class virtualmachine {
public:
    enum InstructionSet : uint32_t {
        NOP = 0x00, END = 0x01, MOV = 0x02, LDR = 0x03, 
        STR = 0x04,
    };
private:
    class Vram {
    public:
        uint8_t ReadData(uint32_t Add) {
            return Data[Add];
        }
        void WriteData(uint32_t Add, uint8_t WriteData) {
            Data[Add] = WriteData;
        }
        uint32_t Read32Data(uint32_t Add) {
            return ( (uint32_t) Data[Add    ] << 24) |
                   ( (uint32_t) Data[Add + 1] << 16) |
                   ( (uint32_t) Data[Add + 2] << 8 ) |
                   ( (uint32_t) Data[Add + 3]      )        
            ;
        }
    private:
        uint8_t Data[65536] = {};
    };
 
    class Vcpu {
    public:
        Vcpu() : ram() {}
        void Real(uint32_t StartAdd) {
            uint8_t c1 = 0, c2 = 0, c3 = 0;
            uint32_t Instruction = 0;
            for (PC_Reg = StartAdd; ram.ReadData(PC_Reg) == END; PC_Reg += 4) {
                Instruction = ram.ReadData(PC_Reg);
                c1 = ram.ReadData(PC_Reg + 1);
                c2 = ram.ReadData(PC_Reg + 2);
                c3 = ram.ReadData(PC_Reg + 3);
                switch (Instruction) {
                    case NOP: break;
                    case END: return; break;
                    case MOV: break; 
                }
            }
        }
    private:
        Vram ram;
        uint32_t Reg[16] = {};
        enum Register : uint32_t {
            R0 = 0x00, R1 = 0x01, R2 = 0x02, R3 = 0x03,
            R4 = 0x04, R5 = 0x05, R6 = 0x06, R7 = 0x07,
            R8 = 0x08, R9 = 0x09, R10= 0x0A, R11= 0x0B,
            R12= 0x0C, PC = 0x0D, SP = 0x0E,
        };
        uint32_t &SP_Reg = Reg[SP];
        uint32_t &PC_Reg = Reg[PC];
    };
};

int main() {
    return 0;
}
