#pragma once
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct LinkedListNode
{
  fs::path data;         // Data
  LinkedListNode* prev;  // A reference to the previous node
  LinkedListNode* next;  // A reference to the next node
};

class DoublyLinkedList
{
  LinkedListNode* front;   // points to first node of list
  LinkedListNode* end;     // points to last node of list
  LinkedListNode* current; // points to current node of list
  int size;				   // size of list

 public:
  DoublyLinkedList();			// Constructor
  void AddFront(fs::path s);	// Add to the front of list
  void AddAfter(LinkedListNode* n, fs::path s);		//Add after a node
  void AddBefore(LinkedListNode* n, fs::path s);	//Add before a node
  void AddEnd(fs::path s);		// Add to the end of list
  /*void DeleteNode(LinkedListNode* n);*/
  void Forward();				// Traverse the list forward
  void Backward();				// Traverse the list backward
  LinkedListNode* Get(int index); // Get node at index
  void Print();					// Prints out items list
  int GetLength();				// Size of list
  LinkedListNode* GetCurrent();	// Get current node
  void DeleteItem(int index);	// Delete items at index in list
};