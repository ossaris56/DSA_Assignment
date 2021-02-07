#include "DoublyLinkedList.h";
DoublyLinkedList::DoublyLinkedList()
{
  front = NULL;
  end = NULL;
  current = NULL;
  size = 0;
}

void DoublyLinkedList::AddFront(fs::path d)
{
  // Creating new node
  LinkedListNode* temp;
  temp = new LinkedListNode();
  temp->data = d;
  temp->prev = NULL;
  temp->next = front;

  // List is empty
  if (front == NULL)
  {
    end = temp;
    current = temp;
  }

  else
    front->prev = temp;

  front = temp;
  size++;
}

void DoublyLinkedList::AddBefore(LinkedListNode* n, fs::path d)
{
  LinkedListNode* temp;
  temp = new LinkedListNode();
  temp->data = d;
  temp->next = n;
  temp->prev = n->prev;
  n->prev = temp;

  // if node is to be inserted before first node
  if (n->prev == NULL) front = temp;
  size++;
}

void DoublyLinkedList::AddAfter(LinkedListNode* n, fs::path d)
{
  LinkedListNode* temp;
  temp = new LinkedListNode();
  temp->data = d;
  temp->prev = n;
  temp->next = n->next;
  n->next = temp;

  // if node is to be inserted after last node
  if (n->next == NULL) end = temp;
  size++;
}

void DoublyLinkedList::AddEnd(fs::path d)
{
  // create new node
  LinkedListNode* temp;
  temp = new LinkedListNode();
  temp->data = d;
  temp->prev = end;
  temp->next = NULL;

  // if list is empty
  if (end == NULL)
  {
    front = temp;
    current = temp;
  }

  else
    end->next = temp;
  end = temp;
  size++;
}

void DoublyLinkedList::DeleteNode(LinkedListNode* n)
{
  // if node to be deleted is first node of list
  if (n->prev == NULL)
  {
    front = n->next;  // the next node will be front of list
    front->prev = NULL;
  }
  // if node to be deleted is last node of list
  else if (n->next == NULL)
  {
    end = n->prev;  // the previous node will be last of list
    end->next = NULL;
  }
  else
  {
    // previous node's next will point to current node's next
    n->prev->next = n->next;
    // next node's prev will point to current node's prev
    n->next->prev = n->prev;
  }
  // delete node
  delete (n);
  size--;
}

void DoublyLinkedList::Forward()
{
  if (current->next != NULL)
  {
    current = current->next;
  }
}

void DoublyLinkedList::Backward()
{
  if (current->prev != NULL)
  {
    current = current->prev;
  }
}

LinkedListNode* DoublyLinkedList::Get(int index)
{
  LinkedListNode* current = front;
  int count = 0;
  while (current != NULL)
  {
    if (count == index) return current;
    count++;
    current = current->next;
  }
}

void DoublyLinkedList::Print()
{
  LinkedListNode* current = front;
  int i = 1;

  while (current != NULL)
  {
    std::cout << "[" << i << "] ";
    std::cout << current->data << std::endl;
    current = current->next;
    i += 1;
  }
}

int DoublyLinkedList::GetLength()
{
  return size;
}

LinkedListNode* DoublyLinkedList::GetCurrent()
{
  return current;
}