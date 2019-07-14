#ifndef CHARACTER_H
#define CHARACTER_H
#include "Constants.h"

/*
Class represents a character in a string
*/

class Character
{
private:
	char _char;
	int frequency;
	// character representation by bits sequence
	std::string bits;
public:
	Character() : _char('\0'), frequency(0), bits() {}
	Character(char newChar);
	Character(char newChar, int frequency);
	Character(char newChar, std::string bitsRepr);
	void increase();
	std::string getBits();
	int getFreq();
	char getChar();
	void operator=(Character& character)
	{
		_char = character.getChar();
		frequency = character.getFreq();
		bits = character.getBits();
	}

};

#endif
