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
  LinkedListNode* front;  // points to first node of list
  LinkedListNode* end;    // points to first las of list
  LinkedListNode* current;
  int size;

 public:
  DoublyLinkedList();
  void AddFront(fs::path s);
  void AddAfter(LinkedListNode* n, fs::path s);
  void AddBefore(LinkedListNode* n, fs::path s);
  void AddEnd(fs::path s);
  void DeleteNode(LinkedListNode* n);
  void Forward();
  void Backward();
  LinkedListNode* Get(int index);
  void Print();
  int GetLength();
  LinkedListNode* GetCurrent();
};