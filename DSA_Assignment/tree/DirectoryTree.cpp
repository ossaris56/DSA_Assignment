#include "DirectoryTree.h"

DirectoryTree::DirectoryTree()
{
}

DirectoryTree::DirectoryTree(TreeNode* node)
{
  rootTreeNode = node;
  AddFilesAndDirectoriesToRoot(rootTreeNode);
  SortFilesAndDirectories(rootTreeNode);
}

DirectoryTree::~DirectoryTree()
{
  delete rootTreeNode;
}

// Recursively populates rootTreeNode with files and directories
void DirectoryTree::AddFilesAndDirectoriesToRoot(TreeNode*& node)
{
  if (fs::is_empty(node->path))
  {
    return;
  }

  for (const auto& entry : fs::directory_iterator(node->path))
  {
    // If the file isnt a directory, add it to the children of the current TreeNode
    if (!fs::is_directory(entry))
    {
      if (entry.path().extension() == ".wav")
      {
        TreeNode* temp = NewTreeNode(entry, false, node);
        node->children.PushBack(temp);
      }
    }
    else
    {
      // Only add wav files as PlaySound only supports wav files
      TreeNode* temp = NewTreeNode(entry, true, node);
      node->children.PushBack(temp);
      TreeNode* directoryTreeNode = node->children.Back();
      AddFilesAndDirectoriesToRoot(directoryTreeNode);
    }
  }
}

void DirectoryTree::SortFilesAndDirectories(TreeNode*& node)
{
  Vector<TreeNode*> directories;
  Vector<TreeNode*> files;
  for (size_t i = 0; i < node->children.Size(); i++)
  {
    if (node->children[i]->isDirectory == false)
    {
      files.PushBack(node->children[i]);
    }
    else
    {
      directories.PushBack(node->children[i]);
      SortFilesAndDirectories(node->children[i]);
    }
  }

  // Append directories to be in front of files
  for (size_t i = 0; i < files.Size(); i++)
  {
    directories.PushBack(files[i]);
  }

  node->children = directories;
}
