#pragma once
#include <iostream>
using namespace std;

struct node
{
  int data;    // Data
  node* prev;  // A reference to the previous node
  node* next;  // A reference to the next node
};

class Doubly_Linked_List
{
  node* front;  // points to first node of list
  node* end;    // points to first las of list
 public:
  Doubly_Linked_List()
  {
    front = NULL;
    end = NULL;
  }
  void add_front(int);
  void add_after(node*, int);
  void add_before(node*, int);
  void add_end(int);
  void delete_node(node*);
  void forward_traverse();
  void backward_traverse();
};