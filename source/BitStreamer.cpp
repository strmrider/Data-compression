#include "BitStreamer.h"

// gets string of 0 and 1 and converts to 8 bits decimal
char binToDec(string& bits)
{
	unsigned int num = 0;
	unsigned int n;
	int j = 7;
	for (int i = 0; i < bits.length(); i++)
	{
		n = bits[i];
		n -= 48;
		num += n * (pow(2, j));
		j--;
	}
	return num;
}

BitStreamer::BitStreamer()
{
	bits = new string();
}

BitStreamer::~BitStreamer()
{
	delete bits;
}

int BitStreamer::totalSize()
{
	return bits->length() + 8;
}

void BitStreamer::flush()
{
	stream = "";
	tmp = "";
	*bits = "";
}

void BitStreamer::extractStream(const string& newStr)
{
	int sub = 8 - stream.length();
	tmp += stream;
	for (int i = 0; i < sub; i++)
		tmp += newStr[i];
	stream = "";
	for (int i = sub; i < newStr.length(); i++)
		stream += newStr[i];
	(*bits) += binToDec(tmp);
	tmp = "";
}

void BitStreamer::operator <<(const string& str)
{
	if (str.length() + stream.length() >= 8)
		extractStream(str);
	else
		stream += str;
}

string* BitStreamer::getBits()
{
	return bits;
}

string BitStreamer::finish(bool addCompletion, bool addDiff)
{
	int len = stream.length();
	int i = 0;
	// complete to byte
	if (addCompletion)
	{
		if (len > 0 && len < 8)
		{
			for (i = 0; i < (8 - (len % 8)); i++)
				stream += "0";
			(*bits) += binToDec(stream);
		}
	}

	stream = "";
	if (addDiff)
		return (char)i + (*bits);
	else
		return (*bits);

}