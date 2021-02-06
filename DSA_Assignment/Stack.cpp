#include "stack_pointerBased.h";

Stack::Stack() //constructor
{
	topNode = NULL;
}

Stack::~Stack() //destructor
{
	while (topNode != NULL)
	{
		this->pop();
	}
}

bool Stack::push(ItemType item)
{
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	
	newNode->next = topNode;
	topNode = newNode;

	return true;
}

bool Stack::pop()
{
	if (!isEmpty())
	{
		Node* temp = topNode;
		topNode = topNode->next;
		delete temp;
		temp = NULL;
	}
	return true;
}

bool Stack::pop(ItemType &item)
{
	if (!isEmpty())
	{
		item = topNode->item;
		Node* temp = topNode;
		topNode = topNode->next;
		delete temp;
		temp = NULL;
	}
	return true;
}

void Stack::getTop(ItemType &item)
{
	if (!isEmpty())
	{
		item = topNode->item;
	}
}

bool Stack::isEmpty() { return (topNode == NULL); }

void Stack::displayInOrder()
{
	if (!isEmpty())
	{
		Node* tempNode = topNode;
		while (tempNode->next != NULL)
		{
			cout << tempNode->item << "	";
			tempNode = tempNode->next;
		}
	}
}

void Stack::displayInOrderOfInsertion()
{
	
	Stack tempStack;

	if (!isEmpty())
	{
		while (!isEmpty())
		{
			ItemType item;
			pop(item);
			tempStack.push(item);
		}
		
		while (!tempStack.isEmpty())
		{
			ItemType tmpitem;
			tempStack.pop(tmpitem);
			cout << tmpitem << "	";
			push(tmpitem);
		}
	}
}