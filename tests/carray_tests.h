// Copyright 2018 (с) The Creep Brothers. All rights reserved.
// Created by antidotcb on 08/29/18.
//

#pragma once

#include <gtest/gtest.h>
#include <src/CArray.h>

#include <iostream>
#include <random>

namespace g5_task
{
namespace test
{
namespace helpers
{
class Helper
{
public:
  explicit Helper(const int data)
    : m_data(data)
  {
    ++m_s_CtorCalls;
    ++m_s_Instances;
  }

  ~Helper()
  {
    ++m_s_DtorCalls;
    --m_s_Instances;
  }

  int data() const noexcept
  {
    return m_data;
  }

  static int Instances()
  {
    return m_s_Instances;
  }

  static int CtorCalls()
  {
    return m_s_CtorCalls;
  }

  static int DtorCalls()
  {
    return m_s_DtorCalls;
  }

  static void reset()
  {
    m_s_Instances = m_s_CtorCalls = m_s_DtorCalls = 0;
  }

private:
  static int m_s_Instances;
  static int m_s_CtorCalls;
  static int m_s_DtorCalls;

  int m_data{0};
};

class Object
{
public:
  Object(const int data)
    : m_helper{std::make_unique<Helper>(data)}
  {
    ++Object::m_s_CtorCalls;
    ++Object::m_s_Instances;
  }

  ~Object()
  {
    ++Object::m_s_DtorCalls;
    --Object::m_s_Instances;
  }

  Object(const Object& object)
    : m_helper{std::make_unique<Helper>(object.data())}
  {
    ++m_s_CopyCtorCalls;
    ++Object::m_s_Instances;
  }

  Object(Object&& object) noexcept
    : m_helper{std::move(object.m_helper)}
  {
    ++m_s_MoveCtorCalls;
    ++Object::m_s_Instances;
  }

  Object& operator=(const Object& object)
  {
    m_helper = std::make_unique<Helper>(object.data());
    ++m_s_CopyAssignCalls;
    return (*this);
  }

  Object& operator=(Object&& object) noexcept
  {
    m_helper = std::move(object.m_helper);
    ++m_s_MoveAssignCalls;
    return (*this);
  }

  bool operator==(const Object& object) const noexcept
  {
    return data() == object.data();
  }

  bool operator<(const Object& object) const noexcept
  {
    return data() < object.data();
  }

  bool operator<=(const Object& object) const noexcept
  {
    return data() <= object.data();
  }

  bool operator!=(const Object& object) const noexcept
  {
    return data() != object.data();
  }

  operator int() const
  {
    return m_helper->data();
  }

  int data() const noexcept
  {
    return m_helper->data();
  }

  static int Instances()
  {
    return m_s_Instances;
  }

  static int CtorCalls()
  {
    return m_s_CtorCalls;
  }

  static int DtorCalls()
  {
    return m_s_DtorCalls;
  }

  static int CopyCtorCalls()
  {
    return m_s_CopyCtorCalls;
  }

  static int MoveCtorCalls()
  {
    return m_s_MoveCtorCalls;
  }

  static int CopyAssignCalls()
  {
    return m_s_CopyAssignCalls;
  }

  static int MoveAssignCalls()
  {
    return m_s_MoveAssignCalls;
  }

  static void reset()
  {
    m_s_CtorCalls = m_s_DtorCalls = m_s_CopyCtorCalls = m_s_MoveCtorCalls = m_s_CopyAssignCalls
      = m_s_Instances = m_s_MoveAssignCalls = 0;
  }

private:
  static int m_s_Instances;
  static int m_s_CtorCalls;
  static int m_s_DtorCalls;
  static int m_s_CopyCtorCalls;
  static int m_s_MoveCtorCalls;
  static int m_s_CopyAssignCalls;
  static int m_s_MoveAssignCalls;

  std::unique_ptr<Helper> m_helper{nullptr};
};
}  // namespace helpers

class CArrayTestBase : public ::testing::Test
{
protected:
  static constexpr int MinRandom = 0;
  static constexpr int MaxRandom = 100;

  int get_random_number(const int _min = MinRandom, const int _max = MaxRandom)
  {
    const int min = std::min(_min, _max);
    const int max = std::max(_min, _max);
    std::uniform_int_distribution<int> distribution(min, max);
    int result = distribution(m_generator);
    return result;
  }

  template <typename T>
  void print(const T& _array)
  {
#ifdef NDEBUG
    return;
#endif
    std::cout << std::endl;
    for (const auto& element : _array)
    {
      std::cout << element << " ";
    }
    std::cout << std::endl;
    std::cerr << std::endl;
  }

private:
  std::default_random_engine m_generator{};
};

}  // namespace test
}  // namespace g5_task
