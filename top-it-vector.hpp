#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
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

    void pushBack(const T&);
    void popBack();
    void insert(size_t, const T&);
    void earse(size_t);
  private:
    T* data_;
    size_t size_, capacity_;
  };
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
#endif