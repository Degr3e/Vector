#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <stdexcept>
#include <utility>
namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    ~Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void pushBack(const T&);
    void popBack();
    void insert(size_t, const T&);
    void erase(size_t);
    void earse(size_t);
  private:
    T* data_;
    size_t size_, capacity_;
  };
  template < class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}
template< class T >
bool topit::operator==(const Vector<T> &lhs, const Vector<T> &rhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for(size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}


template< class T >
T& topit::Vector< T >::at(size_t id)
{
  return const_cast< T& >(static_cast< const Vector< T >* >(this)->at(id));
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if(id < getSize())
  {
    return data_[id];
  }
  throw std::out_of_range("Vector::at bad id");
}

template< class T >
void topit::Vector< T >::pushBack(const T& value)
{
  if (size_ == capacity_)
  {
    size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size_; ++i)
    {
      newData[i] = std::move(data_[i]);
    }
    delete [] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }
  data_[size_] = value;
  ++size_;
}
template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  return data_[id];
}
template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
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
void topit::Vector< T >::popBack()
{
  if (size_ > 0)
  {
    --size_;
  }
}



template< class T >
topit::Vector< T >::~Vector()
{
  delete [] data_;
}
template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
template< class T >
topit::Vector< T >::Vector(const Vector& other):
  data_(nullptr),
  size_(other.size_),
  capacity_(other.capacity_)
{
  if (capacity_ != 0)
  {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i] = other.data_[i];
    }
  }
}
template< class T >
topit::Vector< T >::Vector(Vector&& other):
  data_(other.data_),
  size_(other.size_),
  capacity_(other.capacity_)
{
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}
template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector& other)
{
  if (this == &other)
  {
    return *this;
  }
  T* newData = nullptr;
  if (other.capacity_ != 0)
  {
    newData = new T[other.capacity_];
    for (size_t i = 0; i < other.size_; ++i)
    {
      newData[i] = other.data_[i];
    }
  }
  delete [] data_;
  data_ = newData;
  size_ = other.size_;
  capacity_ = other.capacity_;
  return *this;
}
template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector&& other)
{
  if (this == &other)
  {
    return *this;
  }
  delete [] data_;
  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
  return *this;
}
template< class T >
void topit::Vector< T >::insert(size_t id, const T& value)
{
  if (id > size_)
  {
    throw std::out_of_range("Vector::insert bad id");
  }
  if (size_ == capacity_)
  {
    size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < id; ++i)
    {
      newData[i] = std::move(data_[i]);
    }
    newData[id] = value;
    for (size_t i = id; i < size_; ++i)
    {
      newData[i + 1] = std::move(data_[i]);
    }
    delete [] data_;
    data_ = newData;
    capacity_ = newCapacity;
    ++size_;
    return;
  }
  for (size_t i = size_; i > id; --i)
  {
    data_[i] = std::move(data_[i - 1]);
  }
  data_[id] = value;
  ++size_;
}
template< class T >
void topit::Vector< T >::erase(size_t id)
{
  if (id >= size_)
  {
    throw std::out_of_range("Vector::erase bad id");
  }
  for (size_t i = id; i + 1 < size_; ++i)
  {
    data_[i] = std::move(data_[i + 1]);
  }
  --size_;
}
template< class T >
void topit::Vector< T >::earse(size_t id)
{
  erase(id);
}
#endif