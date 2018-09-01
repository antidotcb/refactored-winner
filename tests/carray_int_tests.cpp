// Copyright 2018 (с) The Creep Brothers. All rights reserved.
// Created by antidotcb on 26-Aug-18.
//

#include <gtest/gtest.h>

#include "carray_tests.h"

namespace g5_task
{
namespace test
{
class TestsWithNumbers : public CArrayTestBase
{};

static constexpr std::size_t NumbersAmount = 20;

TEST_F(TestsWithNumbers, basic_ctor_test)
{
  CArray<int> testArray;

  EXPECT_EQ(0, testArray.size());
  EXPECT_EQ(0, testArray.capacity());
  EXPECT_EQ(nullptr, testArray.begin());
  EXPECT_EQ(nullptr, testArray.end());
}

TEST_F(TestsWithNumbers, copy_ctor_test)
{
  constexpr auto SIZE = 6;

  CArray<int> sourceArray;
  for (auto i = 0u; i < SIZE; ++i)
  {
    sourceArray.push_back(i);
  }
  ASSERT_EQ(SIZE, sourceArray.size());

  const CArray<int> copied(sourceArray);

  ASSERT_EQ(SIZE, copied.size());
  ASSERT_EQ(SIZE, copied.capacity());

  for (auto i = 0u; i < SIZE; ++i)
  {
    ASSERT_EQ(i, copied[i]);
  }
}

TEST_F(TestsWithNumbers, move_ctor_test)
{
  constexpr auto SIZE = 6;

  CArray<int> sourceArray;
  for (auto i = 0u; i < SIZE; ++i)
  {
    sourceArray.push_back(i);
  }
  ASSERT_EQ(SIZE, sourceArray.size());

  const auto capacity = sourceArray.capacity();
  const auto* begin = sourceArray.begin();
  const auto* end = sourceArray.end();

  const CArray<int> moved(std::move(sourceArray));

  ASSERT_EQ(SIZE, moved.size());
  ASSERT_EQ(capacity, moved.capacity());
  ASSERT_EQ(begin, moved.begin());
  ASSERT_EQ(end, moved.end());

  for (auto i = 0u; i < SIZE; ++i)
  {
    ASSERT_EQ(i, moved[i]);
  }
}

TEST_F(TestsWithNumbers, test_add)
{
  constexpr auto SIZE = 6;

  int randomNumbers[SIZE];
  std::generate_n(randomNumbers, SIZE, [this]() { return get_random_number(); });

  CArray<int> testArray{};
  for (const int& randomNumber : randomNumbers)
  {
    testArray.push_back(randomNumber);
  }

  print(testArray);
  ASSERT_EQ(SIZE, testArray.size());

  for (auto i = 0u; i < SIZE; ++i)
  {
    EXPECT_EQ(randomNumbers[i], testArray[i]) << "i=" << i;
  }
}

TEST_F(TestsWithNumbers, test_sort)
{
  CArray<int> testArray{};
  for (auto i = 0u; i < NumbersAmount; ++i)
  {
    const auto randomNumber = get_random_number();
    testArray.push_back(randomNumber);
  }
  print(testArray);
  std::sort(testArray.begin(), testArray.end());
  print(testArray);

  for (auto i = 0u; i < NumbersAmount - 1; ++i)
  {
    ASSERT_LE(testArray[i], testArray[i + 1]);
  }
}

TEST_F(TestsWithNumbers, test_erase)
{
  CArray<int> originalArray{};
  CArray<int> testArray{};
  for (auto i = 0u; i < NumbersAmount; ++i)
  {
    const auto randomNumber = get_random_number();
    originalArray.push_back(randomNumber);
    testArray.push_back(randomNumber);
  }

  print(testArray);
  for (auto i = testArray.size() - 1u; i > 0; --i)
  {
    if (i % 2)
    {
      testArray.erase(i);
    }
  }
  print(testArray);
  ASSERT_EQ(testArray.size(), NumbersAmount / 2u + NumbersAmount % 2u);

  for (auto i = 0u; i < NumbersAmount / 2u; ++i)
  {
    ASSERT_EQ(originalArray[i * 2u], testArray[i]);
  }
}

TEST_F(TestsWithNumbers, test_insert)
{
  CArray<int> testArray{};
  for (auto i = 0u; i < NumbersAmount; ++i)
  {
    const auto randomNumber = get_random_number();
    testArray.push_back(randomNumber);
  }

  print(testArray);

  constexpr std::size_t InsertionsAmount = 10;
  for (auto i = 0u; i < InsertionsAmount; ++i)
  {
    const int randomNumber = get_random_number();
    const auto position
      = (i == InsertionsAmount - 1 || i == 0)
          ? (i == 0 ? 0 : testArray.size())
          : static_cast<std::size_t>(get_random_number(0u, static_cast<int>(testArray.size())));
    testArray.insert(position, randomNumber);
    ASSERT_EQ(randomNumber, testArray[position]) << "Insert " << randomNumber << " at " << position;
    print(testArray);
  }

  ASSERT_EQ(InsertionsAmount + NumbersAmount, testArray.size());
}

TEST_F(TestsWithNumbers, test_clear)
{
  CArray<int> testArray{};
  for (auto i = 0u; i < NumbersAmount; ++i)
  {
    const auto randomNumber = get_random_number();
    testArray.push_back(randomNumber);
  }

  EXPECT_EQ(NumbersAmount, testArray.size());
  testArray.clear();

  EXPECT_EQ(0, testArray.size());
  EXPECT_EQ(testArray.begin(), testArray.end());
  EXPECT_EQ(testArray.begin(), nullptr);
}
}  // namespace test
}  // namespace g5_task
