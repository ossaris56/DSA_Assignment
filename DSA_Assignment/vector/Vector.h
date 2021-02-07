#pragma once
#include <iostream>

/*
  Name : Chua Zhao Lin Jasper
  Team : Team 3
  Student ID : S10177296F
  Cool Features : Working operators and templated class
*/
template <class T>
class Vector
{
 private:
  T* arr;
  int capacity;
  int size;

 public:
  typedef T* iterator;

  // Vector constructor
  Vector()
  {
    arr = new T[1];
    capacity = 1;
    size = 0;
  }

  // Appends an object to the end of the vector
  void PushBack(T data)
  {
    // create new array with more space to accomodate more items
    if (size == capacity)
    {
      T* temp = new T[2 * capacity];

      // copy old items to new array
      for (size_t i = 0; i < capacity; i++)
      {
        temp[i] = arr[i];
      }

      // delete previous array
      delete[] arr;
      capacity *= 2;
      arr = temp;
    }

    arr[size] = data;
    size++;
  }

  typename iterator Begin()
  {
    return arr;
  }

  typename iterator End()
  {
    return arr + Size();
  }

  // Inserts data at a specified index
  void InsertAt(T data, int index)
  {
    if (index == capacity)
      PushBack(data);
    else
      arr[index] = data;
  }

  // Gets an object at a specified index
  T Get(int index)
  {
    if (index < size) return arr[index];
  }

  // Removes an object at a specified index
  void RemoveAt(int index)
  {
    delete arr[index];

    for (size_t i = index; i < size; i++)
    {
      arr[i + 1] = arr[i];
    }

    size--;
  }

  // Remove an object at the end of the vector
  void Pop()
  {
    delete arr[size];
    size--;
  }

  // Returns the size of the vector
  int Size()
  {
    return size;
  }

  // Returns the last item of the vector
  T& Back()
  {
    return arr[size - 1];
  }

  // Prints the items of the vector
  void Print()
  {
    for (size_t i = 0; i < size; i++)
    {
      std::cout << arr[i] << std::endl;
    }
  }

  // Square bracket operators to access an index of the vector
  T& operator[](int index)
  {
    return arr[index];
  }

  // Equal operator to assign a new vector into the current vector
  Vector<T>& operator=(Vector<T>& vector)
  {
    delete[] arr;
    size = vector.size;
    capacity = vector.capacity;
    arr = new T[size];
    for (size_t i = 0; i < size; i++)
    {
      arr[i] = vector.arr[i];
    }
    return *this;
  }
};
