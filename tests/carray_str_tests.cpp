// Copyright 2018 (с) The Creep Brothers. All rights reserved.
// Created by antidotcb on 26-Aug-18.
//

#include <gtest/gtest.h>

#include "carray_tests.h"

namespace g5_task
{
namespace test
{
class TestsWithStrings : public CArrayTestBase
{
protected:
  std::string get_random_word()
  {
    static constexpr auto MinimumWordLength = 3;
    static constexpr auto MaximumWordLength = 10;
    const auto length = get_random_number(MinimumWordLength, MaximumWordLength);
    std::string result(length, 0);
    std::generate_n(result.begin(), length, [this]() { return get_random_char(); });
    return result;
  }

private:
  char get_random_char()
  {
    return static_cast<char>(get_random_number('a', 'z'));
  }
};

static constexpr std::size_t StringsAmount = 15;

TEST_F(TestsWithStrings, test_add)
{
  CArray<std::string> testArray{};
  std::string generatedStrings[StringsAmount];
  for (auto& randomWord : generatedStrings)
  {
    randomWord = get_random_word();
    testArray.push_back(randomWord);
  }

  print(testArray);

  ASSERT_EQ(StringsAmount, testArray.size());
  for (auto i = 0u; i < StringsAmount; ++i)
  {
    EXPECT_EQ(testArray[i], generatedStrings[i])
      << "i=" << i << " " << generatedStrings[i] << " " << testArray[i] << std::endl;
  }
}

TEST_F(TestsWithStrings, test_sort)
{
  CArray<std::string> testArray{};
  for (auto i = 0u; i < StringsAmount; ++i)
  {
    const auto randomWord = get_random_word();
    testArray.push_back(randomWord);
  }

  print(testArray);

  std::sort(testArray.begin(), testArray.end());

  print(testArray);

  for (auto i = 0u; i < StringsAmount - 1; ++i)
  {
    ASSERT_LE(testArray[i], testArray[i + 1]);
  }
}

TEST_F(TestsWithStrings, test_erase)
{
  CArray<std::string> testArray{};
  for (auto i = 0u; i < StringsAmount; ++i)
  {
    const auto randomWord = get_random_word();
    testArray.push_back(randomWord);
  }

  print(testArray);

  const auto charactersToExclude = "abcde";
  for (auto i = 0u; i < testArray.size();)
  {
    const auto& str = testArray[i];
    if (std::string::npos != str.find_first_of(charactersToExclude))
    {
      testArray.erase(i);
      continue;
    }
    ++i;
  }

  print(testArray);

  for (const auto& str : testArray)
  {
    EXPECT_EQ(std::string::npos, str.find_first_of(charactersToExclude));
  }
}

TEST_F(TestsWithStrings, test_insert)
{
  CArray<std::string> testArray{};
  for (auto i = 0u; i < StringsAmount; ++i)
  {
    const auto randomWord = get_random_word();
    testArray.push_back(randomWord);
  }

  static constexpr auto InsertionsAmount = 3u;
  std::string insertedStrings[InsertionsAmount];
  for (auto& insertedString : insertedStrings)
  {
    insertedString = get_random_word();
    const auto insertPosition
      = static_cast<std::size_t>(get_random_number(0, static_cast<int>(testArray.size())));
    testArray.insert(insertPosition, insertedString);
  }
}

}  // namespace test
}  // namespace g5_task
