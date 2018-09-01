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
using Object = helpers::Object;
using Helper = helpers::Helper;

namespace
{
std::ostream& operator<<(std::ostream& _out, const Object& _object)
{
  _out << _object.data();
  return _out;
}

constexpr std::size_t ObjectsAmount = 20;

}  // namespace

template <typename T>
class TestsWithObjects : public CArrayTestBase
{
protected:
  void SetUp() override
  {
    Test::SetUp();
    Object::reset();
    Helper::reset();
  }

  void TearDown() override
  {
    Object::reset();
    Helper::reset();
    Test::TearDown();
  }
};

using testTypes = ::testing::Types<std::vector<Object>, CArray<Object>>;
TYPED_TEST_CASE(TestsWithObjects, testTypes);

TYPED_TEST(TestsWithObjects, basic_ctor_test)
{
  {
    ASSERT_NO_FATAL_FAILURE({ TypeParam testArray{}; });
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(0, Object::CtorCalls());
  EXPECT_EQ(0, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(0, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(0, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(0, Helper::CtorCalls());
  EXPECT_EQ(0, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_add_single)
{
  {
    TypeParam testArray{};

    testArray.push_back(testArray.size());
    ASSERT_EQ(1, testArray.size());
    ASSERT_EQ(1, testArray.capacity());
    EXPECT_EQ(1, Object::Instances());
    EXPECT_EQ(1, Object::CtorCalls());
    EXPECT_EQ(1, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(1, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(1, Helper::Instances());
    EXPECT_EQ(1, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());
    EXPECT_EQ(1, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back(testArray.size());
    ASSERT_EQ(2, testArray.size());
    ASSERT_EQ(2, testArray.capacity());
    EXPECT_EQ(2, Object::Instances());
    EXPECT_EQ(2, Object::CtorCalls());
    EXPECT_EQ(3, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(3, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(2, Helper::Instances());
    EXPECT_EQ(2, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());
    EXPECT_EQ(2, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back(testArray.size());
    ASSERT_EQ(3, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    EXPECT_EQ(3, Object::Instances());
    EXPECT_EQ(3, Object::CtorCalls());
    EXPECT_EQ(6, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(6, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(3, Helper::Instances());
    EXPECT_EQ(3, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());
    EXPECT_EQ(3, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back(testArray.size());
    ASSERT_EQ(4, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    EXPECT_EQ(4, Object::Instances());
    EXPECT_EQ(4, Object::CtorCalls());
    EXPECT_EQ(7, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(7, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(4, Helper::Instances());
    EXPECT_EQ(4, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());
    EXPECT_EQ(4, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back(testArray.size());
    ASSERT_EQ(5, testArray.size());
    ASSERT_EQ(8, testArray.capacity());
    EXPECT_EQ(5, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(12, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(5, Helper::Instances());
    EXPECT_EQ(5, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());
    EXPECT_EQ(5, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    testArray.push_back(testArray.size());
    ASSERT_EQ(6, testArray.size());
    ASSERT_EQ(8, testArray.capacity());
    EXPECT_EQ(6, Object::Instances());
    EXPECT_EQ(6, Object::CtorCalls());
    EXPECT_EQ(13, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(13, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(6, Helper::Instances());
    EXPECT_EQ(6, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());
    EXPECT_EQ(6, std::distance(testArray.begin(), testArray.end()));

    this->print(testArray);

    for (auto i = 0u; i < testArray.size(); ++i)
    {
      EXPECT_EQ(i, testArray[i].data());
    }
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(6, Object::CtorCalls());
  EXPECT_EQ(19, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(13, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(0, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(6, Helper::CtorCalls());
  EXPECT_EQ(6, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_add_single_cref)
{
  {
    const Object object1(0);
    const Object object2(1);
    const Object object3(2);
    const Object object4(3);
    const Object object5(4);
    const Object object6(5);

    EXPECT_EQ(6, Object::Instances());
    EXPECT_EQ(6, Object::CtorCalls());
    EXPECT_EQ(0, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(0, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(6, Helper::Instances());
    EXPECT_EQ(6, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    {
      TypeParam testArray{};
      testArray.push_back(object1);
      ASSERT_EQ(1, testArray.size());
      ASSERT_EQ(1, testArray.capacity());
      EXPECT_EQ(7, Object::Instances());
      EXPECT_EQ(6, Object::CtorCalls());
      EXPECT_EQ(0, Object::DtorCalls());
      EXPECT_EQ(1, Object::CopyCtorCalls());
      EXPECT_EQ(0, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(7, Helper::Instances());
      EXPECT_EQ(7, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());
      EXPECT_EQ(1, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back(object2);
      ASSERT_EQ(2, testArray.size());
      ASSERT_EQ(2, testArray.capacity());
      EXPECT_EQ(8, Object::Instances());
      EXPECT_EQ(6, Object::CtorCalls());
      EXPECT_EQ(1, Object::DtorCalls());
      EXPECT_EQ(2, Object::CopyCtorCalls());
      EXPECT_EQ(1, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(8, Helper::Instances());
      EXPECT_EQ(8, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());
      EXPECT_EQ(2, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back(object3);
      ASSERT_EQ(3, testArray.size());
      ASSERT_EQ(4, testArray.capacity());
      EXPECT_EQ(9, Object::Instances());
      EXPECT_EQ(6, Object::CtorCalls());
      EXPECT_EQ(3, Object::DtorCalls());
      EXPECT_EQ(3, Object::CopyCtorCalls());
      EXPECT_EQ(3, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(9, Helper::Instances());
      EXPECT_EQ(9, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());
      EXPECT_EQ(3, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back(object4);
      ASSERT_EQ(4, testArray.size());
      ASSERT_EQ(4, testArray.capacity());
      EXPECT_EQ(10, Object::Instances());
      EXPECT_EQ(6, Object::CtorCalls());
      EXPECT_EQ(3, Object::DtorCalls());
      EXPECT_EQ(4, Object::CopyCtorCalls());
      EXPECT_EQ(3, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(10, Helper::Instances());
      EXPECT_EQ(10, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());
      EXPECT_EQ(4, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back(object5);
      ASSERT_EQ(5, testArray.size());
      ASSERT_EQ(8, testArray.capacity());
      EXPECT_EQ(11, Object::Instances());
      EXPECT_EQ(6, Object::CtorCalls());
      EXPECT_EQ(7, Object::DtorCalls());
      EXPECT_EQ(5, Object::CopyCtorCalls());
      EXPECT_EQ(7, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(11, Helper::Instances());
      EXPECT_EQ(11, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());
      EXPECT_EQ(5, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      testArray.push_back(object6);
      ASSERT_EQ(6, testArray.size());
      ASSERT_EQ(8, testArray.capacity());
      EXPECT_EQ(12, Object::Instances());
      EXPECT_EQ(6, Object::CtorCalls());
      EXPECT_EQ(7, Object::DtorCalls());
      EXPECT_EQ(6, Object::CopyCtorCalls());
      EXPECT_EQ(7, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(12, Helper::Instances());
      EXPECT_EQ(12, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());
      EXPECT_EQ(6, std::distance(testArray.begin(), testArray.end()));

      this->print(testArray);

      for (auto i = 0u; i < testArray.size(); ++i)
      {
        EXPECT_EQ(i, testArray[i].data());
      }
    }

    EXPECT_EQ(6, Object::Instances());
    EXPECT_EQ(6, Object::CtorCalls());
    EXPECT_EQ(13, Object::DtorCalls());
    EXPECT_EQ(6, Object::CopyCtorCalls());
    EXPECT_EQ(7, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(6, Helper::Instances());
    EXPECT_EQ(12, Helper::CtorCalls());
    EXPECT_EQ(6, Helper::DtorCalls());

    EXPECT_NE(object1, object2);
    EXPECT_NE(object3, object4);
    EXPECT_NE(object5, object6);
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(6, Object::CtorCalls());
  EXPECT_EQ(19, Object::DtorCalls());
  EXPECT_EQ(6, Object::CopyCtorCalls());
  EXPECT_EQ(7, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(0, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(12, Helper::CtorCalls());
  EXPECT_EQ(12, Helper::DtorCalls());
}  // namespace test

TYPED_TEST(TestsWithObjects, test_add)
{
  {
    int randomNumbers[ObjectsAmount];
    std::generate_n(randomNumbers, ObjectsAmount, [this]() { return this->get_random_number(); });

    TypeParam testArray{};
    const std::size_t ExpectedCapacity[ObjectsAmount]
      = {1, 2, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 32, 32};

    std::size_t j = 0;
    for (const auto& randomNumber : randomNumbers)
    {
      testArray.push_back(randomNumber);
      EXPECT_EQ(ExpectedCapacity[j++], testArray.capacity());
    }

    this->print(testArray);
    ASSERT_EQ(ObjectsAmount, testArray.size());

    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      EXPECT_EQ(randomNumbers[i], testArray[i].data()) << "i=" << i;
    }
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(20, Object::CtorCalls());
  EXPECT_EQ(71, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(51, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(0, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(20, Helper::CtorCalls());
  EXPECT_EQ(20, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_sort)
{
  {
    TypeParam testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = this->get_random_number();
      testArray.push_back(randomNumber);
    }
    this->print(testArray);
    std::sort(testArray.begin(), testArray.end());
    this->print(testArray);

    for (auto i = 0u; i < ObjectsAmount - 1; ++i)
    {
      ASSERT_LE(testArray[i], testArray[i + 1]);
    }
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(20, Object::CtorCalls());
  EXPECT_EQ(95, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(75, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(85, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(20, Helper::CtorCalls());
  EXPECT_EQ(20, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_erase_simple)
{
  {
    TypeParam testArray{};

    testArray.push_back(1);
    ASSERT_EQ(1, testArray.size());
    ASSERT_EQ(1, testArray.capacity());
    testArray.push_back(2);
    ASSERT_EQ(2, testArray.size());
    ASSERT_EQ(2, testArray.capacity());
    testArray.push_back(3);
    ASSERT_EQ(3, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    testArray.push_back(4);
    ASSERT_EQ(4, testArray.size());
    ASSERT_EQ(4, testArray.capacity());
    testArray.push_back(5);
    ASSERT_EQ(5, testArray.size());
    ASSERT_EQ(8, testArray.capacity());

    EXPECT_EQ(5, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(12, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(5, Helper::Instances());
    EXPECT_EQ(5, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    this->print(testArray);

    testArray.erase(testArray.begin() + 4);
    this->print(testArray);
    ASSERT_EQ(8, testArray.capacity());
    ASSERT_EQ(4, testArray.size());
    ASSERT_EQ(4, std::distance(testArray.begin(), testArray.end()));

    EXPECT_EQ(4, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(13, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(4, Helper::Instances());
    EXPECT_EQ(5, Helper::CtorCalls());
    EXPECT_EQ(1, Helper::DtorCalls());

    EXPECT_EQ(1, testArray[0].data());
    EXPECT_EQ(2, testArray[1].data());
    EXPECT_EQ(3, testArray[2].data());
    EXPECT_EQ(4, testArray[3].data());

    testArray.erase(testArray.begin() + 2);
    this->print(testArray);
    ASSERT_EQ(8, testArray.capacity());
    ASSERT_EQ(3, testArray.size());
    ASSERT_EQ(3, std::distance(testArray.begin(), testArray.end()));

    EXPECT_EQ(3, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(14, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(1, Object::MoveAssignCalls());
    EXPECT_EQ(3, Helper::Instances());
    EXPECT_EQ(5, Helper::CtorCalls());
    EXPECT_EQ(2, Helper::DtorCalls());

    EXPECT_EQ(1, testArray[0].data());
    EXPECT_EQ(2, testArray[1].data());
    EXPECT_EQ(4, testArray[2].data());

    testArray.erase(testArray.begin() + 0);
    this->print(testArray);
    ASSERT_EQ(8, testArray.capacity());
    ASSERT_EQ(2, testArray.size());
    ASSERT_EQ(2, std::distance(testArray.begin(), testArray.end()));

    EXPECT_EQ(2, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(15, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(3, Object::MoveAssignCalls());
    EXPECT_EQ(2, Helper::Instances());
    EXPECT_EQ(5, Helper::CtorCalls());
    EXPECT_EQ(3, Helper::DtorCalls());

    EXPECT_EQ(2, testArray[0].data());
    EXPECT_EQ(4, testArray[1].data());
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(5, Object::CtorCalls());
  EXPECT_EQ(17, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(12, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(3, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(5, Helper::CtorCalls());
  EXPECT_EQ(5, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_erase)
{
  {
    TypeParam originalArray{};
    TypeParam testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = this->get_random_number();
      originalArray.push_back(randomNumber);
      testArray.push_back(randomNumber);
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
      EXPECT_EQ(originalArray[i * 2u].data(), testArray[i].data());
    }
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(40, Object::CtorCalls());
  EXPECT_EQ(142, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(102, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(45, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(40, Helper::CtorCalls());
  EXPECT_EQ(40, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_insert_simple)
{
  {
    TypeParam testArray{};

    testArray.insert(testArray.begin() + 0, 1);
    this->print(testArray);
    ASSERT_EQ(1, testArray.capacity());
    ASSERT_EQ(1, testArray.size());

    EXPECT_EQ(1, Object::Instances());
    EXPECT_EQ(1, Object::CtorCalls());
    EXPECT_EQ(1, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(1, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(1, Helper::Instances());
    EXPECT_EQ(1, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    EXPECT_EQ(1, testArray[0].data());
    testArray.insert(testArray.begin() + 1, 3);
    this->print(testArray);
    ASSERT_EQ(2, testArray.capacity());
    ASSERT_EQ(2, testArray.size());

    EXPECT_EQ(2, Object::Instances());
    EXPECT_EQ(2, Object::CtorCalls());
    EXPECT_EQ(3, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(3, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(2, Helper::Instances());
    EXPECT_EQ(2, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    EXPECT_EQ(1, testArray[0].data());
    EXPECT_EQ(3, testArray[1].data());

    testArray.insert(testArray.begin() + 1, 2);
    this->print(testArray);
    ASSERT_EQ(4, testArray.capacity());
    ASSERT_EQ(3, testArray.size());

    EXPECT_EQ(3, Object::Instances());
    EXPECT_EQ(3, Object::CtorCalls());
    EXPECT_EQ(6, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(6, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(3, Helper::Instances());
    EXPECT_EQ(3, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    EXPECT_EQ(1, testArray[0].data());
    EXPECT_EQ(2, testArray[1].data());
    EXPECT_EQ(3, testArray[2].data());

    testArray.insert(testArray.begin() + 0, 0);
    this->print(testArray);
    ASSERT_EQ(4, testArray.capacity());
    ASSERT_EQ(4, testArray.size());

    EXPECT_EQ(4, Object::Instances());
    EXPECT_EQ(4, Object::CtorCalls());
    EXPECT_EQ(7, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(7, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(3, Object::MoveAssignCalls());
    EXPECT_EQ(4, Helper::Instances());
    EXPECT_EQ(4, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    EXPECT_EQ(0, testArray[0].data());
    EXPECT_EQ(1, testArray[1].data());
    EXPECT_EQ(2, testArray[2].data());
    EXPECT_EQ(3, testArray[3].data());
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(4, Object::CtorCalls());
  EXPECT_EQ(11, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(7, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(3, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(4, Helper::CtorCalls());
  EXPECT_EQ(4, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_insert)
{
  {
    TypeParam testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = this->get_random_number();
      testArray.push_back(randomNumber);
    }

    this->print(testArray);

    constexpr std::size_t InsertionsAmount = 10;
    for (auto i = 0u; i < InsertionsAmount; ++i)
    {
      const int randomNumber = this->get_random_number();
      const auto position = (i == InsertionsAmount - 1 || i == 0)
                              ? (i == 0 ? 0 : testArray.size())
                              : static_cast<std::size_t>(
                                  this->get_random_number(0u, static_cast<int>(testArray.size())));
      testArray.insert(testArray.begin() + position, randomNumber);
      EXPECT_EQ(randomNumber, testArray[position].data())
        << "Insert " << randomNumber << " at " << position;
      this->print(testArray);
    }

    EXPECT_EQ(InsertionsAmount + ObjectsAmount, testArray.size());
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(30, Object::CtorCalls());
  EXPECT_EQ(91, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(61, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(105, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(30, Helper::CtorCalls());
  EXPECT_EQ(30, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_clear)
{
  {
    TypeParam testArray{};
    for (auto i = 0u; i < ObjectsAmount; ++i)
    {
      const auto randomNumber = this->get_random_number();
      testArray.push_back(randomNumber);
    }
    EXPECT_EQ(ObjectsAmount, testArray.size());

    testArray.clear();

    EXPECT_EQ(0, testArray.size());
    EXPECT_EQ(testArray.begin(), testArray.end());
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(20, Object::CtorCalls());
  EXPECT_EQ(71, Object::DtorCalls());
  EXPECT_EQ(0, Object::CopyCtorCalls());
  EXPECT_EQ(51, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(0, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(20, Helper::CtorCalls());
  EXPECT_EQ(20, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_copy_ctor)
{
  constexpr int ObjectsAmount = 5;
  int randomNumbers[ObjectsAmount];
  std::generate_n(randomNumbers, ObjectsAmount, [this]() { return this->get_random_number(); });
  {
    TypeParam testArray;
    for (const int& randomNumber : randomNumbers)
    {
      testArray.push_back(randomNumber);
    }

    EXPECT_EQ(5, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(12, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(5, Helper::Instances());
    EXPECT_EQ(5, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    {
      const TypeParam& constRef = testArray;
      TypeParam anotherArray(constRef);

      EXPECT_EQ(10, Object::Instances());
      EXPECT_EQ(5, Object::CtorCalls());
      EXPECT_EQ(12, Object::DtorCalls());
      EXPECT_EQ(5, Object::CopyCtorCalls());
      EXPECT_EQ(12, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(10, Helper::Instances());
      EXPECT_EQ(10, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());

      for (auto i = 0u; i < ObjectsAmount; ++i)
      {
        EXPECT_EQ(randomNumbers[i], anotherArray[i].data()) << "i=" << i;
      }
    }

    EXPECT_EQ(5, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(17, Object::DtorCalls());
    EXPECT_EQ(5, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(5, Helper::Instances());
    EXPECT_EQ(10, Helper::CtorCalls());
    EXPECT_EQ(5, Helper::DtorCalls());

    {
      TypeParam anotherArray(std::move(testArray));

      EXPECT_EQ(5, Object::Instances());
      EXPECT_EQ(5, Object::CtorCalls());
      EXPECT_EQ(17, Object::DtorCalls());
      EXPECT_EQ(5, Object::CopyCtorCalls());
      EXPECT_EQ(12, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(5, Helper::Instances());
      EXPECT_EQ(10, Helper::CtorCalls());
      EXPECT_EQ(5, Helper::DtorCalls());

      for (auto i = 0u; i < ObjectsAmount; ++i)
      {
        EXPECT_EQ(randomNumbers[i], anotherArray[i].data()) << "i=" << i;
      }
    }

    EXPECT_EQ(0, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(22, Object::DtorCalls());
    EXPECT_EQ(5, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(0, Helper::Instances());
    EXPECT_EQ(10, Helper::CtorCalls());
    EXPECT_EQ(10, Helper::DtorCalls());
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(5, Object::CtorCalls());
  EXPECT_EQ(22, Object::DtorCalls());
  EXPECT_EQ(5, Object::CopyCtorCalls());
  EXPECT_EQ(12, Object::MoveCtorCalls());
  EXPECT_EQ(0, Object::CopyAssignCalls());
  EXPECT_EQ(0, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(10, Helper::CtorCalls());
  EXPECT_EQ(10, Helper::DtorCalls());
}

TYPED_TEST(TestsWithObjects, test_assign_ctor)
{
  constexpr int ObjectsAmount = 5;
  int randomNumbers[ObjectsAmount];
  std::generate_n(randomNumbers, ObjectsAmount, [this]() { return this->get_random_number(); });
  {
    TypeParam testArray;
    for (const int& randomNumber : randomNumbers)
    {
      testArray.push_back(randomNumber);
    }

    EXPECT_EQ(5, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(12, Object::DtorCalls());
    EXPECT_EQ(0, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(5, Helper::Instances());
    EXPECT_EQ(5, Helper::CtorCalls());
    EXPECT_EQ(0, Helper::DtorCalls());

    {
      const TypeParam& constRef = testArray;

      // ReSharper disable once CppJoinDeclarationAndAssignment
      TypeParam anotherArray;
      anotherArray = constRef;

      EXPECT_EQ(10, Object::Instances());
      EXPECT_EQ(5, Object::CtorCalls());
      EXPECT_EQ(12, Object::DtorCalls());
      EXPECT_EQ(5, Object::CopyCtorCalls());
      EXPECT_EQ(12, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(10, Helper::Instances());
      EXPECT_EQ(10, Helper::CtorCalls());
      EXPECT_EQ(0, Helper::DtorCalls());

      ASSERT_EQ(ObjectsAmount, anotherArray.size());
      for (auto i = 0u; i < ObjectsAmount; ++i)
      {
        EXPECT_EQ(randomNumbers[i], anotherArray[i].data()) << "i=" << i;
      }
    }

    EXPECT_EQ(5, Object::Instances());
    EXPECT_EQ(5, Object::CtorCalls());
    EXPECT_EQ(17, Object::DtorCalls());
    EXPECT_EQ(5, Object::CopyCtorCalls());
    EXPECT_EQ(12, Object::MoveCtorCalls());
    EXPECT_EQ(0, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(5, Helper::Instances());
    EXPECT_EQ(10, Helper::CtorCalls());
    EXPECT_EQ(5, Helper::DtorCalls());

    {
      const TypeParam& constRef = testArray;

      TypeParam anotherArray;
      for (auto i = 0u; i < ObjectsAmount / 2; ++i)
      {
        anotherArray.push_back(i);
      }

      EXPECT_EQ(7, Object::Instances());
      EXPECT_EQ(7, Object::CtorCalls());
      EXPECT_EQ(20, Object::DtorCalls());
      EXPECT_EQ(5, Object::CopyCtorCalls());
      EXPECT_EQ(15, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(7, Helper::Instances());
      EXPECT_EQ(12, Helper::CtorCalls());
      EXPECT_EQ(5, Helper::DtorCalls());

      anotherArray = constRef;

      EXPECT_EQ(10, Object::Instances());
      EXPECT_EQ(7, Object::CtorCalls());
      EXPECT_EQ(22, Object::DtorCalls());
      EXPECT_EQ(10, Object::CopyCtorCalls());
      EXPECT_EQ(15, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(10, Helper::Instances());
      EXPECT_EQ(17, Helper::CtorCalls());
      EXPECT_EQ(7, Helper::DtorCalls());

      ASSERT_EQ(ObjectsAmount, anotherArray.size());
      for (auto i = 0u; i < ObjectsAmount; ++i)
      {
        EXPECT_EQ(randomNumbers[i], anotherArray[i].data()) << "i=" << i;
      }
    }

    {
      const TypeParam& constRef = testArray;

      TypeParam anotherArray;
      for (auto i = 0u; i < ObjectsAmount * 2; ++i)
      {
        anotherArray.push_back(i);
      }

      EXPECT_EQ(15, Object::Instances());
      EXPECT_EQ(17, Object::CtorCalls());
      EXPECT_EQ(52, Object::DtorCalls());
      EXPECT_EQ(10, Object::CopyCtorCalls());
      EXPECT_EQ(40, Object::MoveCtorCalls());
      EXPECT_EQ(0, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(15, Helper::Instances());
      EXPECT_EQ(27, Helper::CtorCalls());
      EXPECT_EQ(12, Helper::DtorCalls());

      anotherArray = constRef;

      EXPECT_EQ(10, Object::Instances());
      EXPECT_EQ(17, Object::CtorCalls());
      EXPECT_EQ(57, Object::DtorCalls());
      EXPECT_EQ(10, Object::CopyCtorCalls());
      EXPECT_EQ(40, Object::MoveCtorCalls());
      EXPECT_EQ(5, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(10, Helper::Instances());
      EXPECT_EQ(32, Helper::CtorCalls());
      EXPECT_EQ(22, Helper::DtorCalls());

      ASSERT_EQ(ObjectsAmount, anotherArray.size());
      for (auto i = 0u; i < ObjectsAmount; ++i)
      {
        EXPECT_EQ(randomNumbers[i], anotherArray[i].data()) << "i=" << i;
      }
    }

    {
      TypeParam anotherArray;
      for (auto i = 0u; i < ObjectsAmount / 2; ++i)
      {
        anotherArray.push_back(i);
      }

      EXPECT_EQ(7, Object::Instances());
      EXPECT_EQ(19, Object::CtorCalls());
      EXPECT_EQ(65, Object::DtorCalls());
      EXPECT_EQ(10, Object::CopyCtorCalls());
      EXPECT_EQ(43, Object::MoveCtorCalls());
      EXPECT_EQ(5, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(7, Helper::Instances());
      EXPECT_EQ(34, Helper::CtorCalls());
      EXPECT_EQ(27, Helper::DtorCalls());

      anotherArray = std::move(testArray);

      EXPECT_EQ(5, Object::Instances());
      EXPECT_EQ(19, Object::CtorCalls());
      EXPECT_EQ(67, Object::DtorCalls());
      EXPECT_EQ(10, Object::CopyCtorCalls());
      EXPECT_EQ(43, Object::MoveCtorCalls());
      EXPECT_EQ(5, Object::CopyAssignCalls());
      EXPECT_EQ(0, Object::MoveAssignCalls());
      EXPECT_EQ(5, Helper::Instances());
      EXPECT_EQ(34, Helper::CtorCalls());
      EXPECT_EQ(29, Helper::DtorCalls());

      ASSERT_EQ(ObjectsAmount, anotherArray.size());
      for (auto i = 0u; i < ObjectsAmount; ++i)
      {
        EXPECT_EQ(randomNumbers[i], anotherArray[i].data()) << "i=" << i;
      }
    }

    EXPECT_EQ(0, Object::Instances());
    EXPECT_EQ(19, Object::CtorCalls());
    EXPECT_EQ(72, Object::DtorCalls());
    EXPECT_EQ(10, Object::CopyCtorCalls());
    EXPECT_EQ(43, Object::MoveCtorCalls());
    EXPECT_EQ(5, Object::CopyAssignCalls());
    EXPECT_EQ(0, Object::MoveAssignCalls());
    EXPECT_EQ(0, Helper::Instances());
    EXPECT_EQ(34, Helper::CtorCalls());
    EXPECT_EQ(34, Helper::DtorCalls());
  }

  EXPECT_EQ(0, Object::Instances());
  EXPECT_EQ(19, Object::CtorCalls());
  EXPECT_EQ(72, Object::DtorCalls());
  EXPECT_EQ(10, Object::CopyCtorCalls());
  EXPECT_EQ(43, Object::MoveCtorCalls());
  EXPECT_EQ(5, Object::CopyAssignCalls());
  EXPECT_EQ(0, Object::MoveAssignCalls());
  EXPECT_EQ(0, Helper::Instances());
  EXPECT_EQ(34, Helper::CtorCalls());
  EXPECT_EQ(34, Helper::DtorCalls());
}
}  // namespace test
}  // namespace g5_task
