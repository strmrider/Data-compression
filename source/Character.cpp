#include "Character.h"
Character::Character(char newChar)
{
	_char = newChar;
	frequency = 1;
}

Character::Character(char newChar, int frequency)
{
	_char = newChar;
	this->frequency = frequency;
	bits = "";
}

Character::Character(char newChar, std::string bitsRepr)
{
	_char = newChar;
	bits = bitsRepr;
}

void Character::increase()
{
	frequency++;
}

int Character::getFreq()
{
	return frequency;
}

char Character::getChar()
{
	return _char;
}

std::string Character::getBits()
{
	return bits;
}