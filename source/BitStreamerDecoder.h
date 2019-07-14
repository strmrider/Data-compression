#pragma once
#ifndef BITSTREAMERDECODER_H
#define BITSTREAMERDECODER_H
#include "Constants.h"

/*
The class gets a string of binary code, extracts each digit and converts it to 8 byte representation.
*/

class BitStreamerDecoder
{
public:
	queue<char> chars;
	int currentBit;
	char currentChar;
	void reload();
	bool init;
public:
	BitStreamerDecoder() : init(false) {};
	BitStreamerDecoder(int start, int end, const string& text);
	void loadByte(const char byte);
	char next();
	bool finished();

};

#endif // !BITSTREAMERDECODER_H
