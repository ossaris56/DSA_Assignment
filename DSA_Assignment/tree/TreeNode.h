#pragma once
#include <filesystem>
#include "../vector/Vector.h"

namespace fs = std::filesystem;

struct TreeNode
{
  fs::path path;
  bool isDirectory;
  TreeNode* parent;
  Vector<TreeNode*> children;
};

inline TreeNode* NewTreeNode(fs::path path, bool isDirectory, TreeNode* parent = NULL)
{
  TreeNode* temp = new TreeNode;
  temp->path = path;
  temp->isDirectory = isDirectory;
  temp->parent = parent;
  return temp;
}
