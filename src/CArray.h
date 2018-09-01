// Copyright 2018 (с) antidotcb. All rights reserved.
// Created by Danylo Bilyk on 26-Aug-18.
//

#pragma once

#include <cmath>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace g5_task
{
template <typename TData>
class CArray
{
public:
  using value_type = TData;

  CArray() = default;

  CArray(
    const CArray& _array
    )
  {
    construct_from(_array);
  }

  CArray(
    CArray&& _array
    ) noexcept
  {
    move_from(std::move(_array));
  }

  CArray& operator=(
    const CArray& _array
    )
  {
    construct_from(_array);
    return *this;
  }

  CArray& operator=(
    CArray&& _array
    ) noexcept
  {
    clear();
    move_from(std::move(_array));
    return *this;
  }

  ~CArray()
  {
    clear();
  }

  TData* begin()
  {
    return m_begin;
  }

  TData* end()
  {
    return m_end;
  }

  const TData* begin() const
  {
    return m_begin;
  }

  const TData* end() const
  {
    return m_end;
  }

  void push_back(
    const TData& _value
    )
  {
    push_back_t(_value);
  }

  void push_back(
    TData&& _value
    )
  {
    push_back_t(std::move(_value));
  }

  void insert(
    const unsigned int _index, const TData& _value
    )
  {
    insert_t(_index, _value);
  }

  void insert(
    const unsigned int _index, TData&& _value
    )
  {
    insert_t(_index, std::move(_value));
  }

  void insert(
    const TData* _ptr, const TData& _value
    )
  {
    unsigned int index = _ptr - m_begin;
    insert_t(index, _value);
  }

  void insert(
    const TData* _ptr, TData&& _value
    )
  {
    unsigned int index = _ptr - m_begin;
    insert_t(index, std::move(_value));
  }

  void erase(
    const TData* _ptr
    )
  {
    const unsigned int index = _ptr - m_begin;
    erase(index);
  }

  void erase(
    const unsigned int _index
    )
  {
    validate_index(_index);

    move_t(m_begin + _index + 1, m_size - _index - 1, m_begin + _index);

    destruct_t(m_end - 1, 1);
    --m_size;
    m_end = m_begin + m_size;
  }

  void clear()
  {
    destruct_t(m_begin, m_size);
    dealloc(m_begin);

    m_capacity = 0u;
    m_size = 0u;
    m_begin = nullptr;
    m_end = nullptr;
  }

  unsigned int capacity() const
  {
    return m_capacity;
  }

  unsigned int size() const
  {
    return m_size;
  }

  TData& operator[](
    const unsigned int _index
    )
  {
    validate_index(_index);
    auto ptr = m_begin + _index;
    return *ptr;
  }

  const TData& operator[](
    const unsigned int _index
    ) const
  {
    return const_cast<CArray&>(*this).operator[](_index);
  }

protected:
  static constexpr unsigned int ElementSize = sizeof(TData);

  void construct_from(
    const CArray& _array
    )
  {
    const auto size = _array.size();
    if (this != &_array)
    {
      if (m_capacity < _array.size())
      {
        // reallocate memory if only there is not enough capacity
        clear();
        void* const ptr = alloc(size);
        try
        {
          const auto dest = reinterpret_cast<TData*>(ptr);
          copy_construct_t(_array.begin(), size, dest);
        }
        catch (...)
        {
          dealloc(ptr);
          throw;
        }

        m_size = size;
        m_capacity = size;
        m_begin = reinterpret_cast<TData*>(ptr);
        m_end = m_begin + m_size;
      }
      else
      {
        // if there are enough capacity just remove unnecessary elements and just copy over
        if (m_size > size)
        {
          destruct_t(m_begin + size, m_size - size);
        }
        copy_t(_array.begin(), size, m_begin);
        m_size = size;
        m_end = m_begin + m_size;
      }
    }
  }

  void move_from(
    CArray&& _array
    )
  {
    std::swap(m_size, _array.m_size);
    std::swap(m_capacity, _array.m_capacity);
    std::swap(m_begin, _array.m_begin);
    std::swap(m_end, _array.m_end);
  }

  template <typename T>
  void push_back_t(
    T&& _value
    )
  {
    const auto size = m_size + 1;

    if (size > m_capacity)
    {
      const auto capacity = optimal_capacity(size);
      void* const ptr = alloc(capacity);

      try
      {
        auto dest = static_cast<TData*>(ptr);
        move_construct_t(m_begin, m_size, dest);
      }
      catch (...)
      {
        dealloc(ptr);
        throw;
      }

      destruct_t(m_begin, m_size);
      dealloc(m_begin);

      m_capacity = capacity;
      m_begin = static_cast<TData*>(ptr);
      m_end = m_begin + m_size;
    }

    auto dest = m_begin + m_size;
    ::new (dest) TData(std::forward<T>(_value));

    m_size = size;
    m_end = m_begin + m_size;
  }

  template <typename T>
  void insert_t(
    const unsigned int _index,
    T&& _value
    )
  {
    if (_index == m_size)
    {
      push_back_t(std::forward<T>(_value));
      return;
    }
    validate_index(_index);

    const auto size = m_size + 1;
    if (size > m_capacity)
    {
      const auto capacity = optimal_capacity(size);
      void* const ptr = alloc(capacity);

      try
      {
        auto dest = static_cast<TData*>(ptr);
        move_construct_t(m_begin, _index, dest);
        move_construct_t(m_begin + _index, m_size - _index, dest + _index + 1);
      }
      catch (...)
      {
        dealloc(ptr);
        throw;
      }

      destruct_t(m_begin, m_size);
      dealloc(m_begin);

      m_capacity = capacity;
      m_begin = static_cast<TData*>(ptr);

      const auto dest = m_begin + _index;
      ::new (dest) TData(std::forward<T>(_value));
    }
    else
    {
      move_t(m_begin + _index, m_size - _index, m_begin + _index + 1);
      m_begin[_index] = std::forward<T>(_value);
    }

    m_size = size;
    m_end = m_begin + m_size;
  }

  // POD & builtin types needs no ctor & dtor mechanics, so simply copy memory in all cases

  template <typename T>
  void destruct_t(
    T*,
    const unsigned int,
    typename std::enable_if<std::is_pod<T>::value>::type* = nullptr
    )
  {
    // nothing to do for pod and builtin types
  }

  template <typename T>
  void move_construct_t(
    T* _src,
    const unsigned int _count,
    T* _dest,
    typename std::enable_if<std::is_pod<T>::value>::type* = nullptr
    )
  {
    memcpy(_dest, _src, _count * ElementSize);
  }

  template <typename T>
  void copy_construct_t(
    const T* _src,
    const unsigned int _count,
    T* _dest,
    typename std::enable_if<std::is_pod<T>::value>::type* = nullptr)
  {
    memcpy(_dest, _src, _count * ElementSize);
  }

  template <typename T>
  void copy_t(
    const T* const _src,
    const unsigned int _count,
    T* _dest,
    typename std::enable_if<std::is_pod<T>::value>::type* = nullptr
    ) const
  {
    memcpy(_dest, _src, _count * ElementSize);
  }

  template <typename T>
  void move_t(
    T* const _src,
    const unsigned int _count,
    T* _dest,
    typename std::enable_if<std::is_pod<T>::value>::type* = nullptr
    ) const
  {
    memcpy(_dest, _src, _count * ElementSize);
  }

  // complex classes need ctor & dtor, move assignments calls so there goes methods for them

  template <
    typename T,
    typename std::enable_if<!std::is_pod<T>::value, int>::type = 0
    >
  void destruct_t(
    T* _src,
    const unsigned int _count
    )
  {
    const auto end = _src + _count;
    for (auto ptr = _src; ptr < end; ++ptr)
    {
      ptr->~T();
    }
  }

  template <
    typename T,
    typename std::enable_if<!std::is_pod<T>::value, int>::type = 0
    >
  void move_construct_t(
    T* _src,
    const unsigned int _count,
    T* _dest
    )
  {
    const auto end = _src + _count;
    for (auto ptr = _src; ptr < end; ++ptr, ++_dest)
    {
      ::new (_dest) T(std::move(*ptr));
    }
  }

  template <
    typename T,
    typename std::enable_if<!std::is_pod<T>::value, int>::type = 0
    >
  void copy_construct_t(
    const T* _src,
    const unsigned int _count, T* _dest
    )
  {
    const auto end = _src + _count;
    for (const auto* ptr = _src; ptr != end; ++ptr, ++_dest)
    {
      ::new (_dest) T(*ptr);
    }
  }

  template <
    typename T,
    typename std::enable_if<!std::is_pod<T>::value, int>::type = 0
    >
  void copy_t(
    const T* const _src,
    const unsigned int _count,
    T* _dest
    ) const
  {
    const auto end = _src + _count;
    for (auto ptr = _src; ptr != end; ++ptr, ++_dest)
    {
      if (_dest < m_end)
      {
        *_dest = *ptr;
      }
      else
      {
        ::new (_dest) T(*ptr);
      }
    }
  }

  template <
    typename T,
    typename std::enable_if<!std::is_pod<T>::value, int>::type = 0
    >
  void move_t(
    T* const _src,
    const unsigned int _count,
    T* _dest
    ) const
  {
    const auto end = _src + _count;

    if (_dest > _src && _dest < end)
    {
      _dest = _dest + _count - 1;
      for (auto ptr = end - 1; ptr != _src - 1; --ptr, --_dest)
      {
        if (_dest < m_end)
        {
          *_dest = std::move(*ptr);
        }
        else
        {
          ::new (_dest) T(std::move(*ptr));
        }
      }
    }
    else
    {
      for (auto ptr = _src; ptr != end; ++ptr, ++_dest)
      {
        if (_dest < m_end)
        {
          *_dest = std::move(*ptr);
        }
        else
        {
          ::new (_dest) T(std::move(*ptr));
        }
      }
    }
  }

  void validate_index(
    const unsigned int _index
  ) const
  {
    if (_index >= m_size)
    {
      throw std::out_of_range("Index is out of range");
    }
  }

  static void* alloc(
    const unsigned int _count
    )
  {
    const auto size = _count * ElementSize;
    void* ptr = malloc(size);
    if (!ptr)
    {
      throw std::runtime_error("Fail to allocate memory");
    }
    return ptr;
  }

  static void dealloc(
    void* _ptr
    )
  {
    if (_ptr)
    {
      free(_ptr);
    }
  }

  static unsigned int optimal_capacity(
    const unsigned int _count
    )
  {
    // compute the next highest power of 2 greater _count
    const auto next = static_cast<unsigned int>(std::pow(2, std::ceil(log(_count) / std::log(2))));
    return next;
  }

protected:
  unsigned int m_size{0};
  unsigned int m_capacity{0};

  TData* m_begin{nullptr};
  TData* m_end{nullptr};
};

}  // namespace g5_task
