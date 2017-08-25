#include <iostream>
static class Node
{
private:
	size_t* data;
	Node* next;
	Node* prev;

	Node()
	{
		Node(NULL, NULL, NULL);
	}
	Node(size_t* d, Node* n, Node* p)
	{
		data = d;
		next = n;
		prev = p;
	}
};

class MyLinkedList
{
private:
	int* size;
	int* count;
	Node* beginMaker;
	Node* endMaker;
};