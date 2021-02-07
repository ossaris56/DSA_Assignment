#pragma once
#include "vector/Vector.h"

/*
  Name : Chua Zhao Lin Jasper
  Team : Team 3
  Student ID : S10177296F
  Cool Features : Matches strings non-case sensitive
*/

// Naive Search algorithm to search for a pattern in a text
bool NaiveSearch(std::string pattern, std::string text)
{
  // Transform to lowercase strings
  std::transform(pattern.begin(), pattern.end(), pattern.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  std::transform(text.begin(), text.end(), text.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  size_t patternLen = pattern.size();
  size_t textLen = text.size();

  // if the pattern text to match is bigger than the compared text
  if (textLen < patternLen)
  {
    return false;
  }

  // for the positions that the pattern text is able to be slotted in
  for (size_t i = 0; i <= textLen - patternLen; i++)
  {
    int j;
    // Match every letter at an index with the compared text's letter at an index
    for (j = 0; j < patternLen; j++)
    {
      if (text[i + j] != pattern[j]) break;
    }

    // if all the letters match, return true
    if (j == patternLen) return true;
  }

  // no match
  return false;
}
