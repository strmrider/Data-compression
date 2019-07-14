#include "Compression.h"

namespace compression {
	// extracts the relevant huffman tree code from the header
	int extractTreeSegemntCode(const string& code)
	{
		unsigned char c = code[0];
		int leaves = (int)c;
		int branches = (leaves - 1) + leaves;
		int compeltion = 0;

		if ((branches % 8) > 0)
			compeltion = (8 - (branches % 8));
		branches = (branches + compeltion) / 8;
		int total = 1 + branches + leaves;

		return total;
	}

	string encodeText(const string& txt, Hash& dict)
	{
		BitStreamer stream;
		for (int i = 0; i < txt.length(); i++)
		{
			stream << dict.getCharObj(txt[i])->getBits();
		}
		return stream.finish();
	}

	Heap& getHeap(const string& text)
	{
		Hash hash(1024);
		for (int i = 0; i < text.length(); i++)
			hash.handleChar(text[i]);

		Heap* heap = new Heap(MIN);
		Character** charsArr = hash.getCharsArray();
		for (int i = 0; i < hash.getNumOfItems(); i++)
			heap->insert(new Node(charsArr[i]->getChar(), charsArr[i]->getFreq()));

		for (int i = 0; i < hash.getNumOfItems(); i++)
			delete charsArr[i];
		delete[] charsArr;

		return *heap;
	}

	string& encode(const string& text)
	{
		string* encodedText = new string();

		Heap* heap = &getHeap(text);
		HuffmanTree tree(*heap);
		(*encodedText) += tree.buildFullHeader();
		(*encodedText) += tree.encode(text);
		return (*encodedText);
	}

	string& decode(const string& encodedText)
	{
		int len = extractTreeSegemntCode(encodedText);
		string treeCode(encodedText.begin(), encodedText.begin() + len);
		HuffmanTreeDecoder tree(treeCode);
		string encoded(encodedText.begin() + len, encodedText.end());

		string* decoded = &tree.decode(encoded);

		return *decoded;
	}

	string& readFromFile(const string& path)
	{
		ifstream file(path, ios::in | ios::binary);
		if (file) {
			file.seekg(0, file.end);
			int len = file.tellg();
			file.seekg(0, file.beg);
			char* data = new char[len];
			file.read(data, len);
			file.close();
			string *str = new string(data, len);
			return *str;
		}
		else {
			throw  "Source file not found"; 
		}
	}

	void writeToFile(ofstream& file, const string& data)
	{
		for (int i = 0; i < data.length(); i++)
			file.write((char*)&data[i], sizeof(char));
		file.close();
	}

	void compress(const string& data, const string& path)
	{
		string code = encode(data);
		ofstream file(path, ios::out | ios::binary);
		writeToFile(file, code);
	}

	void compressFile(const string& sourceFile, const string& targetFile)
	{
		string* data;
		try {
			data = &readFromFile(sourceFile);
			compress(*data, targetFile);
		}
		catch (char* error)
		{
			cout << error;
		}
	}

	void decompress(const string& data, const string& path)
	{
		string decodedData = decode(data);
		ofstream file(path, ios::out | ios::binary);
		writeToFile(file, decodedData);
	}


	string& decompress(const string& path)
	{
		string* data;
		try {
			data = &readFromFile(path);
			return decode(*data);
		}
		catch (char* error)
		{
			cout << error;
		}
	}

	void decompressFile(const string& sourceFile, const string& targetFile)
	{
		string* data;
		try
		{
			data = &readFromFile(sourceFile);
			decompress(*data, targetFile);
		}
		catch (char* error)
		{
			cout << error;
		}
	}
}
