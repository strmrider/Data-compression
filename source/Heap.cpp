#include "Heap.h"

Heap::Heap(HEAP_ORDER heapOrder)
{
	root = NULL;
	order = heapOrder;
	size = 0;
}

Heap::~Heap()
{

}

bool Heap::isEmpty()
{
	return root ? false : true;
}

int Heap::height()
{
	return root ? root->height() : 0;
}

void Heap::replaceNode(Node* node)
{
	Node* child = node->repChild(order);
	if (child)
	{
		Node* tmpSub = child->getSubTree();
		child->setSubTree(node->getSubTree());
		node->setSubTree(tmpSub);

		Character tmp = node->getCharObj();
		node->getCharObj() = child->getCharObj();
		child->getCharObj() = tmp;
	}
}

void Heap::insert(Node* node, Node* newNode, vector<int>* path, int index)
{
	if (index < 0)
		return;
	if (index == 0)
	{
		if ((*path)[index] == 0)
			node->setLeft(newNode);
		else
			node->setRight(newNode);
	}
	if ((*path)[index] == 0)
		insert(node->getLeft(), newNode, path, index -1);
	else
		insert(node->getRight(), newNode, path, index -1);
	replaceNode(node);
}

void Heap::insert(Node* node)
{
	if (!root)
		root = node;
	else if (size == 1)
	{
		root->setLeft(node);
		selfOrder(root);
	}
	else
	{
		vector<int>* p = path(size+1);
		insert(root, node, p, p->size()-1);
		delete p;
	}
	size++;
}

void Heap::selfOrder(Node* node)
{
	if (node)
	{
		Node* child = node->repChild(order);
		if (child)
		{
			replaceNode(node);
			selfOrder(child);
		}
	}
}

Node* Heap::top()
{
	if (isEmpty())
		return NULL;
	// only one element in heap
	else if (!root->getLeft() && !root->getRight())
	{
		size = 0;
		Node* tmp = root;
		root = NULL;
		return tmp;
	}

	Node* lastNodeParent = last(true);
	Node* lastNode;
	if (lastNodeParent->getRight())
	{
		lastNode = lastNodeParent->getRight();
		lastNodeParent->setRight(NULL);
	}
	else
	{
		lastNode = lastNodeParent->getLeft();
		lastNodeParent->setLeft(NULL);
	}

	Node* tmp = root;
	root = lastNode;
	lastNode->setRight(tmp->getRight());
	lastNode->setLeft(tmp->getLeft());
	selfOrder(root);
	size--;
	return tmp;
}

// initialQ is initial q in order to ignore first q when only parent is needed
Node* Heap::last(int initialQ, int q, int remainder, Node* node, bool parent)
{
	if ( q >= 2)
	{
		node = last(initialQ, q / 2, (q / 2) % 2, node, parent);
		if (!parent || (parent &&  q != initialQ))
		{
			if (remainder == 0)
				node = node->getLeft();
			else
				node = node->getRight();
		}
		return node;
	}
	else
		return root;
}


vector<int>* Heap::path(int q)
{
	vector<int>* path = new vector<int>();
	while (q >= 2)
	{
		path->push_back(q % 2);
		q /= 2;
	}
	return path;
}

Node* Heap::last(bool parent)
{
	return last(size, size, size%2, root, parent);
}


/****************
* Print methods
*****************/
void Heap::print(Node* node)
{
	if (!node)
		return;
	cout << node->getCharObj().getFreq() << endl;
	print(node->getLeft());
	print(node->getRight());
}

void Heap::print()
{
	if (!root)
		cout << "Empty\n";
	else
		print(root);
}

void Heap::printPerLevel(Node* node, int level, int requieredLevel)
{
	if (node)
	{
		if (level == requieredLevel)
			cout << node->getCharObj().getFreq() << " ";
		else if (level < requieredLevel)
		{
			printPerLevel(node->getLeft(), level + 1, requieredLevel);
			printPerLevel(node->getRight(), level + 1, requieredLevel);
		}
	}
}

void Heap::printPerLevel()
{
	if (!root)
		cout << "Empty\n";
	for (int i = 0; i < height()+1; i++)
	{
		printPerLevel(root, 0, i);
		cout << endl;
	}
}