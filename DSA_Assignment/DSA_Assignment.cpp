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
#include "NaiveSearch.h"

namespace fs = std::filesystem;

// Function prototypes
void MainMenu();
void SongMenu(TreeNode* musicFile);
void SongLibraryMenu(Vector<TreeNode*> directory);
void PlayingSongMenu(DoublyLinkedList* songQueue);
void AllPlaylistsMenu(Vector<Playlist*>* playlists);
void PlaylistMenu(Playlist* playlist);
Vector<TreeNode*> GetRootMusicDirectory();
void AddSongToPlaylist(TreeNode* musicFile);
void AddPlaylist();
void RemovePlaylist();
TreeNode* SearchSong(Vector<TreeNode*> directory, std::string input);
Playlist* SearchPlaylist(Vector<Playlist*>* playlists, std::string input);
void RemoveSongFromPlaylist(Playlist* playlist);

namespace SongVariables
{
Vector<Playlist*>* playlists = new Vector<Playlist*>;
}

// Feature for Main Menu of Tunes Player
void MainMenu()
{
  int option = -1;
  Vector<TreeNode*> rootMusicDirectory = GetRootMusicDirectory();

  while (option != 0)
  {
    // options for main menu
    std::cout << std::endl;
    std::cout << "Tunes Player" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "[1] View song library" << std::endl;
    std::cout << "[2] View playlists" << std::endl;
    std::cout << "[0] Exit" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> option;
    switch (option)
    {
      case 0:
        return;  // End Program
      case 1:
        SongLibraryMenu(rootMusicDirectory);  // Leads to View Song Library Feature
        return;
      case 2:
        AllPlaylistsMenu(SongVariables::playlists);  // Leads to View All Playlist Feature
        return;
      // Invalid options check
      default:
        std::cout << "Invalid input, please try again" << std::endl;
        break;
    }
  }
}

// The View All Playlist Feature
void AllPlaylistsMenu(Vector<Playlist*>* playlists)
{
  int option = -1;
  std::cout << std::endl;
  std::cout << "Playlists" << std::endl;
  std::cout << "==========================" << std::endl;
  // Checks if there are any existing playlists
  if (playlists->Size() == 0)
  {
    std::cout << "No playlists available" << std::endl;
  }
  std::cout << "[0] Main Menu" << std::endl;
  std::cout << "[1] Search Playlist" << std::endl;

  // Display the names of the playlists
  for (size_t i = 2; i <= playlists->Size() + 1; i++)
  {
    std::string playlistName = "[" + std::to_string(i) + "] " + playlists->operator[](i - 2)->name;
    std::cout << playlistName << std::endl;
  }

  std::cout << "[" + std::to_string(playlists->Size() + 2) + "] Create Playlist" << std::endl;
  std::cout << "[" + std::to_string(playlists->Size() + 3) + "] Delete Playlist" << std::endl;
  std::cout << "Enter option : ";
  std::cin >> option;

  // If user wants to exit
  if (option == 0)
  {
    MainMenu();
    return;
  }

  if (option == 1)
  {
    std::string playlistName;
    std::cout << std::endl;
    std::cout << "Enter Playlist Name : ";
    std::cin >> playlistName;
    Playlist* playlist = SearchPlaylist(playlists, playlistName);
    if (playlist != NULL)
    {
      PlaylistMenu(playlist);
      return;
    }
    else
    {
      std::cout << "Playlist not found" << std::endl;
      AllPlaylistsMenu(playlists);
      return;
    }
  }

  // If user selects a playlist
  if (option <= playlists->Size() + 1)
  {
    PlaylistMenu(playlists->operator[](option - 2));
    return;
  }

  // Create a new playlist
  if (option == (playlists->Size() + 2))
  {
    AddPlaylist();
    AllPlaylistsMenu(SongVariables::playlists);
    return;
  }

  // Remove an existing playlist
  if (option == (playlists->Size() + 3))
  {
    RemovePlaylist();
    return;
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
    return;
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

  if (option == 0)
  {
    AllPlaylistsMenu(playlists);
    return;
  }
  if (option <= playlists->Size())
  {
    std::cout << "Removing " << playlists->operator[](option - 1)->name << std::endl;
    playlists->RemoveAt(option - 1);
    AllPlaylistsMenu(playlists);
    return;
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

// The View Single Playlist Feature
void PlaylistMenu(Playlist* playlist)
{
  int option = -1;
  std::cout << std::endl;
  std::cout << playlist->name << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "[0] Main Menu" << std::endl;
  std::cout << "[1] Remove song" << std::endl;
  // To display the names of songs added into the playlist
  for (size_t i = 2; i <= playlist->songs->GetLength() + 1; i++)
  {
    std::string songName =
        "[" + std::to_string(i) + "] " + playlist->songs->Get(i - 2)->data.filename().u8string();
    std::cout << songName << std::endl;
  }
  // If no songs are added into the playlist yet
  if (playlist->songs->GetLength() < 1)
  {
    std::cout << "No songs added yet, add some songs!" << std::endl;
  }
  std::cout << "Select option: ";
  std::cin >> option;

  if (option == 0)
  {
    MainMenu();  // Leads to MainMenu feature
    return;
  }
  if (option == 1)
  {
    RemoveSongFromPlaylist(playlist);  // Leads to remove song from playlist feature
    return;
  }
  // Checks if invalid option has been entered
  if (option < 0 || option > playlist->songs->GetLength() + 1)
  {
    std::cout << "Invaild option selected, please try again." << std::endl;
    PlaylistMenu(playlist);
    return;
  }
  // Plays song for selected music and lead to playing song menu feature
  else
  {
    std::string musicPath = playlist->songs->GetCurrent()->data.u8string();
    std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
    const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();
    PlaySound(constTcharMusicPath, 0, SND_FILENAME | SND_ASYNC);  // plays selected song
    PlayingSongMenu(playlist->songs);                             // leads to playing song feature
    return;
  }
}

void SongLibraryMenu(Vector<TreeNode*> directory)
{
  int option = -1;
  std::cout << std::endl;
  std::cout << "Song Library" << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "[0] Main Menu" << std::endl;
  std::cout << "[1] Search Song" << std::endl;
  // for every file in the /music folder
  for (size_t i = 2; i <= directory.Size() + 1; i++)
  {
    std::string musicName = "[" + std::to_string(i) + "] ";
    // Get filename of current file and append it into musicName
    musicName += directory[i - 2]->path.filename().u8string();
    if (directory[i - 2]->isDirectory)
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
    MainMenu();
    return;
  }

  if (option == 1)
  {
    std::string songName;
    std::cout << std::endl;
    std::cout << "Enter Song Name : ";
    std::cin >> songName;
    TreeNode* song = SearchSong(directory, songName);
    if (song != NULL)
    {
      SongMenu(song);
      return;
    }
    else
    {
      std::cout << "Song not found" << std::endl;
      SongLibraryMenu(directory);
      return;
    }
  }
  if (option < 0 || option > directory.Size() + 1)
  {
    std::cout << "Invalid input, please try again";
    SongLibraryMenu(directory);
    return;
  }
  if (directory[option - 2]->isDirectory)
  {
    SongLibraryMenu(directory[option - 2]->children);
    return;
  }
  else
  {
    SongMenu(directory[option - 2]);
    return;
  }
}

TreeNode* SearchSong(Vector<TreeNode*> directory, std::string input)
{
  for (size_t i = 0; i < directory.Size(); i++)
  {
    if (directory[i]->isDirectory)
    {
      SearchSong(directory[i]->children, input);
    }
    else
    {
      if (NaiveSearch(input, directory[i]->path.filename().stem().u8string()))
      {
        return directory[i];
      }
    }
  }

  return NULL;
}

Playlist* SearchPlaylist(Vector<Playlist*>* playlists, std::string input)
{
  for (size_t i = 0; i < playlists->Size(); i++)
  {
    if (NaiveSearch(input, playlists->operator[](i)->name))
    {
      return playlists->operator[](i);
    }
  }
  return NULL;
}

void SongMenu(TreeNode* musicFile)
{
  int option = -1;
  DoublyLinkedList* songQueue = new DoublyLinkedList();
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
      return;
    case 1:
      songQueue->AddEnd(musicPath);
      PlaySound(constTcharMusicPath, NULL,
                SND_FILENAME | SND_ASYNC);  // To play the corresponding song
      PlayingSongMenu(songQueue);
      return;
    case 2:
      if (SongVariables::playlists->Size() <= 0)
      {
        std::cout << "No playlist found, please create a new playlist" << std::endl;
        AddPlaylist();
        SongMenu(musicFile);
        return;
      }
      else
      {
        AddSongToPlaylist(musicFile);
        return;
      }
      break;
    default:
      std::cout << "Invalid input, please try again." << std::endl;
      SongMenu(musicFile);
      return;
  }
}

// The remove song from playlist feature
void RemoveSongFromPlaylist(Playlist* playlist)
{
  int option = -1;
  std::cout << std::endl;
  std::cout << "Remove Song" << std::endl;
  std::cout << "==========================" << std::endl;
  playlist->songs->Print();  // Displays all songs in playlist
  // If no songs has been added into the playlist
  if (playlist->songs->GetLength() - 1 < 0)
  {
    std::cout << "No songs in this playlist to remove!" << std::endl;
  }
  std::cout << "[0] Playlist Menu" << std::endl;
  std::cout << "Select option: ";
  std::cin >> option;
  if (option == 0)
  {
    PlaylistMenu(playlist);  // Leads to the playlist menu
    return;
  }
  // If invalid option has been entered
  if (option < 0 || option > playlist->songs->GetLength())
  {
    std::cout << "Invalid option, please try again." << std::endl;
    RemoveSongFromPlaylist(playlist);
    return;
  }
  // Function to remove song from playlist
  else
  {
    std::cout << playlist->songs->Get(option - 1)->data.filename().u8string()
              << " has been removed from " << playlist->name << std::endl;
    playlist->songs->DeleteItem(option - 1);  // Remove song from playlist
    return;
  }
  PlaylistMenu(playlist);
  return;
}

// The add song to playlist feature
void AddSongToPlaylist(TreeNode* musicFile)
{
  std::cout << std::endl;
  int playlistOption = -1;
  Vector<Playlist*>* playlists = SongVariables::playlists;

  // checks if there are any playlist availble
  if (playlists->Size() == 0)  // no playlist available
  {
    std::cout << std::endl;
    std::cout << "No playlists available" << std::endl;
  }
  else  // existing playlists availble
  {
    std::cout << "Playlists" << std::endl;
    std::cout << "==========================" << std::endl;
  }
  std::cout << "[0] Songs Menu" << std::endl;
  std::cout << "[1] Add playlist" << std::endl;
  // print out playlist names
  for (size_t i = 2; i <= (playlists->Size() + 1); i++)
  {
    std::string playlistName = "[" + std::to_string(i) + "] " + playlists->operator[](i - 2)->name;
    std::cout << playlistName << std::endl;
  }
  std::cout << "Select option: ";
  std::cin >> playlistOption;

  if (playlistOption == 0)
  {
    SongMenu(musicFile);  // Leads to song menu feature
    return;
  }
  if (playlistOption == 1)
  {
    std::cout << std::endl;
    fs::path musicFileString = musicFile->path.u8string();
    playlists->operator[](playlistOption - 2)
        ->songs->AddEnd(musicFileString);  // add song into the end of the playlist
    std::cout << musicFile->path.filename().u8string() << " successfully added into "
              << playlists->operator[](playlistOption - 2)->name << std::endl;
    SongMenu(musicFile);
    return;
  }
  // Checks if there are invalid inputs
  else if (playlistOption < 0 || playlistOption > playlists->Size() + 1)
  {
    std::cout << "Invaild input, please try again." << std::endl;
    AddSongToPlaylist(musicFile);
    return;
  }
  else
  {
    std::string musicFileString = musicFile->path.u8string();
    playlists->operator[](playlistOption - 2)
        ->songs->AddEnd(musicFileString);  // add song into the end of the playlist
    std::cout << musicFile->path.filename().u8string() << " successfully added into "
              << playlists->operator[](playlistOption - 2)->name << std::endl;
    SongMenu(musicFile);
    return;
  }
}

void PlayingSongMenu(DoublyLinkedList* songQueue)
{
  int option = -1;
  static int currentSongIndex = 0;
  // Convert music path to const TCHAR* for use in PlaySound()
  std::string musicPath = songQueue->GetCurrent()->data.u8string();
  std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
  const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();

  std::cout << std::endl;
  std::cout << songQueue->GetCurrent()->data.filename().u8string() << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "[0] Stop and Exit" << std::endl;
  std::cout << "[1] Replay" << std::endl;
  // If there are more that 1 song in playlist
  if (songQueue->GetLength() > 1)
  {
    std::cout << "[2] Next" << std::endl;      // Triggers the traverseFoward operation
    std::cout << "[3] Previous" << std::endl;  // Triggers the traversBackward operation
  }
  std::cout << "Select Option:";
  std::cin >> option;

  if (songQueue->GetLength() > 1)  // Checks for invalid inputs for multiple songs in playlist
  {
    if (option < 0 || option > 3)
    {
      std::cout << "Invalid input, please try again" << std::endl;
      PlayingSongMenu(songQueue);
      return;
    }
  }
  else
  {
    if (option < 0 || option > 1)  // Checks for invalid inputs for only 1 song in playlist
    {
      std::cout << "Invalid input, please try again" << std::endl;
      PlayingSongMenu(songQueue);
      return;
    }
  }
  if (option == 0)
  {
    // Stop playing song
    PlaySound(NULL, 0, 0);
    SongLibraryMenu(GetRootMusicDirectory());
    return;
  }
  if (option == 1)
  {
    // Stop playing song
    PlaySound(NULL, 0, 0);
    // Replay song
    PlaySound(constTcharMusicPath, 0, SND_FILENAME | SND_ASYNC);
    PlayingSongMenu(songQueue);
    return;
  }
  if (songQueue->GetLength() > 1)
  {
    if (option == 2)
    {
      // Play next song in queue
      PlaySound(NULL, 0, 0);
      songQueue->Forward();
      std::string musicPath = songQueue->GetCurrent()->data.u8string();
      std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
      const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();
      PlaySound(constTcharMusicPath, 0, SND_FILENAME | SND_ASYNC);  // Plays the song
      PlayingSongMenu(songQueue);
      return;
    }
    if (option == 3)
    {
      // Play previous song in queue
      PlaySound(NULL, 0, 0);
      songQueue->Backward();
      std::string musicPath = songQueue->GetCurrent()->data.u8string();
      std::basic_string<TCHAR> tcharMusicPath(musicPath.begin(), musicPath.end());
      const TCHAR* constTcharMusicPath = tcharMusicPath.c_str();
      PlaySound(constTcharMusicPath, 0, SND_FILENAME | SND_ASYNC);  // Plays the song
      PlayingSongMenu(songQueue);
      return;
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
