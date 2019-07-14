#pragma once
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "Heap.h"
#include "BitStreamer.h"

class HuffmanTree
{
protected:
	Node* root;
	int size;

	void print(Node* node);
	int height();
	void printPerLevel(Node* node, int level, int requieredLevel);
	void code(Node* node, BitStreamer& stream, string& chars); // build huffman code
public:
	HuffmanTree();
	~HuffmanTree();
	HuffmanTree(Heap& heap);
	void freeTree(Node* node);
	void setDictionary(Node* node, const string& code, Hash& hash);
	Hash& getDictionary();
	void print(PRINT_TYPE type = PREORDER);
	string buildFullHeader(); // build and encapsulate full header
	string encode(const string& data); // encode given data
};

#endif