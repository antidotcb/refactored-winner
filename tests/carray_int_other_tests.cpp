// Copyright 2018 (с) The Creep Brothers. All rights reserved.
// Created by antidotcb on 26-Aug-18.
//

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "./carray_tests.h"

namespace g5_task
{
namespace test
{
namespace
{
constexpr std::size_t ObjectsAmount = 20;

struct POD
{
  unsigned long long int value;
};

std::ostream& operator<<(std::ostream& _out, const POD& _object)
{
  _out << _object.value;
  return _out;
}

bool operator==(const POD& rhs, const POD& lhs) noexcept
{
  return rhs.value == lhs.value;
}

bool operator<(const POD& rhs, const POD& lhs) noexcept
{
  return rhs.value < lhs.value;
}

bool operator<=(const POD& rhs, const POD& lhs) noexcept
{
  return rhs.value <= lhs.value;
}

bool operator==(const std::size_t rhs, const POD& lhs) noexcept
{
  return rhs == lhs.value;
}

}  // namespace

class TestsWithAnotherNumbers : public CArrayTestBase
{
protected:
  void SetUp() override
  {
    Test::SetUp();
  }

  void TearDown() override
  {
    Test::TearDown();
  }
};

TEST_F(TestsWithAnotherNumbers, basic_ctor_test)
{
  {
    ASSERT_NO_FATAL_FAILURE({ CArray<POD> testArray{}; });
  }
}

TEST_F(TestsWithAnotherNumbers, test_add_single)
{
  {
    CArray<POD> testArray{};

    testArray.push_back({testArray.size()});
    ASSERT_EQ(1, testArray.size());
    ASSERT_EQ(1, testArray.capacity());
    EXPECT_EQ(1, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back({testArray.size()});
    ASSERT_EQ(2, testArray.size());
    ASSERT_EQ(2, testArray.capacity());
    EXPECT_EQ(2, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back({testArray.size()});
    ASSERT_EQ(3, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    EXPECT_EQ(3, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back({testArray.size()});
    ASSERT_EQ(4, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    EXPECT_EQ(4, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back({testArray.size()});
    ASSERT_EQ(5, testArray.size());
    ASSERT_EQ(8, testArray.capacity());
    EXPECT_EQ(5, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back({testArray.size()});
    ASSERT_EQ(6, testArray.size());
    ASSERT_EQ(8, testArray.capacity());
    EXPECT_EQ(6, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    for (auto i = 0u; i < testArray.size(); ++i)
    {
      EXPECT_EQ(i, testArray[i]);
    }
  }
}

TEST_F(TestsWithAnotherNumbers, test_add_single_cref)
{
  {
    const auto object1(0);
    const auto object2(1);
    const auto object3(2);
    const auto object4(3);
    const auto object5(4);
    const auto object6(5);

    {
      CArray<POD> testArray{};
      testArray.push_back({object1});
      ASSERT_EQ(1, testArray.size());
      ASSERT_EQ(1, testArray.capacity());
      EXPECT_EQ(1, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back({object2});
      ASSERT_EQ(2, testArray.size());
      ASSERT_EQ(2, testArray.capacity());
      EXPECT_EQ(2, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back({object3});
      ASSERT_EQ(3, testArray.size());
      ASSERT_EQ(4, testArray.capacity());
      EXPECT_EQ(3, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back({object4});
      ASSERT_EQ(4, testArray.size());
      ASSERT_EQ(4, testArray.capacity());
      EXPECT_EQ(4, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back({object5});
      ASSERT_EQ(5, testArray.size());
      ASSERT_EQ(8, testArray.capacity());
      EXPECT_EQ(5, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back({object6});
      ASSERT_EQ(6, testArray.size());
      ASSERT_EQ(8, testArray.capacity());
      EXPECT_EQ(6, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      for (auto i = 0u; i < testArray.size(); ++i)
      {
        EXPECT_EQ(i, testArray[i]);
      }
    }

    EXPECT_NE(object1, object2);
    EXPECT_NE(object3, object4);
    EXPECT_NE(object5, object6);
  }

}  // namespace test

TEST_F(TestsWithAnotherNumbers, test_add)
{
  {
    std::size_t randomNumbers[ObjectsAmount];
    std::generate_n(randomNumbers, ObjectsAmount, [this]() { return this->get_random_number(); });

    CArray<POD> testArray{};
    const std::size_t ExpectedCapacity[ObjectsAmount]
      = {1, 2, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 32, 32};

    std::size_t n = 0;
    for (const auto& randomNumber : randomNumbers)
    {
      testArray.push_back({randomNumber});
      EXPECT_EQ(ExpectedCapacity[n++], testArray.capacity());
    }

    this->print(testArray);
    ASSERT_EQ(ObjectsAmount, testArray.size());

    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      EXPECT_EQ(randomNumbers[i], testArray[i]) << "i=" << i;
    }
  }
}

TEST_F(TestsWithAnotherNumbers, test_sort)
{
  {
    CArray<POD> testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = static_cast<size_t>(this->get_random_number());
      testArray.push_back({randomNumber});
    }
    this->print(testArray);
    std::sort(testArray.begin(), testArray.end());
    this->print(testArray);

    for (auto i = 0u; i < ObjectsAmount - 1; ++i)
    {
      ASSERT_LE(testArray[i], testArray[i + 1]);
    }
  }
}

TEST_F(TestsWithAnotherNumbers, test_erase_simple)
{
  {
    CArray<POD> testArray{};

    testArray.push_back({1});
    ASSERT_EQ(1, testArray.size());
    ASSERT_EQ(1, testArray.capacity());
    testArray.push_back({2});
    ASSERT_EQ(2, testArray.size());
    ASSERT_EQ(2, testArray.capacity());
    testArray.push_back({3});
    ASSERT_EQ(3, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    testArray.push_back({4});
    ASSERT_EQ(4, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    testArray.push_back({5});
    ASSERT_EQ(5, testArray.size());
    ASSERT_EQ(8, testArray.capacity());

    this->print(testArray);

    testArray.erase(testArray.begin() + 4);
    this->print(testArray);
    ASSERT_EQ(8, testArray.capacity());
    ASSERT_EQ(4, testArray.size());
    ASSERT_EQ(4, std::distance(testArray.begin(), testArray.end()));

    EXPECT_EQ(1, testArray[0]);
    EXPECT_EQ(2, testArray[1]);
    EXPECT_EQ(3, testArray[2]);
    EXPECT_EQ(4, testArray[3]);

    testArray.erase(testArray.begin() + 2);
    this->print(testArray);
    ASSERT_EQ(8, testArray.capacity());
    ASSERT_EQ(3, testArray.size());
    ASSERT_EQ(3, std::distance(testArray.begin(), testArray.end()));

    EXPECT_EQ(1, testArray[0]);
    EXPECT_EQ(2, testArray[1]);
    EXPECT_EQ(4, testArray[2]);

    testArray.erase(testArray.begin() + 0);
    this->print(testArray);
    ASSERT_EQ(8, testArray.capacity());
    ASSERT_EQ(2, testArray.size());
    ASSERT_EQ(2, std::distance(testArray.begin(), testArray.end()));

    EXPECT_EQ(2, testArray[0]);
    EXPECT_EQ(4, testArray[1]);
  }
}

TEST_F(TestsWithAnotherNumbers, test_erase)
{
  {
    CArray<POD> originalArray{};
    CArray<POD> testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = static_cast<size_t>(this->get_random_number());
      originalArray.push_back({randomNumber});
      testArray.push_back({randomNumber});
    }

    this->print(testArray);
    for (auto position = testArray.size() - 1u; position > 0; --position)
    {
      if (position % 2)
      {
        testArray.erase(testArray.begin() + position);
      }
    }
    this->print(testArray);
    ASSERT_EQ(testArray.size(), ObjectsAmount / 2u + ObjectsAmount % 2u);

    for (auto i = 0u; i < ObjectsAmount / 2u; ++i)
    {
      EXPECT_EQ(originalArray[i * 2u], testArray[i]);
    }
  }
}

TEST_F(TestsWithAnotherNumbers, test_insert_simple)
{
  {
    CArray<POD> testArray{};

    testArray.insert(testArray.begin() + 0, {1});
    this->print(testArray);
    ASSERT_EQ(1, testArray.capacity());
    ASSERT_EQ(1, testArray.size());

    EXPECT_EQ(1, testArray[0]);
    testArray.insert(testArray.begin() + 1, {3});
    this->print(testArray);
    ASSERT_EQ(2, testArray.capacity());
    ASSERT_EQ(2, testArray.size());

    EXPECT_EQ(1, testArray[0]);
    EXPECT_EQ(3, testArray[1]);

    testArray.insert(testArray.begin() + 1, {2});
    this->print(testArray);
    ASSERT_EQ(4, testArray.capacity());
    ASSERT_EQ(3, testArray.size());

    EXPECT_EQ(1, testArray[0]);
    EXPECT_EQ(2, testArray[1]);
    EXPECT_EQ(3, testArray[2]);

    testArray.insert(testArray.begin() + 0, {0});
    this->print(testArray);
    ASSERT_EQ(4, testArray.capacity());
    ASSERT_EQ(4, testArray.size());

    EXPECT_EQ(0, testArray[0]);
    EXPECT_EQ(1, testArray[1]);
    EXPECT_EQ(2, testArray[2]);
    EXPECT_EQ(3, testArray[3]);
  }
}

TEST_F(TestsWithAnotherNumbers, test_insert)
{
  {
    CArray<POD> testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = static_cast<size_t>(this->get_random_number());
      testArray.push_back({randomNumber});
    }

    this->print(testArray);

    constexpr std::size_t InsertionsAmount = 10;
    for (auto i = 0u; i < InsertionsAmount; ++i)
    {
      const auto randomNumber = static_cast<size_t>(this->get_random_number());
      const auto position = (i == InsertionsAmount - 1 || i == 0)
                              ? (i == 0 ? 0 : testArray.size())
                              : static_cast<std::size_t>(
                                  this->get_random_number(0u, static_cast<int>(testArray.size())));
      testArray.insert(testArray.begin() + position, {randomNumber});
      EXPECT_EQ(randomNumber, testArray[position])
        << "Insert " << randomNumber << " at " << position;
      this->print(testArray);
    }

    EXPECT_EQ(InsertionsAmount + ObjectsAmount, testArray.size());
  }
}

TEST_F(TestsWithAnotherNumbers, test_clear)
{
  {
    CArray<POD> testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = static_cast<size_t>(this->get_random_number());
      testArray.push_back({randomNumber});
    }

    EXPECT_EQ(ObjectsAmount, testArray.size());
    testArray.clear();

    EXPECT_EQ(0, testArray.size());
    EXPECT_EQ(testArray.begin(), testArray.end());
  }
}
}  // namespace test
}  // namespace g5_task
