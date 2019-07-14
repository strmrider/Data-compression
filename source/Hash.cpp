#include "Hash.h"


Hash::Hash(int size)
{
	this->size = size;
	items = 0;
	charsTable = new Character*[size];
	for (int i = 0; i < size; i++)
		charsTable[i] = NULL;
	a = rand();
	b = rand();
}

Hash::~Hash()
{
	for (int i = 0; i < size; i++)
		delete charsTable[i];
	delete[] charsTable;
}

 int Hash::hashFunc(char ch, int attempt)
{
	return abs(((a*ch) + b + attempt) % (size-1));
}

int Hash::search(char ch)
{
	int attempt = 0;
	int index;
	while (attempt <= size)
	{
		index = hashFunc(ch, attempt);
		if (charsTable[index])
		{
			if (charsTable[index]->getChar() == ch)
				return index;
		}
		attempt++;
	}
	return -1;
}

void Hash::add(char newChar)
{
	int attempt = 0;
	int index;
	while (attempt <= size)
	{
		index = hashFunc(newChar, attempt);
		if (!charsTable[index])
		{
			charsTable[index] = new Character(newChar);
			break;
		}
		else
			attempt++;
	}
	items++;
}

void Hash::add(char newChar, string code)
{
	int attempt = 0;
	int index;
	while (attempt <= size)
	{
		index = hashFunc(newChar, attempt);
		if (!charsTable[index])
		{
			charsTable[index] = new Character(newChar, code);
			break;
		}
		else
			attempt++;
	}
	items++;
}

int Hash::add(Character* newChar)
{
	int attempt = 0;
	int index = 0;
	while (attempt <= size)
	{
		index = abs(hashFunc(newChar->getChar(), attempt));
		if (!charsTable[index])
		{
			charsTable[index] = newChar;
			items++;
			return 0;
		}
		else
			attempt++;
	}
	return -1;
}

void Hash::remove(char ch)
{
	int index = search(ch);
	if (index != -1)
	{
		delete charsTable[index];
		charsTable[index] = NULL;
	}
	items--;
}

void Hash::handleChar(char ch)
{
	int index = search(ch);
	// adds new one if character doesn't exist
	if (index == -1)
		add(ch);
	//increases frequency if exists
	else
		charsTable[index]->increase();
}

Character* Hash::getCharObj(char ch)
{
	int index = search(ch);
	if (index == -1)
		return NULL;
	else
		return charsTable[index];
}

int Hash::getNumOfItems()
{
	return items;
}

Character** Hash::getCharsArray(bool bits)
{
	Character** arr = new Character*[items];
	for (int i = 0, j=0; i < size; i++)
	{
		if (charsTable[i])
		{
			if(!bits)
				arr[j] = new Character(charsTable[i]->getChar(),
									charsTable[i]->getFreq());
			else
				arr[j] = new Character(charsTable[i]->getChar(),
					charsTable[i]->getBits());
			j++;
		}
	}
	return arr;
}