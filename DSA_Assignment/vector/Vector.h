#pragma once
#include <iostream>

template <typename T>
class Vector
{
 private:
  T* arr;
  int capacity;
  int size;

 public:
  Vector()
  {
    arr = new T[1];
    capacity = 1;
    size = 0;
  }
  ~Vector()
  {
    delete arr;
  }

  void PushBack(T data)
  {
    // create new array with more space to accomodate more items
    if (size == capacity)
    {
      T* temp = new T[capacity * 2];

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

  void InsertAt(T data, int index)
  {
    if (index == capacity)
      pushBack(data);
    else
      arr[index] = data;
  }

  T Get(int index)
  {
    if (index < size) return arr[index];
  }

  void Pop()
  {
    size--;
  }

  int Size()
  {
    return size;
  }

  void Print()
  {
    for (size_t i = 0; i < size; i++)
    {
      std::cout << arr[i] << std::endl;
    }
  }

  T& operator[](int index)
  {
    return arr[index];
  }

  Vector<T>& operator=(const Vector<T>& vector)
  {
    delete arr;
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
