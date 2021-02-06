// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends
// there.
//

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mmsystem.h>

namespace fs = std::filesystem;

int option = -1;
int musicOption = -1;
int musicMenu = -1;

void MainMenuOption(int option);

int main()
{
  std::cout << "\nMusic Player" << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "[1] View songs" << std::endl;
  std::cout << "[2] View playlist" << std::endl;
  std::cout << "[3] Organize songs" << std::endl;
  std::cout << "[4] Search" << std::endl;
  std::cout << "[0] Exit" << std::endl;
  std::cout << "Enter option: ";
  std::cin >> option;
  MainMenuOption(option);
}

void SongMenu(int musicOption)
{
  // code to display selected music title
  std::cout << "\nDry Flower" << std::endl;  // delete this line once music title is implemented
  std::cout << "==========================" << std::endl;
  std::cout << "[1] Play Song" << std::endl;
  // Check if song is in playlist
  std::cout << "[2] Add to Playlist" << std::endl;  // If song is not in playlist
  // std::cout << "[2] Remove from Playlist" << std::endl;  // If song is in playlist
  std::cout << "[0] Music List" << std::endl;
  std::cout << "Select Option:";
  std::cin >> musicMenu;

  if (musicMenu == 1)
  {
    int stopMusic = 0;
    PlaySound(TEXT("../assets/DryFlower.wav"), NULL,
              SND_FILENAME | SND_ASYNC);  // To play the corresponding song
    std::cout << "[0] Back" << std::endl;
    std::cout << "Press 1 to stop : ";
    std::cin >> stopMusic;
    if (stopMusic == 1)
    {
      PlaySound(NULL, 0, 0);
    }
    else
    {
      MainMenuOption(option);
    }
  }
}

void MainMenuOption(int option)
{
  if (option == 1)
  {
    std::cout << "\nList of Music" << std::endl;
    std::cout << "==========================" << std::endl;
    // code to display list of music titles
    std::cout << "[1] Dry Flower" << std::endl;  // delete this line once list is implemented
    std::cout << "[0] Main Menu" << std::endl;
    std::cout << "Select Music: ";
    std::cin >> musicOption;
    SongMenu(musicOption);
  }

  if (option == 2)
  {
    std::cout << "\nPlaylist" << std::endl;
    std::cout << "==========================" << std::endl;
    // Display list of songs in playlist
    std::cout << "[0] Main Menu" << std::endl;
    std::cout << "Select Music: ";
    std::cin >> musicOption;
    SongMenu(musicOption);
  }

  else
  {
  //return 0;
  }
}