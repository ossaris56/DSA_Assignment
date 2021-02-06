#pragma once
#include <iostream>
#include <string>

struct node
{
  std::string data;  // Data
  node* prev;        // A reference to the previous node
  node* next;        // A reference to the next node
};

class DoublyLinkedList
{
  node* front;  // points to first node of list
  node* end;    // points to first las of list
 public:
  // TODO: move to cpp file
  DoublyLinkedList()
  {
    front = NULL;
    end = NULL;
  }

  void AddFront(std::string);
  void AddAfter(node*, std::string);
  void AddBefore(node*, std::string);
  void AddEnd(std::string);
  void DeleteNode(node*);
  void ForwardTraverse();
  void BackwardTraverse();
};