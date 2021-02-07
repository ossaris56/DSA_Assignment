#pragma once
#include "TreeNode.h"
#include <iostream>

namespace fs = std::filesystem;

/*
  Name : Chua Zhao Lin Jasper
  Team : Team 3
  Student ID : S10177296F
  Cool Features : Recursively add files and directories to a project root,
                  Sorts directories to be in front of files alphabetically
*/
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
