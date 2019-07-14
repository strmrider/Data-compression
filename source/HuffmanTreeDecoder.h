#pragma once
#ifndef HUFFMANTREEDECODER_H
#define HUFFMANTREEDECODER_H
#include "HuffmanTree.h"
#include "BitStreamerDecoder.h"

class HuffmanTreeDecoder : HuffmanTree
{
private:
	Node* buildTree(const string& chars, int* charIndex, BitStreamerDecoder& stream);
public:
	HuffmanTreeDecoder(const string& encodedTree);
	string& decode(const string& encodedData);
	void print();
};

#endif // !HUFFMANTREEDECODER_H
