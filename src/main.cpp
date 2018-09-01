// Copyright 2018 (с) antidotcb. All rights reserved.
// Created by Danylo Bilyk on 09/01/18.
//

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

#include "CArray.h"

using namespace g5_task;

namespace
{
template <typename T>
std::ostream& operator<<(
  std::ostream& _out,
  const CArray<T>& _array
  )
{
  std::stringstream ss;
  ss << "[ ";
  const auto* last = _array.end() - 1;
  for (const auto& element : _array)
  {
    if (&element != last)
    {
      ss << std::setw(2) << element << ", ";
    }
    else
    {
      ss << element;
    }
  }
  ss << " ]";
  return _out << ss.str();
}
}  // namespace

int main()
{
  const auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
  std::default_random_engine generator(seed);

  const auto random = [&generator](const int _max)
  {
    assert(_max > 0);
    std::uniform_int_distribution<int> distribution(0, _max);
    return distribution(generator);
  };

  const auto randomWord = [random]()
  {
    const auto wordLength = random(5) + 2;  // max word length - 6
    std::string word(wordLength, 0);
    std::generate_n(word.begin(), wordLength, [random]() {
      constexpr auto FirstLetter = 'a';
      constexpr auto LastLetter = 'z';
      constexpr auto LettersRange = LastLetter - FirstLetter;
      return static_cast<char>(FirstLetter + random(LettersRange));
    });
    return word;
  };

  CArray<int> intArray;

  constexpr auto NumbersCount = 20U;
  constexpr auto RandomNumberRange = 100;
  for (auto i = 0u; i < NumbersCount; ++i)
  {
    intArray.push_back(random(RandomNumberRange));
  }
  std::cout << intArray << std::endl;

  std::sort(intArray.begin(), intArray.end());
  std::cout << intArray << std::endl;

  for (auto i = intArray.size() - 1U; i > 0; --i)
  {
    if (i % 2)
    {
      intArray.erase(i);
    }
  }
  std::cout << intArray << std::endl;

  constexpr auto InsertsCount = 10U;
  for (auto i = 0U; i < InsertsCount; ++i)
  {
    const auto pos = static_cast<unsigned int>(random(intArray.size()));
    intArray.insert(pos, random(RandomNumberRange));
  }
  std::cout << intArray << std::endl;

  intArray.clear();
  std::cout << intArray << std::endl;

  CArray<std::string> strArray;

  constexpr auto WordsCount = 15U;
  for (auto i = 0u; i < WordsCount; ++i)
  {
    auto word = randomWord();
    strArray.push_back(word);
  }
  std::cout << strArray << std::endl;

  std::sort(strArray.begin(), strArray.end());
  std::cout << strArray << std::endl;

  constexpr const auto* CharsToExpel = "abcde";
  for (auto i = 0u; i < strArray.size();)
  {
    const auto& str = strArray[i];
    if (std::string::npos != str.find_first_of(CharsToExpel))
    {
      strArray.erase(i);
      continue;
    }
    ++i;
  }
  std::cout << strArray << std::endl;

  constexpr auto WordsInsertsCount = 3U;
  for (auto i = 0U; i < WordsInsertsCount; ++i)
  {
    const auto pos = static_cast<unsigned int>(random(strArray.size()));
    strArray.insert(pos, randomWord());
  }
  std::cout << strArray << std::endl;

}
