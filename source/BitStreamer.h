#ifndef BITSTREAMER_h
#define BITSTREAMER_h
#include "Constants.h"

/*
As RAM and other media storage address cannot represent a sequence of less than 8 bits,
any shorter sequence would have to be completed with additional redundant bits.
This would result in a false representation of the original code and the increment of data
(which misses all the purpose of compression).
The class gets a string that represents binary code, converts every 64 bytes to 1 byte by converting it to the equivalent ASCII code.
*/

class BitStreamer
{
public:
	string stream;
	string* bits;
	string tmp;
	void extractStream(const string& newStr);
public:
	BitStreamer();
	~BitStreamer();
	void operator <<(const string& str);
	int totalSize();
	string* getBits();
	string finish(bool addCompletion = false, bool addDiff = false);
	void flush();
};
#endif // !BITSTREAMER_h
