// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends
// there.
//

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mmsystem.h>

namespace fs = std::filesystem;

int main()
{
  int option = -1;

  while (option != 0)
  {
    std::cout << "Music Player" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "[1] View songs" << std::endl;
    std::cout << "[2] Organize songs" << std::endl;
    std::cout << "[0] Exit" << std::endl;
    std::cin >> option;

    if (option == 1)
    {
      int stopMusic = 0;
      PlaySound(TEXT("../assets/piano.wav"), NULL, SND_FILENAME | SND_ASYNC);
      std::cout << "Press 1 to stop : ";
      std::cin >> stopMusic;
      if (stopMusic == 1)
      {
        PlaySound(NULL, 0, 0);
      }
    }
  }
}
