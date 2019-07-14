#include "BitStreamerDecoder.h"

BitStreamerDecoder::BitStreamerDecoder(int start, int end, const string& text)
{
	while(start < end)
	{
		chars.push(text[start]);
		start++;
	}
	reload();
}

void BitStreamerDecoder::loadByte(const char byte)
{
	chars.push(byte);
	if (currentBit >= 8)
		reload();
}

void BitStreamerDecoder::reload()
{
	currentChar = chars.front();
	currentBit = 0;
	chars.pop();
}

char BitStreamerDecoder::next()
{
	if (chars.empty() && currentBit >= 8)
		return '2';
	if (currentBit >= 8 && !chars.empty())
		reload();
	char bit = currentChar >> 7;
	currentChar = currentChar << 1;
	currentBit++;

	return bit;
}

bool BitStreamerDecoder::finished()
{
	if ( chars.empty() && currentBit >= 8)
		return true;
	else
		return false;
}