#pragma once
#ifndef NODE_H
#define NODE_H
#include "Hash.h"


class Node
{
private:
	Character character;
	Node* left;
	Node* right;
	Node* subTree;

	Node* compareChildPerOrder(HEAP_ORDER order, Node* child);
	Node* highestChild();
	int notInPlace(HEAP_ORDER order);
public:
	Node(char newChar, int frequency);
	Node(Node* node1 , Node* node2, int frequency);

	Character& getCharObj();
	Node* getLeft();
	Node* getRight();
	Node* getSubTree();
	void setLeft(Node* newLeft);
	void setRight(Node* newRight);
	void setSubTree(Node* root);

	VACANCY vacant();
	int height();
	// return replaceable child or NULL if there isn't
	Node* repChild(HEAP_ORDER order);

	void makeVacant();
};
#endif // !NODE_H
