/*
 * Instructions.h
 *
 *  Created on: Nov 25, 2021
 *      Author: omkar
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

unsigned short address = 0;
char relative = 0;

void Cpu::IMP() {

}

void Cpu::IMM() {
	address = ++PC;
}

void Cpu::ABS() {
	unsigned char lo = memory[++PC];
	unsigned char hi = memory[++PC];
	address = (hi << 8) | lo;
}

void Cpu::ZP() {
	address = memory[++PC];
	address &= 0xFF;
}

void Cpu::REL() {
	char rel = memory[++PC];
	relative = rel;
}

void Cpu::ABI() {
	unsigned char tmp_lo = memory[++PC];
	unsigned char tmp_hi = memory[++PC];
	unsigned short temp_address = (tmp_hi << 8) | tmp_lo;
	unsigned char lo = memory[temp_address];
	unsigned char hi = memory[(temp_address + 1) & 0xFFFF];
	address = (hi << 8) | lo;
}

void Cpu::ABX() {
	int INST = memory[PC];
	unsigned char lo = memory[++PC];
	unsigned char hi = memory[++PC];
	address = (hi << 8) | lo;
	address += X;
}

void Cpu::ABY() {
	unsigned char lo = memory[++PC];
	unsigned char hi = memory[++PC];
	address = (hi << 8) | lo;
	address += Y;
}

void Cpu::ZPX() {
	unsigned char add = memory[++PC] + X;
	address = add;
}

void Cpu::ZPY() {
	unsigned char add = memory[++PC] + Y;
	address = add;
}

void Cpu::ZPInIX() {
	unsigned char add = memory[++PC] + X;
	unsigned char lo = memory[add];
	unsigned char n = (add + 1);
	unsigned char hi = memory[n];
	address = (hi << 8) | lo;
}

void Cpu::ZPIInY() {
	unsigned char val = memory[++PC];
	unsigned char lo = memory[val];
	unsigned char hi = memory[(val + 1) & 0xFF];
	unsigned short address_temp = (hi << 8) | lo;
	address = address_temp + Y;
}

bool isA = false;
void Cpu::ACC() {
	isA = true;
}

void Cpu::LDA() {
	A = memory[address];
	setFlag(Z, A == 0);
	setFlag(N, (A & 0x80) == 0x80);
	PC++;
}

void Cpu::LDX() {
	X = memory[address];
	setFlag(Z, X == 0);
	setFlag(N, (X & 0x80) == 0x80);
	PC++;
}

void Cpu::LDY() {
	Y = memory[address];
	setFlag(Z, Y == 0);
	setFlag(N, (Y & 0x80) == 0x80);
	PC++;
}

void Cpu::STA() {
	memory[address] = A;
	PC++;
}

void Cpu::STX() {
	memory[address] = X;
	PC++;
}

void Cpu::STY() {
	memory[address] = Y;
	PC++;
}

void Cpu::INC() {
	++memory[address];
	setFlag(Z, memory[address] == 0);
	setFlag(N, (memory[address] & 0x80) == 0x80);
	PC++;
}

void Cpu::DEC() {
	--memory[address];
	setFlag(Z, memory[address] == 0);
	setFlag(N, (memory[address] & 0x80) == 0x80);
	PC++;
}

void Cpu::DEX() {
	--X;
	setFlag(Z, X == 0);
	setFlag(N, (X & 0x80) == 0x80);
	PC++;
}

void Cpu::DEY() {
	--Y;
	setFlag(Z, Y == 0);
	setFlag(N, (Y & 0x80) == 0x80);
	PC++;
}

void Cpu::INX() {
	X += 1;
	setFlag(Z, X == 0);
	setFlag(N, (X & 0x80) == 0x80);
	PC++;
}

void Cpu::INY() {
	Y += 1;
	setFlag(Z, Y == 0);
	setFlag(N, (Y & 0x80) == 0x80);
	PC++;
}

void Cpu::TAX() {
	X = A;
	setFlag(Z, X == 0);
	setFlag(N, (X & 0x80) == 0x80);
	PC++;
}

void Cpu::TXA() {
	A = X;
	setFlag(Z, A == 0);
	setFlag(N, (A & 0x80) == 0x80);
	PC++;
}

void Cpu::TAY() {
	Y = A;
	setFlag(Z, Y == 0);
	setFlag(N, (Y & 0x80) == 0x80);
	PC++;
}

void Cpu::TYA() {
	A = Y;
	setFlag(Z, A == 0);
	setFlag(N, (A & 0x80) == 0x80);
	PC++;
}

void Cpu::TSX() {
	X = SP;
	setFlag(Z, X == 0);
	setFlag(N, (X & 0x80) == 0x80);
	PC++;
}

void Cpu::TXS() {
	SP = X;
	setFlag(Z, SP == 0);
	setFlag(N, (SP & 0x80) == 0x80);
	PC++;
}

void Cpu::JMP() {
	PC = address;
}

void Cpu::JSR() {
	unsigned char hi = (PC >> 8);
	unsigned char lo = PC & 0xFF;
	memory[0x100 + SP] = hi;
	SP--;
	memory[0x100 + SP] = lo;
	SP--;
	PC = address;
}

void Cpu::RTS() {
	SP++;
	unsigned char lo = memory[0x100 + SP];
	SP++;
	unsigned char hi = memory[0x100 + SP];
	PC = ((hi << 8) & 0xFFFF) | (lo & 0xFF);
	PC++;
}

void Cpu::CMP() {
	unsigned char value = memory[address];

	if (A < value) {
		setFlag(N, true);
		setFlag(Z, false);
		setFlag(C, false);
	} else if (A == value) {
		setFlag(N, false);
		setFlag(Z, true);
		setFlag(C, true);
	} else if (A > value) {
		setFlag(N, false);
		setFlag(Z, false);
		setFlag(C, true);
	}
	PC++;
}

void Cpu::CPX() {
	unsigned char value = memory[address];
	if (X < value) {
		setFlag(N, true);
		setFlag(Z, false);
		setFlag(C, false);
	} else if (X == value) {
		setFlag(N, false);
		setFlag(Z, true);
		setFlag(C, true);
	} else if (X > value) {
		setFlag(N, false);
		setFlag(Z, false);
		setFlag(C, true);
	}
	PC++;
}

void Cpu::CPY() {
	unsigned char value = memory[address];

	if (Y < value) {
		setFlag(N, true);
		setFlag(Z, false);
		setFlag(C, false);
	} else if (Y == value) {
		setFlag(N, false);
		setFlag(Z, true);
		setFlag(C, true);
	} else if (Y > value) {
		setFlag(N, false);
		setFlag(Z, false);
		setFlag(C, true);
	}
	PC++;
}

void Cpu::BCC() {
	if (getFlag(C) == 0) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::BCS() {
	if (getFlag(C) == 1) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::BNE() {
	if (getFlag(Z) == 0) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::BEQ() {
	if (getFlag(Z) == 1) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::BPL() {
	if (getFlag(N) == 0) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::BMI() {
	if (getFlag(N) == 1) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::BVC() {
	if (getFlag(V) == 0) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::BVS() {
	if (getFlag(V) == 1) {
		address = PC + relative;
		PC = address;
	}
	PC++;
}

void Cpu::AND() {
	A &= memory[address];
	setFlag(Z, A == 0);
	setFlag(N, (A & 0x80) == 0x80);
	PC++;
}

void Cpu::ORA() {
	A |= memory[address];
	setFlag(Z, A == 0);
	setFlag(N, (A & 0x80) == 0x80);
	PC++;
}

void Cpu::EOR() {
	A ^= memory[address];
	setFlag(Z, A == 0);
	setFlag(N, (A & 0x80) == 0x80);
	PC++;
}

void Cpu::CLC() {
	setFlag(C, false);
	PC++;
}

void Cpu::SEC() {
	setFlag(C, true);
	PC++;
}

void Cpu::CLD() {
	setFlag(D, false);
	PC++;
}

void Cpu::SED() {
	setFlag(D, true);
	PC++;
}

void Cpu::CLI() {
	setFlag(I, false);
	PC++;
}

void Cpu::SEI() {
	setFlag(I, true);
	PC++;
}

void Cpu::CLV() {
	setFlag(V, false);
	PC++;
}

void Cpu::ASL() {
	unsigned int val;
	unsigned char VAL = memory[address];
	if (isA) {
		VAL = A;
	}
	val = VAL;
	val <<= 1;
	setFlag(C, ((VAL >> 7) & 0x1) == 1);
	setFlag(Z, (val & 0xFF) == 0);
	setFlag(N, (val & 0x80) == 0x80);
	if (isA) {
		A = val & 0xFF;
	} else {
		memory[address] = val & 0xFF;
	}
	isA = false;
	PC++;
}

void Cpu::LSR() {
	unsigned int val;
	unsigned char VAL = memory[address];
	if (isA) {
		VAL = A;
	}
	val = VAL;
	val >>= 1;
	setFlag(C, (VAL & 0x1) == 1);
	setFlag(Z, (val & 0xFF) == 0);
	setFlag(N, (val & 0x80) == 0x80);
	if (isA) {
		A = val & 0xFF;
	} else {
		memory[address] = val & 0xFF;
	}
	isA = false;
	PC++;
}

void Cpu::ROL() {
	unsigned int val = memory[address];
	if (isA) {
		val = A;
	}

	bool car = (val >> 7) & 0x1;
	val <<= 1;
	val |= getFlag(C);

	setFlag(C, car);
	setFlag(Z, (val & 0xFF) == 0);
	setFlag(N, (val & 0x80) == 0x80);

	if (isA) {
		A = val & 0xFF;
	} else {
		memory[address] = val & 0xFF;
	}
	isA = false;
	PC++;
}

void Cpu::ROR() {
	unsigned int val = memory[address];
	if (isA) {
		val = A;
	}

	bool car = val & 0x1;
	val = (getFlag(C) << 7) | (val >> 1);
	setFlag(C, car);
	setFlag(Z, (val & 0xFF) == 0);
	setFlag(N, (val & 0x80) == 0x80);

	if (isA) {
		A = val & 0xFF;
	} else {
		memory[address] = val & 0xFF;
	}
	isA = false;
	PC++;
}

void Cpu::ADC() {
	unsigned short val = A + memory[address] + getFlag(C);
	setFlag(C, val > 0xFF);
	setFlag(Z, (val & 0xFF) == 0);
	setFlag(N, (val & 0x80) == 0x80);
	setFlag(V, (((A ^ val) & (~(A ^ memory[address]))) & 0x80) == 0x80);
	A = val & 0xFF;
	PC++;
}

void Cpu::SBC() {
	unsigned short value = memory[address] ^ 0xFF;
	unsigned short val = A + value + getFlag(C);
	setFlag(C, val > 0xFF);
	setFlag(Z, (val & 0xFF) == 0);
	setFlag(N, (val & 0x80) == 0x80);
	setFlag(V, (((A ^ val) & (~(A ^ memory[address]))) & 0x80) == 0x80);
	A = val & 0xFF;
	PC++;
}

void Cpu::NOP() {
	PC++;
}

void Cpu::BIT() {
	unsigned char value = A & memory[address];
	setFlag(N, ((value >> 7) & 0x1) == 1);
	setFlag(V, ((value >> 6) & 0x1) == 1);
	setFlag(Z, value == 0);
	PC++;
}

void Cpu::PHA() {
	memory[0x100 + SP] = A;
	SP--;
	PC++;
}

void Cpu::PLA() {
	SP++;
	A = memory[0x100 + SP];
	setFlag(Z, A == 0);
	setFlag(N, (A & 0x80) == 0x80);
	PC++;
}

void Cpu::PHP() {
	memory[0x100 + SP] = SR | B | U;
	setFlag(U, true);
	SP--;
	PC++;
}

void Cpu::PLP() {
	SP++;
	unsigned char STATUS = memory[0x100 + SP];
	SR = STATUS;
	setFlag(U, true);
	setFlag(B, false);
	PC++;
}

void Cpu::RTI() {
	SP++;
	unsigned char STATUS = memory[0x100 + SP];
	SR = STATUS;

	SR &= ~B;
	SR &= ~U;

	SP++;
	unsigned char lo = memory[0x100 + SP];
	SP++;
	unsigned char hi = memory[0x100 + SP];
	PC = (hi << 8) | lo;
}

void Cpu::BRK(){
	setFlag(U, true);
	setFlag(B, true);
	setFlag(I, true);
}

bool Cpu::getFlag(Flags f) {
	unsigned char bit = log2((double) f);
	bool ST = (((SR >> bit) & 0x1) == 1);
	return ST;
}

void Cpu::setFlag(Flags f, bool b) {
	if (b) {
		SR |= f;
	} else {
		SR &= ~f;
	}
}

void Cpu::ERR() {
	if (memory[PC] != 0) {
//		print("Error Opcode Not found: " << std::hex << (int) memory[PC]);
	}
}

#endif /* INSTRUCTIONS_H_ */
