#ifndef COMPRESSION_H
#define COMPRESSION_H
#include "HuffmanTreeDecoder.h"

namespace compression {

	// data to file
	void compress(const string& data, const string& path);
	void decompress(const string& data, const string& path);
	// file to file
	void compressFile(const string& sourceFile, const string& targetFile);
	void decompressFile(const string& sourceFile, const string& targetFile);
	// returns decompressed data from ile
	string& decompress(const string& path);
	string& encode(const string& text);
	string& decode(const string& encodedText);
}

#endif