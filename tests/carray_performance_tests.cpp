// Copyright 2018 (с) The Creep Brothers. All rights reserved.
// Created by antidotcb on 09/01/18.
//

#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>

#include "./carray_tests.h"

namespace g5_task
{
namespace test
{
namespace
{
constexpr auto Iterations = 10U;
constexpr auto Size = 1000U;

using Object = helpers::Object;
using Clock = std::chrono::steady_clock;

template <typename T>
T generate_value()
{
  return T{};
}

std::default_random_engine generator{};

int get_random_number(const int _min = 0, const int _max = 1000000U)
{
  const auto min = std::min(_min, _max);
  const auto max = std::max(_min, _max);
  std::uniform_int_distribution<int> distribution(min, max);
  const auto result = distribution(generator);
  return result;
}

template <>
int generate_value<int>()
{
  return get_random_number();
}

template <>
Object generate_value<Object>()
{
  return Object{get_random_number()};
}

char get_random_char()
{
  return static_cast<char>(get_random_number('a', 'z'));
}

std::string get_random_word()
{
  static constexpr auto MinimumWordLength = 3;
  static constexpr auto MaximumWordLength = 1000;
  const auto length = get_random_number(MinimumWordLength, MaximumWordLength);
  std::string result(length, 0);
  std::generate_n(result.begin(), length, []() { return get_random_char(); });
  return result;
}

template <>
std::string generate_value<std::string>()
{
  return get_random_word();
}

}  // namespace

template <typename TypeParam>
class TestsWithPerformance : public CArrayTestBase
{
protected:
  using value_type = typename TypeParam::value_type;

  void SetUp() override
  {
    for (auto i = 0U; i < Size; ++i)
    {
      auto value = generate_value<value_type>();
      m_testArray.push_back(value);
    }
    Test::SetUp();
    start_clock();
  }

  void TearDown() override
  {
    stop_clock();
    print_results();
    Test::TearDown();
  }

  const TypeParam& test_array() const
  {
    return m_testArray;
  }

private:
  void start_clock()
  {
    m_begin = Clock::now();
  }

  void stop_clock()
  {
    m_end = Clock::now();
  }

  void print_results() const
  {
    using namespace std::chrono;
    auto duration = duration_cast<milliseconds>(m_end - m_begin).count();
    std::cout << std::endl
              << "Test takes " << duration << " ms." << std::endl
              << "Test iteration takes " << duration / Iterations << " ms." << std::endl;
  }

  Clock::time_point m_begin{};
  Clock::time_point m_end{};
  TypeParam m_testArray{};
};

using TestTypes = ::testing::Types<
  std::vector<Object>,
  CArray<Object>,
  std::vector<int>,
  CArray<int>,
  std::vector<std::string>,
  CArray<std::string>>;

TYPED_TEST_CASE(TestsWithPerformance, TestTypes);

TYPED_TEST(TestsWithPerformance, test_copy_ctor)
{
  const auto& test = this->test_array();

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    const auto array = test;  // NOLINT(performance-unnecessary-copy-initialization)
    EXPECT_EQ(array[0], test[0]);
  }
}

TYPED_TEST(TestsWithPerformance, test_move_ctor)
{
  const auto& test = this->test_array();

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    auto array = test;
    const auto array2(std::move(array));  // NOLINT(performance-unnecessary-copy-initialization)
    EXPECT_EQ(array2[0], test[0]);
  }
}

TYPED_TEST(TestsWithPerformance, test_insert_cref)
{
  const auto& test = this->test_array();
  auto array = test;

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    for (auto k = 0U; k < Size; ++k)
    {
      const auto begin = array.begin();
      const auto testPos = get_random_number(0, test.size() - 1);
      const auto pos = get_random_number(0, array.size() - 1);
      const auto& value = test[testPos];
      array.insert(begin + pos, value);
      const auto& result = array[pos];
      EXPECT_EQ(result, value);
    }
  }
}

TYPED_TEST(TestsWithPerformance, test_insert_rvalue)
{
  const auto& test = this->test_array();
  auto array = test;

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    for (auto k = 0U; k < Size; ++k)
    {
      const auto begin = array.begin();
      const auto testPos = get_random_number(0, test.size() - 1);
      const auto pos = get_random_number(0, array.size() - 1);
      auto value = test[testPos];
      array.insert(begin + pos, std::move(value));
      const auto& result = array[pos];
      const auto& tested = test[testPos];
      EXPECT_EQ(result, tested);
    }
  }
}

TYPED_TEST(TestsWithPerformance, test_push_back_cref)
{
  const auto& test = this->test_array();
  auto array = test;

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    for (auto i = 0U; i < Size; ++i)
    {
      const auto testPos = get_random_number(0, test.size() - 1);
      const auto& value = test[testPos];
      array.push_back(value);
      const auto& result = array[array.size() - 1];
      EXPECT_EQ(result, value);
    }
  }
}

TYPED_TEST(TestsWithPerformance, test_push_back_rvalue)
{
  const auto& test = this->test_array();
  auto array = test;

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    for (auto i = 0U; i < Size; ++i)
    {
      const auto testPos = get_random_number(0, test.size() - 1);
      auto value = test[testPos];
      array.push_back(std::move(value));
      const auto& result = array[array.size() - 1];
      const auto& tested = test[testPos];
      EXPECT_EQ(result, tested);
    }
  }
}

TYPED_TEST(TestsWithPerformance, test_erase)
{
  const auto& test = this->test_array();
  auto array = test;

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    while (array.size())
    {
      const auto begin = array.begin();
      const auto size = array.size() - 1;
      const auto pos = get_random_number(0, size);
      array.erase(begin + pos);
      EXPECT_EQ(array.size(), size);
    }
  }
}

TYPED_TEST(TestsWithPerformance, test_sort)
{
  const auto& test = this->test_array();
  auto array = test;

  for (auto iteration = 0U; iteration < Iterations; ++iteration)
  {
    std::shuffle(array.begin(), array.end(), generator);
    std::sort(array.begin(), array.end());
  }
}

}  // namespace test
}  // namespace g5_task
