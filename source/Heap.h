#pragma once
#ifndef HEAP_H
#define HEAP
#include "Node.h"

class Heap
{
	Node* root;
	int size;
	HEAP_ORDER order;

	void insert(Node* node, Node* newNode, vector<int>* path, int index);
	void replaceNode(Node* node);
	// gets last node in heap
	Node* last(int initialQ, int q, int remainder, Node* node, bool parent); 
	// path to where new node should be inserted
	vector<int>* path(int q);
	// makes every element to fit the order- replace parent with child
	void selfOrder(Node* node);
	void print(Node* node);
	void printPerLevel(Node* node, int level, int requieredLevel);
public:
	Heap(HEAP_ORDER heapOrder = MAX);
	~Heap();

	Node* getRoot() { return root; };
	int getSize() { return size; };
	void insert(Node* node);
	Node* top();
	Node* last(bool parent = false);
	int height();
	bool isEmpty();
	void print();
	void printPerLevel();
};
#endif // !HEAP_H
