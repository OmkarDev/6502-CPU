#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Static.h"
#include "Cpu.h"

using namespace sf;

bool play = true;
Font font;
bool only_display;

template<typename T>
std::string hex(T i) {
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex
			<< (int) i;
	return stream.str();
}

void show_data(Cpu cpu, RenderWindow &window) {
	sf::Text Registers;
	Registers.setFont(font);
	std::string A = hex(cpu.A);
	std::string X = hex(cpu.X);
	std::string Y = hex(cpu.Y);
	std::string PC = hex(cpu.PC);
	std::string SP = hex(cpu.SP);
	std::string INST = hex(cpu.memory[cpu.PC]);
	std::string SR = hex(cpu.SR);
	Registers.setString(
			"A: 0x" + A + "    PC:0x" + PC + "\n" + "X: 0x" + X + "    SP:0x"
					+ SP + "\n" + "Y: 0x" + Y + "    INST: 0x" + INST + "\n"
					+ SR);
	Registers.setCharacterSize(20);
	Registers.setFillColor(Color::Black);
	Registers.setPosition(10, 5);
	window.draw(Registers);

	sf::Text Memory;
	Memory.setFont(font);
	std::string mem = "";
	int start = 0;
	int row = 8;
	int col = 16;
	for (int j = 0; j < row; j++) {
		for (int i = 0; i < col; i++) {
			std::string byte = hex(cpu.memory[start + (i + j * col)]);
			mem += byte + " ";
		}
		mem += "\n";
	}

	mem += "\n";
	mem += "\n";
	mem += "\n";

	start = cpu.startAt;

	for (int j = 0; j < row; j++) {
		for (int i = 0; i < col; i++) {
			std::string byte = hex(cpu.memory[start + (i + j * col)]);
			mem += byte + " ";
		}
		mem += "\n";
	}

	Memory.setString(mem);
	Memory.setCharacterSize(20);
	Memory.setFillColor(Color::Black);
	Memory.setPosition(10, 100);
	window.draw(Memory);
}

unsigned int colors[] = { 0x000000FF, 0xFFFFFFFF, 0x880000FF, 0xAAFFEEFF,
		0xCC44CCFF, 0x00CC55FF, 0x0000AAFF, 0xEEEE77FF, 0xDD8855FF, 0x664400FF,
		0xFF7777FF, 0x4C3B3BFF, 0x777777FF, 0xAAFF66FF, 0x0088FFFF, 0xBBBBBBFF };

RectangleShape rects[32 * 32];

unsigned int FPS = 0;
unsigned max_FPS = 40;

void show_display(Cpu cpu, RenderWindow &window) {
	if (only_display == false) {
		RectangleShape border;
		border.setOutlineColor(Color(0xE21717FF));
		border.setOutlineThickness(5);
		border.setPosition(rects[0].getPosition().x, pixel_size);
		border.setSize(Vector2f(32 * pixel_size, 32 * pixel_size));
		window.draw(border);
	}
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 32; i++) {
			unsigned char val = cpu.memory[0x200 + (i + j * 32)];
			unsigned int col = colors[val & 0xF];
			Color color(col);
			rects[i + j * 32].setFillColor(color);
			window.draw(rects[i + j * 32]);
		}
	}
}

void init(RenderWindow &window, RectangleShape (&rects)[32 * 32]) {
	if (only_display) {
		window.create(VideoMode(32 * pixel_size, 32 * pixel_size), "6502",
				sf::Style::Close);
		max_FPS = 60;
	} else {
		window.create(sf::VideoMode(WIDTH, HEIGHT), "6502 Emulator",
				sf::Style::Close);
	}
	auto desktop = VideoMode::getDesktopMode();
	window.setPosition(
			Vector2i((desktop.width - window.getSize().x) / 2,
					(desktop.height - window.getSize().y) / 2));

	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 32; i++) {
			int posX = WIDTH - (32 * pixel_size) - pixel_size;
			int posY = pixel_size;
			RectangleShape rect;
			if (only_display == true) {
				posX = 0;
				posY = 0;
			}
			rect.setPosition(posX + (i * pixel_size), posY + (j * pixel_size));
			rect.setSize(Vector2f(pixel_size, pixel_size));
			rects[i + j * 32] = rect;
		}
	}
	if (only_display == false) {
		font.loadFromFile("monospace.ttf");
	}
}

int main() {
	RenderWindow window;

	only_display = true;
	init(window, rects);

	Cpu cpu;
	cpu.loadAsm("res/demoscene2.asm");
//	cpu.loadBin("res/AllSuiteA.bin");

	srand(time(0));
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (Keyboard::isKeyPressed(sf::Keyboard::R)) {
				cpu.reset();
			}
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed
					&& Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				cpu.emulateCycle();
			}
			if (event.type == Event::KeyPressed
					&& Keyboard::isKeyPressed(sf::Keyboard::W)) {
				cpu.memory[0xFF] = 0x77;
			}
			if (event.type == Event::KeyPressed
					&& Keyboard::isKeyPressed(sf::Keyboard::S)) {
				cpu.memory[0xFF] = 0x73;
			}
			if (event.type == Event::KeyPressed
					&& Keyboard::isKeyPressed(sf::Keyboard::A)) {
				cpu.memory[0xFF] = 0x61;
			}
			if (event.type == Event::KeyPressed
					&& Keyboard::isKeyPressed(sf::Keyboard::D)) {
				cpu.memory[0xFF] = 0x64;
			}
		}
		if (play) {
			cpu.emulateCycle();
		}
		FPS++;
		if (FPS >= max_FPS) {
			window.clear(Color::White);
			if (only_display == false) {
				show_data(cpu, window);
			}
			show_display(cpu, window);
			window.display();
			FPS = 0;
		}
	}

	return 0;
}
