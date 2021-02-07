#pragma once
#include "vector/Vector.h"

bool NaiveSearch(std::string pattern, std::string text)
{
  std::transform(pattern.begin(), pattern.end(), pattern.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  std::transform(text.begin(), text.end(), text.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  size_t patternLen = pattern.size();
  size_t textLen = text.size();

  if (textLen < patternLen)
  {
    return false;
  }

  for (size_t i = 0; i <= textLen - patternLen; i++)
  {
    int j;
    for (j = 0; j < patternLen; j++)
    {
      if (text[i + j] != pattern[j]) break;
    }

    if (j == patternLen) return true;
  }

  return false;
}
