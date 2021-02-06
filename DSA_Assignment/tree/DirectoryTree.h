#pragma once
#include "../vector/Vector.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

struct Node
{
  fs::path path;
  bool isDirectory;
  Vector<Node*> children;
};

Node* NewNode(fs::path path, bool isDirectory)
{
  Node* temp = new Node;
  temp->path = path;
  temp->isDirectory = isDirectory;
  return temp;
}

class DirectoryTree
{
 private:
  Node* rootNode;

 public:
  DirectoryTree();
  DirectoryTree(Node* node);
  ~DirectoryTree();

  void AddFilesAndDirectoriesToRoot(Node*& node);
  void SortFilesAndDirectories(Node*& node);
};
