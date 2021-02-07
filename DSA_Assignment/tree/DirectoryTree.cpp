#include "DirectoryTree.h"

/*
  Name : Chua Zhao Lin Jasper
  Team : Team 3
  Student ID : S10177296F
  Cool Features : Recursively add files and directories to a project root,
                  Sorts directories to be in front of files alphabetically
*/
DirectoryTree::DirectoryTree()
{
}

// DirectoryTree constructor with rootNode as parameter
DirectoryTree::DirectoryTree(TreeNode* node)
{
  rootTreeNode = node;
  AddFilesAndDirectoriesToRoot(rootTreeNode);
  SortFilesAndDirectories(rootTreeNode);
}

// DirectoryTree destructor
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

  // Iterate over files and directories
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

// Sorts directories to be in front of files alphabetically
void DirectoryTree::SortFilesAndDirectories(TreeNode*& node)
{
  Vector<TreeNode*> directories;
  Vector<TreeNode*> files;
  for (size_t i = 0; i < node->children.Size(); i++)
  {
    // If it is not a directory, add to the files vector
    if (node->children[i]->isDirectory == false)
    {
      files.PushBack(node->children[i]);
    }
    // If it is a directory, add to the directories vector
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

  // Set node's children to be the new sorted Vector
  node->children = directories;
}
