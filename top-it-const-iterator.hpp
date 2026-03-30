#ifndef TOP_IT_CONST_ITERATOR_HPP
#define TOP_IT_CONST_ITERATOR_HPP
#include <cassert>
#include <cstddef>
#include <memory>

namespace topit
{
  template< class T > struct Vector;

  template< class T >
  struct VecConstIter {
  public:
    VecConstIter();
    VecConstIter< T >& operator++();
    VecConstIter< T > operator++(int);

    VecConstIter< T >& operator--();
    VecConstIter< T > operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const VecConstIter< T >& other) const;
    bool operator==(const VecConstIter< T >& other) const;
  private:
    friend struct Vector< T >;
    VecConstIter(const T* data, size_t size, size_t pos);
    const T* data_;
    size_t size_;
    size_t pos_;
  };
}

template< class T >
topit::VecConstIter< T >::VecConstIter():
  data_(nullptr),
  size_(0),
  pos_(0)
{}

template< class T >
topit::VecConstIter< T >::VecConstIter(const T* data, size_t size, size_t pos):
  data_(data),
  size_(size),
  pos_(pos)
{}

template< class T >
topit::VecConstIter< T >& topit::VecConstIter< T >::operator++()
{
  assert(pos_ != size_);
  ++pos_;
  return *this;
}

template< class T >
topit::VecConstIter< T > topit::VecConstIter< T >::operator++(int)
{
  assert(pos_ != size_);
  VecConstIter< T >tmp{*this};
  ++(*this);
  return tmp;
}


template< class T >
topit::VecConstIter< T >& topit::VecConstIter< T >::operator--()
{
  assert(pos_ != 0);
  pos_--;
  return *this;
}

template< class T >
topit::VecConstIter< T > topit::VecConstIter< T >::operator--(int)
{
  assert(pos_ != 0);
  VecConstIter< T >tmp{*this};
  --(*this);
  return tmp;
}


template< class T >
const T& topit::VecConstIter< T >::operator*() const
{
  assert(data_ != nullptr);
  return data_[pos_];
}

template< class T >
const T* topit::VecConstIter< T >::operator->() const
{
  assert(data_ != nullptr);
  return std::addressof(data_[pos_]);
}

template< class T >
bool topit::VecConstIter< T >::operator!=(const VecConstIter< T >& rhs) const
{
  return !(*this == rhs);
}

template< class T >
bool topit::VecConstIter< T >::operator==(const VecConstIter< T >& rhs) const
{
  return data_ == rhs.data_ && pos_ == rhs.pos_;
}

#endif