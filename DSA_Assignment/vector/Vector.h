#pragma once
#include <iostream>

template <class T>
class Vector
{
 private:
  T* arr;
  int capacity;
  int size;

 public:
  typedef T* iterator;

  Vector()
  {
    arr = new T[1];
    capacity = 1;
    size = 0;
  }

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

  void InsertAt(T data, int index)
  {
    if (index == capacity)
      PushBack(data);
    else
      arr[index] = data;
  }

  T Get(int index)
  {
    if (index < size) return arr[index];
  }

  void RemoveAt(int index)
  {
    delete arr[index];

    for (size_t i = index; i < size; i++)
    {
      arr[i + 1] = arr[i];
    }

    size--;
  }

  void Pop()
  {
    delete arr[size];
    size--;
  }

  int Size()
  {
    return size;
  }

  T& Back()
  {
    return arr[size - 1];
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
