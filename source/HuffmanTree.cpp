#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(): root(NULL), size(0) {};

HuffmanTree::HuffmanTree(Heap& heap): root(NULL), size(0)
{
	Node* tmpNode1;
	Node* tmpNode2;
	Node* newSubTree;
	Node* newNode;
	int sum;
	while (heap.getSize()>0)
	{
		tmpNode1 = heap.top();
		tmpNode1->makeVacant();
		tmpNode2 = heap.top();
		tmpNode2->makeVacant();

		sum = tmpNode1->getCharObj().getFreq() + tmpNode2->getCharObj().getFreq();
		
		if (tmpNode1->getSubTree())
			tmpNode1 = tmpNode1->getSubTree();
		if (tmpNode2->getSubTree())
			tmpNode2 = tmpNode2->getSubTree();

		newSubTree = new Node(tmpNode1, tmpNode2, sum);

		if (heap.isEmpty())
			root = newSubTree->getSubTree();
		else
			heap.insert(newSubTree);
	}
}

HuffmanTree::~HuffmanTree()
{
	freeTree(root);
}

void HuffmanTree::freeTree(Node* node)
{
	if (node)
	{
		freeTree(node->getLeft());
		freeTree(node->getRight());

		delete node;
	}
}

void HuffmanTree::setDictionary(Node* node, const string& code, Hash& hash)
{
	if (node)
	{
		if (node->getRight() == NULL && node->getLeft() == NULL)
			hash.add(new Character(node->getCharObj().getChar(), code));

		setDictionary(node->getLeft(), code + "0", hash);
		setDictionary(node->getRight(), code + "1", hash);
	}
}

Hash& HuffmanTree::getDictionary()
{
	Hash* hash = new Hash(1024);
	setDictionary(root, "", *hash);
	return *hash;
}

int HuffmanTree::height()
{
	return root ? root->height() : 0;
}

void HuffmanTree::printPerLevel(Node* node, int level, int requieredLevel)
{
	if (!node)
		return;
	if (level == requieredLevel)
	{
		if (node->vacant() == 0)
			cout << "* ";
		else
			cout << node->getCharObj().getChar() << " ";
	}
	else if (level < requieredLevel)
	{
		printPerLevel(node->getLeft(), level + 1, requieredLevel);
		printPerLevel(node->getRight(), level + 1, requieredLevel);
	}
}

void HuffmanTree::code(Node* node, BitStreamer& stream, string& chars)
{
	if (node == NULL)
		return;
	if (node->vacant())
	{
		stream << "0";
		chars += node->getCharObj().getChar();
	}
	else
		stream << "1";
	code(node->getLeft(), stream, chars);
	code(node->getRight(), stream, chars);
}

string HuffmanTree::buildFullHeader()
{
	BitStreamer streamer;
	string chars;
	code(root, streamer, chars);
	int len = chars.length();
	if (len > 255)
		len = 255;

	// final code, includes huffman code and the encoded chars
	return (char)len + (streamer.finish(true, false)) + chars;
}

string HuffmanTree::encode(const string& data)
{
	Hash* dictionary = &getDictionary();
	BitStreamer streamer;
	string encoded;
	for (int i = 0; i < data.length(); i++)
		streamer << dictionary->getCharObj(data[i])->getBits();
	delete dictionary;

	return streamer.finish(true, true);
}

/* print metods */

void HuffmanTree::print(PRINT_TYPE type)
{
	if (!root)
		cout << "Empty\n";
	else if (type == PREORDER)
		print(root);
	else if (type == LEVEL)
	{
		for (int i = 0; i < height() + 1; i++)
		{
			printPerLevel(root, 0, i);
			cout << endl;
		}
	}
}

void HuffmanTree::print(Node* node)
{
	if (node)
	{
		std::cout << node->getCharObj().getChar() << std::endl;
		print(node->getLeft());
		print(node->getRight());
	}
}
