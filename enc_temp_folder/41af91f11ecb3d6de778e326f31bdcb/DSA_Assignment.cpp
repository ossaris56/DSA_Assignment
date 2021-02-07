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
#include "Playlist.h"

namespace fs = std::filesystem;

// Function prototypes
void MainMenu();
void SongMenu(TreeNode* musicFile);
void SongLibraryMenu(Vector<TreeNode*> directory);
void PlayingSongMenu(DoublyLinkedList songQueue);
void AllPlaylistsMenu(Vector<Playlist*>* playlists);
void PlaylistMenu(Playlist* playlist);
Vector<TreeNode*> GetRootMusicDirectory();
void AddSongToPlaylist(TreeNode* musicFile);
void AddPlaylist();
void RemovePlaylist();
void SearchSong(Vector<TreeNode*> directory);

namespace SongVariables
{
Vector<Playlist*>* playlists = new Vector<Playlist*>;
}

void MainMenu()
{
  int option = -1;
  Vector<TreeNode*> rootMusicDirectory = GetRootMusicDirectory();

  while (option != 0)
  {
    std::cout << std::endl;
    std::cout << "Music Player" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "[1] View song library" << std::endl;
    std::cout << "[2] View playlists" << std::endl;
    std::cout << "[3] Search Songs" << std::endl;
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
        AllPlaylistsMenu(SongVariables::playlists);
        break;
      case 3:
        break;
      case 4:
        /*SearchSong(rootMusicDirectory);*/
        break;
      default:
        std::cout << "Invalid input, please try again" << std::endl;
        break;
    }
  }
}

//void SearchSong(Vector<TreeNode*> directory)
//{ 
//  Vector<std::string> dummy;
//  dummy.PushBack("Flower");
//  dummy.PushBack("blah");
//  std::vector<std::string>::iterator item;
//  std::string userTitle;
//  std::cout << "Enter title: ";
//  std::cin >> userTitle;
//  item = std::find(dummy.Begin(), dummy.End(), userTitle);
//  if (item != dummy.Size())
//  {
//    std::cout << item - dummy.Begin() << " (counting from zero) \n"; 
//  }
//}

void AllPlaylistsMenu(Vector<Playlist*>* playlists)
{
  int option = -1;
  std::cout << std::endl;
  if (playlists->Size() == 0)
  {
    std::cout << "No playlists available" << std::endl;
  }
  std::cout << "[0] Main Menu" << std::endl;

  // Display the names of the playlists
  for (size_t i = 1; i <= playlists->Size(); i++)
  {
    std::string playlistName = "[" + std::to_string(i) + "] " + playlists->operator[](i - 1)->name;
    std::cout << playlistName << std::endl;
  }

  std::cout << "[" + std::to_string(playlists->Size() + 1) + "] Create Playlist" << std::endl;
  std::cout << "[" + std::to_string(playlists->Size() + 2) + "] Delete Playlist" << std::endl;
  std::cout << "Enter option : ";
  std::cin >> option;

  // If user wants to exit
  if (option == 0)
  {
    MainMenu();
  }

  // If user selects a playlist
  if (option <= playlists->Size())
  {
    PlaylistMenu(playlists->operator[](option-1));
  }

  // Create a new playlist
  if (option == (playlists->Size() + 1))
  {
    AddPlaylist();
    AllPlaylistsMenu(SongVariables::playlists);
  }

  // Remove an existing playlist
  if (option == (playlists->Size() + 2))
  {
    RemovePlaylist();
  }
}

void RemovePlaylist()
{
  int option = -1;
  Vector<Playlist*>* playlists = SongVariables::playlists;
  std::cout << std::endl;

  if (playlists->Size() <= 0)
  {
    std::cout << "No playlists available" << std::endl;
    AllPlaylistsMenu(playlists);
  }
  std::cout << "Select a playlist to remove" << std::endl;
  std::cout << "===============================" << std::endl;
  std::cout << "[0] Back" << std::endl;
  // Display the names of the playlists
  for (size_t i = 1; i <= playlists->Size(); i++)
  {
    std::string playlistName = "[" + std::to_string(i) + "] " + playlists->operator[](i - 1)->name;
    std::cout << playlistName << std::endl;
  }

  std::cout << "Enter Option : ";
  std::cin >> option;

  // TODO :: add checks when < 0 and > playlists.size()
  if (option == 0)
  {
    AllPlaylistsMenu(playlists);
  }
  if (option <= playlists->Size())
  {
    std::cout << "Removing " << playlists->operator[](option - 1)->name << std::endl;
    playlists->RemoveAt(option - 1);
    AllPlaylistsMenu(playlists);
  }
}

void AddPlaylist()
{
  std::cout << std::endl;
  std::cout << "Enter name of the new playlist : ";
  std::string playlistName;
  // Flush cin input buffer so that the program will wait for user input
  std::cin.ignore();
  std::getline(std::cin, playlistName);
  Playlist* newPlaylist = new Playlist();
  newPlaylist->name = playlistName;
  newPlaylist->songs = new DoublyLinkedList();
  newPlaylist->currentIndex = 0;
  SongVariables::playlists->PushBack(newPlaylist);
  std::cout << "Successfully added " << playlistName << std::endl;
}

void PlaylistMenu(Playlist* playlist)
{
  int option = -1;
  std::cout << playlist->name << std::endl;
  std::cout << "==========================" << std::endl;
  for (size_t i = 1; i <= playlist->songs->GetLength(); i++)
  {
    std::string songName = "[" + std::to_string(i) + "] " + playlist->songs->Get(i - 1)->data;
    std::cout << songName << std::endl;
  }
  std::cout << "[0] Main Menu" << std::endl;
  std::cout << "Select option: ";
  std::cin >> option;
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
    if (directory[i - 1]->isDirectory)
    {
      musicName += " (Directory)";
    }
    else
    {
      musicName += " (File)";
    }
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
  std::cout << "[2] Add to Playlist" << std::endl;
  std::cout << "[0] Song Library" << std::endl;
  std::cout << "Select Option:";
  std::cin >> option;

  switch (option)
  {
    case 0:
      SongLibraryMenu(GetRootMusicDirectory());
      break;
    case 1:
      songQueue.AddEnd(musicPath);
      PlaySound(constTcharMusicPath, NULL,
                SND_FILENAME | SND_ASYNC);  // To play the corresponding song
      PlayingSongMenu(songQueue);
      break;
    case 2:
      AddSongToPlaylist(musicFile);
      break;
    default:
      std::cout << "Invalid input, please try again." << std::endl;
      SongMenu(musicFile);
  }
}

void AddSongToPlaylist(TreeNode* musicFile)
{
  int playlistOption = -1;
  Vector<Playlist*>* playlists = SongVariables::playlists;

  if (playlists->Size() == 0)
  {
    std::cout << "\nNo playlists available" << std::endl;
  }
  else
  {
    std::cout << "Playlists available:" << std::endl;
  }
  std::cout << "[0] Songs Menu" << std::endl;
  std::cout << "[1] Add playlist" << std::endl;
  for (size_t i = 2; i <= (playlists->Size() + 1); i++)
  {
    std::string playlistName = "[" + std::to_string(i) + "] " + playlists->operator[](i - 2)->name;
    std::cout << playlistName << std::endl;
  }
  std::cout << "Select option: ";
  std::cin >> playlistOption;

  if (playlistOption == 0)
  {
    SongMenu(musicFile);
  }
  if (playlistOption == 1)
  {
    std::cout << std::endl;
    AddPlaylist();
    std::string musicFileString = musicFile->path.u8string();
    playlists->operator[](playlistOption - 2)->songs->AddEnd(musicFileString);
    std::cout << musicFile->path.filename().u8string() << " successfully added into "
              << playlists->operator[](playlistOption - 2)->name << std::endl;
    SongMenu(musicFile);
  }
  else if (playlistOption < 0 || playlistOption > playlists->Size() + 1)
  {
    std::cout << "Invaild input, please try again." << std::endl;
    AddSongToPlaylist(musicFile);
  }
  else
  {
    std::string musicFileString = musicFile->path.u8string();
    playlists->operator[](playlistOption - 2)->songs->AddEnd(musicFileString);
    std::cout << musicFile->path.filename().u8string() << " successfully added into "
              << playlists->operator[](playlistOption - 2)->name << std::endl;
    SongMenu(musicFile);
  }
}

void PlayingSongMenu(DoublyLinkedList songQueue)
{
  int option = -1;
  static int currentSongIndex = 0;
  // Convert music path to const TCHAR* for use in PlaySound()
  std::string musicPath = songQueue.GetCurrent()->data;
  std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
  const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();

  std::cout << "[0] Stop and Exit" << std::endl;
  std::cout << "[1] Replay" << std::endl;
  std::cout << "[2] Next" << std::endl;
  std::cout << "[3] Previous" << std::endl;
  std::cout << "Select Option:";
  std::cin >> option;

  switch (option)
  {
    case 0:
      // Stop playing song
      PlaySound(NULL, 0, 0);
      SongLibraryMenu(GetRootMusicDirectory());
      break;  //
    case 1:   //
    {
      // Stop playing song
      PlaySound(NULL, 0, 0);
      PlaySound(constTcharMusicPath, 0, SND_FILENAME | SND_ASYNC);
      PlayingSongMenu(songQueue);
      break;
    }
    case 2:
    {
      PlaySound(NULL, 0, 0);
      songQueue.Forward();
      std::string musicPath = songQueue.GetCurrent()->data;
      std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
      const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();
      PlaySound(constTcharMusicPath, 0, SND_FILENAME | SND_ASYNC);
      PlayingSongMenu(songQueue);
      break;
    }
    case 3:
    {
      PlaySound(NULL, 0, 0);
      songQueue.Backward();
      std::string musicPath = songQueue.GetCurrent()->data;
      std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
      const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();
      PlaySound(constTcharMusicPath, 0, SND_FILENAME | SND_ASYNC);
      PlayingSongMenu(songQueue);
      break;
    }
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
