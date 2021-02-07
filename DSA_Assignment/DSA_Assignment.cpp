// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends
// there.
//

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include "tree/DirectoryTree.h"
#include "DoublyLinkedList.h"

namespace fs = std::filesystem;

void MainMenu();
void SongMenu(TreeNode* musicFile);
void SongLibraryMenu(Vector<TreeNode*> directory);
void PlayingSongMenu(DoublyLinkedList songQueue);
Vector<TreeNode*> GetRootMusicDirectory();

void MainMenu()
{
  int option = -1;
  Vector<TreeNode*> rootMusicDirectory = GetRootMusicDirectory();
  while (option != 0)
  {
    std::cout << "\nMusic Player" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "[1] View song library" << std::endl;
    std::cout << "[2] View playlist" << std::endl;
    std::cout << "[3] Organize songs" << std::endl;
    std::cout << "[4] Search" << std::endl;
    std::cout << "[0] Exit" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> option;
    switch (option)
    {
      case 0:
        return;
      case 1:
        SongLibraryMenu(rootMusicDirectory);
        break;
      case 2:
        // std::cout << "\nPlaylist" << std::endl;
        // std::cout << "==========================" << std::endl;
        //// Display list of songs in playlist
        // std::cout << "[0] Main Menu" << std::endl;
        // std::cout << "Select Music: ";
        // std::cin >> musicOption;
        // SongMenu(musicOption);
        break;
      default:
        std::cout << "Invalid input, please try again" << std::endl;
        break;
    }
  }
}

void SongLibraryMenu(Vector<TreeNode*> directory)
{
  int option = -1;
  std::cout << std::endl;
  std::cout << "Song Library" << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "[0] Main Menu" << std::endl;
  // for every file in the /music folder
  for (size_t i = 1; i <= directory.Size(); i++)
  {
    std::string musicName = "[" + std::to_string(i) + "] ";
    // Get filename of current file and append it into musicName
    musicName += directory[i - 1]->path.filename().u8string();
    std::cout << musicName << std::endl;
  }
  std::cout << "Select Song/Folder : ";
  std::cin >> option;
  if (option == 0)
  {
    return;
  }
  if (option < 0 || option > directory.Size())
  {
    std::cout << "Invalid input, please try again";
    SongLibraryMenu(directory);
  }
  if (directory[option - 1]->isDirectory)
  {
    SongLibraryMenu(directory[option - 1]->children);
  }
  else
  {
    SongMenu(directory[option - 1]);
  }
}

void SongMenu(TreeNode* musicFile)
{
  int option = -1;
  DoublyLinkedList songQueue;
  std::string musicPath = musicFile->path.u8string();
  // convert path to const TCHAR* for use in PlaySound
  std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
  const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();

  std::cout << std::endl;
  // Display selected music title
  std::cout << musicFile->path.stem() << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "[1] Play Song" << std::endl;
  // Check if song is in playlist
  std::cout << "[2] Add to Playlist" << std::endl;  // If song is not in playlist
  // std::cout << "[2] Remove from Playlist" << std::endl;  // If song is in playlist
  std::cout << "[0] Song Library" << std::endl;
  std::cout << "Select Option:";
  std::cin >> option;

  switch (option)
  {
    case 0:
      SongLibraryMenu(musicFile->parent->children);
    case 1:
      songQueue.AddEnd(musicPath);
      PlaySound(constTcharMusicPath, NULL,
                SND_FILENAME | SND_ASYNC);  // To play the corresponding song
      PlayingSongMenu(songQueue);
      break;
    case 2:
      break;
    default:
      std::cout << "Invalid input, please try again." << std::endl;
      SongMenu(musicFile);
  }
}

void PlayingSongMenu(DoublyLinkedList songQueue)
{
  int option = -1;
  int currentSongIndex = 0;
  std::cout << "[0] Stop and Exit" << std::endl;
  std::cout << "[1] Replay" << std::endl;
  std::cout << "[2] Next" << std::endl;
  std::cout << "[3] Previous" << std::endl;
  std::cin >> option;

  switch (option)
  {
    case 0:
      SongLibraryMenu(GetRootMusicDirectory());
      break;
    case 1:
      // TODO: remove comment when at is implemented in doubly linked list
      // PlaySound(NULL, 0, 0);
      // PlaySound((const TCHAR*)songQueue.At(currentSongIndex).c_str(), 0, 0);
      PlayingSongMenu(songQueue);
      break;
    case 2:
      PlayingSongMenu(songQueue);
      break;
    case 3:
      PlayingSongMenu(songQueue);
      break;
  }
}

Vector<TreeNode*> GetRootMusicDirectory()
{
  TreeNode* musicNode = NewTreeNode(fs::current_path().parent_path() / "music", true);
  DirectoryTree musicDirectoryTree = DirectoryTree(musicNode);
  Vector<TreeNode*> musicDirectory = musicDirectoryTree.rootTreeNode->children;
  return musicDirectory;
}
int main()
{
  MainMenu();
}
