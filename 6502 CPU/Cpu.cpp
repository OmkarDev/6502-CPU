#include "Cpu.h"
#include "Instructions.h"
#include <bits/stdc++.h>

Cpu::Cpu() {
	A = 0;
	Y = 0;
	X = 0;
	SP = 0xFD;
	SR = 0x24;
	PC = startAt;
	for (int i = 0; i < 65536; i++) {
		memory[i] = 0;
	}
	//load all instructions with their addressing mode and instructions mode in an list and then call them
	for (int i = 0; i < 256; i++) {
		Instruction inst;
		inst.address_mode = &Cpu::IMP;
		inst.instruction = &Cpu::ERR;
		instructions.push_back(inst);
	}
	add(0xAD, &Cpu::ABS, &Cpu::LDA);
	add(0xBD, &Cpu::ABX, &Cpu::LDA);
	add(0xB9, &Cpu::ABY, &Cpu::LDA);
	add(0xA9, &Cpu::IMM, &Cpu::LDA);
	add(0xA5, &Cpu::ZP, &Cpu::LDA);
	add(0xA1, &Cpu::ZPInIX, &Cpu::LDA);
	add(0xB5, &Cpu::ZPX, &Cpu::LDA);
	add(0xB1, &Cpu::ZPIInY, &Cpu::LDA);

	add(0xAE, &Cpu::ABS, &Cpu::LDX);
	add(0xBE, &Cpu::ABY, &Cpu::LDX);
	add(0xA2, &Cpu::IMM, &Cpu::LDX);
	add(0xA6, &Cpu::ZP, &Cpu::LDX);
	add(0xB6, &Cpu::ZPY, &Cpu::LDX);

	add(0xAC, &Cpu::ABS, &Cpu::LDY);
	add(0xBC, &Cpu::ABX, &Cpu::LDY);
	add(0xA0, &Cpu::IMM, &Cpu::LDY);
	add(0xA4, &Cpu::ZP, &Cpu::LDY);
	add(0xB4, &Cpu::ZPX, &Cpu::LDY);

	add(0x8D, &Cpu::ABS, &Cpu::STA);
	add(0x9D, &Cpu::ABX, &Cpu::STA);
	add(0x99, &Cpu::ABY, &Cpu::STA);
	add(0x85, &Cpu::ZP, &Cpu::STA);
	add(0x81, &Cpu::ZPInIX, &Cpu::STA);
	add(0x95, &Cpu::ZPX, &Cpu::STA);
	add(0x91, &Cpu::ZPIInY, &Cpu::STA);

	add(0x8E, &Cpu::ABS, &Cpu::STX);
	add(0x86, &Cpu::ZP, &Cpu::STX);
	add(0x96, &Cpu::ZPY, &Cpu::STX);

	add(0x8C, &Cpu::ABS, &Cpu::STY);
	add(0x84, &Cpu::ZP, &Cpu::STY);
	add(0x94, &Cpu::ZPX, &Cpu::STY);

	add(0xEE, &Cpu::ABS, &Cpu::INC);
	add(0xFE, &Cpu::ABX, &Cpu::INC);
	add(0xE6, &Cpu::ZP, &Cpu::INC);
	add(0xF6, &Cpu::ZPX, &Cpu::INC);

	add(0xCE, &Cpu::ABS, &Cpu::DEC);
	add(0xDE, &Cpu::ABX, &Cpu::DEC);
	add(0xC6, &Cpu::ZP, &Cpu::DEC);
	add(0xD6, &Cpu::ZPX, &Cpu::DEC);

	add(0xCA, &Cpu::IMP, &Cpu::DEX);

	add(0x88, &Cpu::IMP, &Cpu::DEY);

	add(0xE8, &Cpu::IMP, &Cpu::INX);
	add(0xC8, &Cpu::IMP, &Cpu::INY);

	add(0xCD, &Cpu::ABS, &Cpu::CMP);
	add(0xDD, &Cpu::ABX, &Cpu::CMP);
	add(0xD9, &Cpu::ABY, &Cpu::CMP);
	add(0xC9, &Cpu::IMM, &Cpu::CMP);
	add(0xC5, &Cpu::ZP, &Cpu::CMP);
	add(0xC1, &Cpu::ZPInIX, &Cpu::CMP);
	add(0xD5, &Cpu::ZPX, &Cpu::CMP);
	add(0xD1, &Cpu::ZPIInY, &Cpu::CMP);

	add(0xEC, &Cpu::ABS, &Cpu::CPX);
	add(0xE0, &Cpu::IMM, &Cpu::CPX);
	add(0xE4, &Cpu::ZP, &Cpu::CPX);

	add(0xCC, &Cpu::ABS, &Cpu::CPY);
	add(0xC0, &Cpu::IMM, &Cpu::CPY);
	add(0xC4, &Cpu::ZP, &Cpu::CPY);

	add(0x90, &Cpu::REL, &Cpu::BCC);
	add(0xB0, &Cpu::REL, &Cpu::BCS);
	add(0xD0, &Cpu::REL, &Cpu::BNE);
	add(0xF0, &Cpu::REL, &Cpu::BEQ);
	add(0x10, &Cpu::REL, &Cpu::BPL);
	add(0x30, &Cpu::REL, &Cpu::BMI);
	add(0x50, &Cpu::REL, &Cpu::BVC);
	add(0x70, &Cpu::REL, &Cpu::BVS);

	add(0xAA, &Cpu::IMP, &Cpu::TAX);
	add(0x8A, &Cpu::IMP, &Cpu::TXA);
	add(0xA8, &Cpu::IMP, &Cpu::TAY);
	add(0x98, &Cpu::IMP, &Cpu::TYA);
	add(0xBA, &Cpu::IMP, &Cpu::TSX);
	add(0x9A, &Cpu::IMP, &Cpu::TXS);

	add(0x4C, &Cpu::ABS, &Cpu::JMP);
	add(0x6C, &Cpu::ABI, &Cpu::JMP);

	add(0x20, &Cpu::ABS, &Cpu::JSR);
	add(0x60, &Cpu::IMP, &Cpu::RTS);

	add(0x2D, &Cpu::ABS, &Cpu::AND);
	add(0x3D, &Cpu::ABX, &Cpu::AND);
	add(0x39, &Cpu::ABY, &Cpu::AND);
	add(0x29, &Cpu::IMM, &Cpu::AND);
	add(0x25, &Cpu::ZP, &Cpu::AND);
	add(0x21, &Cpu::ZPInIX, &Cpu::AND);
	add(0x35, &Cpu::ZPX, &Cpu::AND);
	add(0x31, &Cpu::ZPIInY, &Cpu::AND);

	add(0x0D, &Cpu::ABS, &Cpu::ORA);
	add(0x1D, &Cpu::ABX, &Cpu::ORA);
	add(0x19, &Cpu::ABY, &Cpu::ORA);
	add(0x09, &Cpu::IMM, &Cpu::ORA);
	add(0x05, &Cpu::ZP, &Cpu::ORA);
	add(0x01, &Cpu::ZPInIX, &Cpu::ORA);
	add(0x15, &Cpu::ZPX, &Cpu::ORA);
	add(0x11, &Cpu::ZPIInY, &Cpu::ORA);

	add(0x4D, &Cpu::ABS, &Cpu::EOR);
	add(0x5D, &Cpu::ABX, &Cpu::EOR);
	add(0x59, &Cpu::ABY, &Cpu::EOR);
	add(0x49, &Cpu::IMM, &Cpu::EOR);
	add(0x45, &Cpu::ZP, &Cpu::EOR);
	add(0x41, &Cpu::ZPInIX, &Cpu::EOR);
	add(0x55, &Cpu::ZPX, &Cpu::EOR);
	add(0x51, &Cpu::ZPIInY, &Cpu::EOR);

	add(0x0E, &Cpu::ABS, &Cpu::ASL);
	add(0x1E, &Cpu::ABX, &Cpu::ASL);
	add(0x0A, &Cpu::ACC, &Cpu::ASL);
	add(0x06, &Cpu::ZP, &Cpu::ASL);
	add(0x16, &Cpu::ZPX, &Cpu::ASL);

	add(0x4E, &Cpu::ABS, &Cpu::LSR);
	add(0x5E, &Cpu::ABX, &Cpu::LSR);
	add(0x4A, &Cpu::ACC, &Cpu::LSR);
	add(0x46, &Cpu::ZP, &Cpu::LSR);
	add(0x56, &Cpu::ZPX, &Cpu::LSR);

	add(0x2E, &Cpu::ABS, &Cpu::ROL);
	add(0x3E, &Cpu::ABX, &Cpu::ROL);
	add(0x2A, &Cpu::ACC, &Cpu::ROL);
	add(0x26, &Cpu::ZP, &Cpu::ROL);
	add(0x36, &Cpu::ZPX, &Cpu::ROL);

	add(0x6E, &Cpu::ABS, &Cpu::ROR);
	add(0x7E, &Cpu::ABX, &Cpu::ROR);
	add(0x6A, &Cpu::ACC, &Cpu::ROR);
	add(0x66, &Cpu::ZP, &Cpu::ROR);
	add(0x76, &Cpu::ZPX, &Cpu::ROR);

	add(0x18, &Cpu::IMP, &Cpu::CLC);
	add(0x38, &Cpu::IMP, &Cpu::SEC);
	add(0xD8, &Cpu::IMP, &Cpu::CLD);
	add(0xF8, &Cpu::IMP, &Cpu::SED);
	add(0x58, &Cpu::IMP, &Cpu::CLI);
	add(0x78, &Cpu::IMP, &Cpu::SEI);
	add(0xB8, &Cpu::IMP, &Cpu::CLV);

	add(0x6D, &Cpu::ABS, &Cpu::ADC);
	add(0x7D, &Cpu::ABX, &Cpu::ADC);
	add(0x79, &Cpu::ABY, &Cpu::ADC);
	add(0x69, &Cpu::IMM, &Cpu::ADC);
	add(0x65, &Cpu::ZP, &Cpu::ADC);
	add(0x61, &Cpu::ZPInIX, &Cpu::ADC);
	add(0x75, &Cpu::ZPX, &Cpu::ADC);
	add(0x71, &Cpu::ZPIInY, &Cpu::ADC);

	add(0xED, &Cpu::ABS, &Cpu::SBC);
	add(0xFD, &Cpu::ABX, &Cpu::SBC);
	add(0xF9, &Cpu::ABY, &Cpu::SBC);
	add(0xE9, &Cpu::IMM, &Cpu::SBC);
	add(0xE5, &Cpu::ZP, &Cpu::SBC);
	add(0xE1, &Cpu::ZPInIX, &Cpu::SBC);
	add(0xF5, &Cpu::ZPX, &Cpu::SBC);
	add(0xF1, &Cpu::ZPIInY, &Cpu::SBC);

	add(0x2C, &Cpu::ABS, &Cpu::BIT);
	add(0x89, &Cpu::IMM, &Cpu::BIT);
	add(0x24, &Cpu::ZP, &Cpu::BIT);

	add(0x48, &Cpu::IMP, &Cpu::PHA);
	add(0x68, &Cpu::IMP, &Cpu::PLA);
	add(0x08, &Cpu::IMP, &Cpu::PHP);
	add(0x28, &Cpu::IMP, &Cpu::PLP);

	add(0xEA, &Cpu::IMP, &Cpu::NOP);

	add(0x00, &Cpu::IMP, &Cpu::BRK);

	add(0x40, &Cpu::IMP, &Cpu::RTI);

}

void Cpu::add(int index, void (Cpu::*address_mode)(),
		void (Cpu::*instruction)()) {
	instructions[index].address_mode = address_mode;
	instructions[index].instruction = instruction;
}

void Cpu::emulateCycle() {
	//read opcode from adress startAt
	unsigned int inst = memory[PC];
	//execute address_mode first
	(this->*instructions[inst].address_mode)();
	//execute instructions later
	(this->*instructions[inst].instruction)();

	memory[0xFE] = rand() & 0xFF;
}

void Cpu::reset(){
	A = 0;
	Y = 0;
	X = 0;
	SP = 0xFD;
	SR = 0x24;
	PC = startAt;

	for (int i = 0; i < 0x200+32*32; i++) {
		memory[i] = 0;
	}
}

//loads hex string data and remove line number
void Cpu::loadAsm(std::string path) {
	//read and write asm file to memory at address StartAt
	std::string line;
	vector<string> lines;
	std::ifstream myfile(path);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			lines.push_back(line);
		}
		for (int i = 0; i < lines.size(); i++) {
			string lin = lines[i];
			string code = lin.substr(6, lin.size());
			int code_length = ceil(code.size() / 3.0f);
			for (int x = 0; x < code_length; x++) {
				string block = "";
				block += code[x * 3];
				block += code[(x * 3) + 1];
				short c;
				stringstream ss;
				ss << std::hex << block;
				ss >> c;
				memory[startAt + x + (i * 16)] = c;
			}
		}
		myfile.close();
	}
}

//loads raw binary into memory
void Cpu::loadBin(std::string path) {
	std::ifstream input(path, std::ios::binary);
	std::vector<unsigned char> file(std::istreambuf_iterator<char>(input), { });

	for (int i = 0; i < file.size(); i++) {
		memory[i + startAt] = file[i];
	}
}

int Cpu::hexStringToInt(std::string hx) {
	stringstream ss;
	ss << std::hex << hx;
	int a = 0;
	ss >> a;
	return a;
}
