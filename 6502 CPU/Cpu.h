#ifndef CPU_H_
#define CPU_H_

#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "Static.h"

using namespace std;

class Cpu {
private:
	struct Instruction {
		void (Cpu::*address_mode)() = nullptr;
		void (Cpu::*instruction)() = nullptr;
	};

	void IMP();
	void IMM();
	void ABS();
	void ABX();
	void ABY();
	void ZP();
	void ZPX();
	void ZPY();
	void ZPInIX();
	void ZPIInY();
	void REL();
	void ABI();
	void ABIX();
	void ABIY();
	void ACC();

	void ERR();
	void LDA();
	void LDX();
	void LDY();
	void STA();
	void STX();
	void STY();

	void INC();
	void INX();
	void INY();

	void DEC();
	void DEX();
	void DEY();

	void TAX();
	void TXA();
	void TAY();
	void TYA();
	void TSX();
	void TXS();

	void CMP();
	void CPX();
	void CPY();

	void BCC();
	void BCS();
	void BNE();
	void BEQ();
	void BPL();
	void BMI();
	void BVC();
	void BVS();

	void AND();
	void ORA();
	void EOR();

	void ASL();
	void LSR();
	void ROL();
	void ROR();

	void CLC();
	void SEC();
	void CLD();
	void SED();
	void CLI();
	void SEI();
	void CLV();

	void JMP();
	void JSR();
	void RTS();

	void ADC();
	void SBC();

	void BIT();

	void PHA();
	void PLA();
	void PHP();
	void PLP();

	void NOP();

	void RTI();

	void BRK();

	void add(int index, void (Cpu::*address_mode)(),
			void (Cpu::*instruction)());

public:
	unsigned char A, X, Y, SP, SR;
	unsigned short PC;
	unsigned char memory[65536];
	unsigned short startAt = 0x600;
//	unsigned short startAt = 0xC000;
//	unsigned short startAt = 0x4000;
	vector<Instruction> instructions;

	enum Flags {
		C = (1 << 0),
		Z = (1 << 1),
		I = (1 << 2),
		D = (1 << 3),
		B = (1 << 4),
		U = (1 << 5),
		V = (1 << 6),
		N = (1 << 7),
	};

	int log[6][8991];

	void setFlag(Flags f,bool b);
	bool getFlag(Flags f);

	Cpu();
	void loadAsm(std::string);
	void loadBin(std::string);
	void loadNes(std::string);
	void loadLog(std::string);
	void emulateCycle();
	int hexStringToInt(std::string);
	void reset();

	int count = 0;
};

#endif /* CPU_H_ */
