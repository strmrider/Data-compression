#include "HuffmanTreeDecoder.h"

Node* HuffmanTreeDecoder::buildTree(const string& chars, int* charIndex, BitStreamerDecoder& stream)
{
	int bit = abs((int)stream.next());
	Node* node;
	if (bit == 0)
	{
		 node = new Node(chars[*charIndex], -1);
		(*charIndex)++;
	}
	else
	{
		node= new Node('*', -1);
		node->setLeft(buildTree(chars, charIndex, stream));
		node->setRight(buildTree(chars, charIndex, stream));
	}
	return node;
}

HuffmanTreeDecoder::HuffmanTreeDecoder(const string& encodedTree)
{
	unsigned char len = encodedTree[0];
	int leafs = (int)len;
	int branches = encodedTree.length() - leafs;
	string chars(encodedTree.begin() + branches, encodedTree.end());
	BitStreamerDecoder stream(1, branches, encodedTree);
	int* index = new int(0);
	root = buildTree(chars, index, stream);
}


string& HuffmanTreeDecoder::decode(const string& encodedData)
{
	string* decodedText = new string();
	int completion = (int)encodedData[0];
	int totalBits = ((encodedData.length() -1)* 8) - completion;
	int bits = 0;
	Node* node = root;
	BitStreamerDecoder stream(1, encodedData.length(), encodedData);
	int bit; 
	while (bits < totalBits)
	{
		bit = abs((int)stream.next());
		bits++;
		if (node->vacant() != 1)
		{
			if (bit == 0)
				node = node->getLeft();
			else if (bit == 1)
				node = node->getRight();

			if (node->vacant() == 1)
			{
				*decodedText += node->getCharObj().getChar();
				node = root;
			}
		}
	}
	return *decodedText;
}

void HuffmanTreeDecoder::print()
{
	HuffmanTree::print(LEVEL);
}