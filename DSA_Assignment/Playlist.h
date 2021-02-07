#pragma once
#include <string>
#include "DoublyLinkedList.h"

struct Playlist
{
  std::string name;
  DoublyLinkedList* songs;
  int currentIndex;
};
