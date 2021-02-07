#pragma once
#include <filesystem>
#include "../vector/Vector.h"

/*
  Name : Chua Zhao Lin Jasper
  Team : Team 3
  Student ID : S10177296F
*/
// namespace just to make it easier to type std::filesystem
namespace fs = std::filesystem;

// TreeNode to represent files and directories in the general tree
struct TreeNode
{
  fs::path path;
  bool isDirectory;
  TreeNode* parent;
  Vector<TreeNode*> children;
};

// Create a new TreeNode*
inline TreeNode* NewTreeNode(fs::path path, bool isDirectory, TreeNode* parent = NULL)
{
  TreeNode* temp = new TreeNode;
  temp->path = path;
  temp->isDirectory = isDirectory;
  temp->parent = parent;
  return temp;
}
