#include "Node.h"

Node::Node(char newChar, int frequency) : character(newChar, frequency)
{
	left = NULL;
	right = NULL;
	subTree = NULL;
};

Node::Node(Node* node1, Node* node2, int frequency): character('*', frequency)
{
	left = NULL;
	right = NULL;
	subTree = new Node('*', frequency);
	subTree->setLeft(node1);
	subTree->setRight(node2);
}

Character& Node::getCharObj()
{
	return character;
}

Node* Node::getLeft()
{
	return left;
}

Node* Node::getRight()
{
	return right;
}

void Node::setLeft(Node* newLeft)
{
	left = newLeft;
}

void Node::setRight(Node* newRight)
{
	right = newRight;
}

Node* Node::getSubTree()
{
	return subTree;
}

void Node::setSubTree(Node* root)
{
	subTree = root;
}

VACANCY Node::vacant()
{
	if (!left && !right)
		return BOTH;
	else if (left && !right)
		return RIGHT;
	else if (!left && right)
		return LEFT;
	else
		return NONE;
}


Node* Node::compareChildPerOrder(HEAP_ORDER order, Node* child)
{
	if (child)
	{
		if (order == MAX)
			return (child->getCharObj().getFreq() >= getCharObj().getFreq()) ? (child) : (NULL);
		else
			return (child->getCharObj().getFreq() <= getCharObj().getFreq()) ? (child) : (NULL);
	}
	return NULL;
}

int Node::notInPlace(HEAP_ORDER order)
{
	bool left = compareChildPerOrder(order, this->left);
	bool right = compareChildPerOrder(order, this->right);

	if (left && right) // both
		return 1;
	if (left && !right) // right
		return 2;
	else if (!left && right) // left
		return 3;
	else
		return 0; // in place

}

// returns bigger child to replace or null if there isn't
Node* Node::repChild(HEAP_ORDER order)
{
	if (!left && !right)
		return NULL;
	else if (left && right)
	{
		int leftFrequency = left->getCharObj().getFreq();
		int rightFrequency = right->getCharObj().getFreq();
		if (order == MAX)
		{
			if (compareChildPerOrder(MAX, left) || 
				compareChildPerOrder(MAX, right) )
				return (leftFrequency >= rightFrequency) ? (left) : (right);
		}
		else
		{
			if (compareChildPerOrder(MIN, left)
				|| compareChildPerOrder(MIN, right))
				return (leftFrequency <= rightFrequency) ? (left) : (right);
		}
		return NULL;
	}
	else
	{
		if (right)
			return compareChildPerOrder(order, right);
		else
			return compareChildPerOrder(order, left);
	}
}

int Node::height()
{
	VACANCY vacancy = vacant();
	if (vacancy == BOTH)
		return 0;
	else if (vacancy == NONE)
	{
		int l = left->height();
		int r = right->height();
		return ((l > r) ? (l) : (r)) + 1;
	}
	else if (vacancy == RIGHT)
		return left->height() + 1;
	else
		return right->height() + 1;
}

Node* Node::highestChild()
{
	VACANCY vacancy = vacant();
	if (vacancy == BOTH)
		return NULL;
	else if (vacancy == NONE)
	{
		return ((left->height() > right->height()) ? (left) : (right));
	}
	else if (vacancy == RIGHT)
		return right;
	else
		return left;
}

void Node::makeVacant()
{
	left = NULL;
	right = NULL;
}
