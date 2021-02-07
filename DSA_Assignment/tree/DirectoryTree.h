#pragma once
#include "TreeNode.h"
#include <iostream>

namespace fs = std::filesystem;

class DirectoryTree
{
 public:
  TreeNode* rootTreeNode;

  DirectoryTree();
  DirectoryTree(TreeNode* node);
  ~DirectoryTree();

  void AddFilesAndDirectoriesToRoot(TreeNode*& node);
  void SortFilesAndDirectories(TreeNode*& node);
};
