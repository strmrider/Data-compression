#ifndef HASH_H
#define HASH_H
#include "Character.h"


class Hash
{
private:
	Character** charsTable;
	int size;
	int items;
	// randomal numbers for hash function calculations
	int a, b;
	int hashFunc(char ch, int attempt = 0);
public:
	Hash(int initSize);
	~Hash();

	void add(char newChar);
	int add(Character* newChar);
	void Hash::add(char newChar, string code);
	int search(char ch);
	void remove(char ch);
	Character* getCharObj(char ch);
	void handleChar(char ch);
	int  getNumOfItems();
	// array of all inserted characters
	Character** getCharsArray(bool freq = false);
};

#endif // !HASH_H


