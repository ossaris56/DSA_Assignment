#include "DirectoryTree.h"

DirectoryTree::DirectoryTree()
{
}

DirectoryTree::DirectoryTree(Node* node)
{
  rootNode = node;
  AddFilesAndDirectoriesToRoot(rootNode);
  SortFilesAndDirectories(rootNode);
}

DirectoryTree::~DirectoryTree()
{
  delete rootNode;
}

// Recursively populates rootNode with files and directories
void DirectoryTree::AddFilesAndDirectoriesToRoot(Node*& node)
{
  if (fs::is_empty(node->path))
  {
    return;
  }

  for (const auto& entry : fs::directory_iterator(node->path))
  {
    if (!fs::is_directory(entry))
    {
      Node* temp = NewNode(entry, false);
      node->children.PushBack(temp);
    }
    else
    {
      Node* temp = NewNode(entry, true);
      node->children.PushBack(temp);
      Node* directoryNode = node->children.Back();
      AddFilesAndDirectoriesToRoot(directoryNode);
    }
  }
}

void DirectoryTree::SortFilesAndDirectories(Node*& node)
{
  Vector<Node*> directories;
  Vector<Node*> files;
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
