#pragma once
#include <iostream>
#include <string>

struct LinkedListNode
{
  std::string data;      // Data
  LinkedListNode* prev;  // A reference to the previous node
  LinkedListNode* next;  // A reference to the next node
};

class DoublyLinkedList
{
  LinkedListNode* front;  // points to first node of list
  LinkedListNode* end;    // points to first las of list
  int size;

 public:
  DoublyLinkedList();
  void AddFront(std::string s);
  void AddAfter(LinkedListNode* n, std::string s);
  void AddBefore(LinkedListNode* n, std::string s);
  void AddEnd(std::string s);
  void DeleteNode(LinkedListNode* n);
  void ForwardTraverse();
  void BackwardTraverse();
  LinkedListNode* Get(int index);
  void print();
  int getLength();
};