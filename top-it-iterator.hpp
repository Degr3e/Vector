#ifndef TOP_IT_ITERATOR_HPP
#define TOP_IT_ITERATOR_HPP

#include <cassert>
#include <cstddef>

namespace topit
{
  template< class T > struct Vector;

  template< class T >
  struct VecIter
  {
  public:
    VecIter();
    VecIter< T >& operator++();
    VecIter< T > operator++(int);

    VecIter< T >& operator--();
    VecIter< T > operator--(int);

    T& operator*();
    T* operator->();

    bool operator!=(const VecIter< T >& other) const;
    bool operator==(const VecIter< T >& other) const;

  private:
    friend struct Vector< T >;
    VecIter(T* data, size_t size, size_t pos);
    T* data_;
    size_t size_;
    size_t pos_;
  };
}

template< class T >
topit::VecIter< T >::VecIter():
  data_(nullptr),
  size_(0),
  pos_(0)
{}

template< class T >
topit::VecIter< T >::VecIter(T* data, size_t size, size_t pos):
  data_(data),
  size_(size),
  pos_(pos)
{}

template< class T >
topit::VecIter< T >& topit::VecIter< T >::operator++()
{
  assert(pos_ != size_);
  ++pos_;
  return *this;
}

template< class T >
topit::VecIter< T > topit::VecIter< T >::operator++(int)
{
  assert(pos_ != size_);
  VecIter< T > tmp{*this};
  ++(*this);
  return tmp;
}

template< class T >
topit::VecIter< T >& topit::VecIter< T >::operator--()
{
  assert(pos_ != 0);
  --pos_;
  return *this;
}

template< class T >
topit::VecIter< T > topit::VecIter< T >::operator--(int)
{
  assert(pos_ != 0);
  VecIter< T > tmp{*this};
  --(*this);
  return tmp;
}

template< class T >
T& topit::VecIter< T >::operator*()
{
  assert(data_ != nullptr);
  return data_[pos_];
}

template< class T >
T* topit::VecIter< T >::operator->()
{
  assert(data_ != nullptr);
  return data_ + pos_;
}

template< class T >
bool topit::VecIter< T >::operator!=(const VecIter< T >& rhs) const
{
  return !(*this == rhs);
}

template< class T >
bool topit::VecIter< T >::operator==(const VecIter< T >& rhs) const
{
  return data_ == rhs.data_ && pos_ == rhs.pos_;
}

#endif

