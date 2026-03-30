#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include "top-it-iterator.hpp"
#include "top-it-const-iterator.hpp"
namespace topit
{
  template< class T >
  struct Vector {
  public:
    ~Vector();

    Vector();
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector(size_t size, const T& init);
    explicit Vector(std::initializer_list< T > il);
    Vector< T >& operator=(const Vector&);
    Vector< T >& operator=(Vector&&) noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;

    T& at(size_t it);
    const T& at(size_t it) const;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    //Классная работа 30.03.26
    void reserve(size_t);
    void shrimpToFit();
    void pushBackCount(size_t k, const T& v);
    void unsafePushBack(const T& v); //private
    template< class IT >
    void pushBackRange(IT b, size_t c);

    VecIter< T > begin() const;
    VecConstIter< T > cbegin() const;
    VecIter< T > end() const;
    VecConstIter< T > cend() const;

    void pushBack(const T& v);

    void popBack();
    void insert(size_t pos, const T& v);
    void insert(VecIter< T > pos, const T& v);
    void insert(VecIter< T > pos, size_t count, const T& v);
    void insert(VecIter< T > pos, VecIter< T > start, VecIter< T > end);

    void insert(const Vector< T >& another, size_t start, size_t end, size_t pos);
    void erase(size_t pos);
    void erase(size_t start, size_t end);
    void erase(VecIter< T > pos);
    void erase(VecIter< T > pos, size_t s);
    void erase(VecIter< T > start, VecIter< T > end);
    void swap(Vector< T >& rhs) noexcept;

  private:
    void extend(T** oldData, size_t& k, const T& newT);
    explicit Vector(size_t size);
    T* data_;
    size_t size_, capacity_;
  };
  template< class T >
  bool operator==(const Vector< T >& rhs, const Vector< T >& lhs);
}


template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::Vector(const Vector& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = init;
  }
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size]: nullptr),
  size_(size),
  capacity_(size_)
{}

template< class T >
topit::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t i = 0;
  for (auto it = il.begin(); it != il.end(); ++it)
  {
    data_[i++] = *it;
  }
}


template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }

  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }

  Vector< T >cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T >* cthis = this;
  return const_cast< T& >((*cthis)[id]);
}


template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}


template< class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis->at(id));
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}


template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
topit::VecIter< T > topit::Vector< T >::begin() const
{
  VecIter< T > it = VecIter< T >{data_, size_, 0};
  return it;
}

template< class T >
topit::VecIter< T > topit::Vector< T >::end() const
{
  VecIter< T > it = VecIter< T >{data_, size_, size_};
  return it;
}

template< class T >
topit::VecConstIter< T > topit::Vector< T >::cbegin() const
{
  VecConstIter< T > it = VecConstIter< T >{data_, size_, 0};
  return it;
}

template< class T >
topit::VecConstIter< T > topit::Vector< T >::cend() const
{
  VecConstIter< T > it = VecConstIter< T >{data_, size_, size_};
  return it;
}

template< class T >
void topit::Vector< T >::pushBack(const T& v) // тут с проверкой
{
  insert(size_, v);
}

template< class T >
template< class IT >
void topit::Vector< T >::pushBackRange(IT b, size_t c) // Не (IT e) потому что заставляет писать плохой код
{
  // Если памяти не хватает на с
  // -делаем так, чтоб хватило на k*
  // Добавляем в конец
}


template< class T >
void topit::Vector< T >::pushBackCount(size_t k, const T& v)
{
  // Если памяти не хватает на k
  // -делаем так, чтоб хватило на k*
  // Добавляем в конец
}

template< class T >
void topit::Vector< T >::unsafePushBack(const T& v) // Без проверки. Вызывается во всех остальных push back
{

}

template< class T >
void topit::Vector< T >::popBack()
{
  if (size_ == 0)
  {
    return;
  }
  erase(size_ - 1);
}
template< class T >
void topit::Vector< T >::insert(VecIter< T > pos, const T& v)
{
  insert(pos.pos_, v);
}

template< class T >
void topit::Vector< T >::insert(VecIter< T > pos, size_t count, const T& v)
{
  for (size_t i = 0; i < count; ++i)
  {
    insert(pos.pos_, v);
  }
}

template< class T >
void topit::Vector< T >::insert(VecIter< T > pos, VecIter< T > start, VecIter< T > end)
{
  size_t index = pos.pos_;
  for (VecIter<T> s = start; s != end; ++s)
  {
    insert(index, *s);
    ++index;
  }
}

template< class T >
void topit::Vector< T >::insert(size_t pos, const T& v)
{
  T* newData = nullptr;
  size_t newCapacity = 0;
  if (capacity_ == 0)
  {
    newData = new T[8];
    newCapacity = 8;
  }
  else if (pos >= capacity_)
  {
    newData = new T[pos + 1];
    newCapacity = pos + 1;
  }
  else if (size_ + 1 >= capacity_)
  {
    newData = new T[capacity_ * 2];
    newCapacity = capacity_ * 2;
  } else
  {
    newData = data_;
    newCapacity = capacity_;
  }

  size_t i = 0;
  try
  {
    if (pos > size_)
    {
      for (; i < size_; ++i)
      {
        newData[i] = data_[i];
      }
      newData[pos] = v;
      size_ = pos + 1;
    }
    else if (newData == data_)
    {
      for (i = size_; i > pos; --i)
      {
        newData[i] = newData[i - 1];
      }
      newData[pos] = v;
      ++size_;
    }
    else
    {
      for (; i < pos; ++i)
      {
        newData[i] = data_[i];
      }
      newData[pos] = v;
      for (; i < size_; ++i)
      {
        newData[i + 1] = data_[i];
      }
      size_++;
    }
  }
  catch(...)
  {
    delete[] newData;
    throw;
  }
  capacity_ = newCapacity;
  delete[] data_;
  data_ = newData;
}

template< class T >
void topit::Vector< T >::insert(const Vector< T >& another, size_t start, size_t end, size_t pos)
{
  for (size_t i = start; i < end; ++i)
  {
    insert(pos++, another[i]);
  }
}

template< class T >
void topit::Vector< T >::erase(size_t pos)
{
  erase(pos, pos + 1);
}

template< class T >
void topit::Vector< T >::erase(size_t start, size_t end)
{
  if (!size_)
  {
    return;
  }
  if (start >= size_ || start >= end)
  {
    return;
  }
  if (end > size_)
  {
    end = size_;
  }

  T* newData = new T[capacity_];
  try
  {
    size_t i = 0;
    for (; i < start; ++i)
    {
      newData[i] = data_[i];
    }
    for (size_t j = end; j < size_; ++j, ++i)
    {
      newData[i] = data_[j];
    }
    delete[] data_;
    data_ = newData;
    size_ -= (end - start);
  }
  catch(...)
  {
    delete[] newData;
    throw;
  }
}

template< class T >
void topit::Vector< T >::erase(VecIter< T > pos)
{
  erase(pos.pos_);
}


template< class T >
void topit::Vector< T >::erase(VecIter< T > pos, size_t s)
{
  for (size_t i = 0; i < s; ++i)
  {
    erase(pos);
  }
}

template< class T >
void topit::Vector< T >::erase(VecIter< T > start, VecIter< T > end)
{
  size_t s = start.pos_;
  size_t e = end.pos_;

  erase(s, e);
}


template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
bool topit::operator==(const Vector< T >& rhs, const Vector< T >& lhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

#endif