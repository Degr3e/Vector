#include "top-it-vector.hpp"
#include <iostream>
#include <stdexcept>

bool testEmptyVector()
{
  using namespace topit;
  Vector< int > v;
  return v.isEmpty();
}

bool testElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
    int & val = v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementConstAccess()
{
  topit::Vector< int > v;
  const topit::Vector< int > & rv = v;
  v.pushBack(1);
  try
  {
    const int & val = rv.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementsOutOfBoundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementsOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testPushBackSizeAndCapacity()
{
  topit::Vector< int > v;
  if (v.getSize() != 0 || v.getCapacity() != 0)
  {
    return false;
  }
  v.pushBack(10);
  if (v.getSize() != 1 || v.getCapacity() != 1 || v[0] != 10)
  {
    return false;
  }
  v.pushBack(20);
  if (v.getSize() != 2 || v.getCapacity() != 2 || v[1] != 20)
  {
    return false;
  }
  v.pushBack(30);
  return v.getSize() == 3 && v.getCapacity() == 4 && v[2] == 30;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.popBack();
  if (!v.isEmpty())
  {
    return false;
  }
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  if (v.getSize() != 1 || v[0] != 1)
  {
    return false;
  }
  v.popBack();
  return v.isEmpty();
}

bool testInsertMiddle()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertOutOfRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
    v.insert(2, 99);
    return false;
  }
  catch (const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testErase()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool testEraseOutOfRange()
{
  topit::Vector< int > v;
  try
  {
    v.erase(0);
    return false;
  }
  catch (const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  v.pushBack(7);
  v.pushBack(8);
  topit::Vector< int > copy(v);
  v[0] = 100;
  return copy.getSize() == 2 && copy[0] == 7 && copy[1] == 8;
}

bool testCopyAssignment()
{
  topit::Vector< int > src;
  src.pushBack(11);
  src.pushBack(22);
  topit::Vector< int > dst;
  dst.pushBack(5);
  dst = src;
  src[0] = 99;
  return dst.getSize() == 2 && dst[0] == 11 && dst[1] == 22;
}

bool testMoveConstructor()
{
  topit::Vector< int > src;
  src.pushBack(4);
  src.pushBack(5);
  topit::Vector< int > moved(static_cast< topit::Vector< int >&& >(src));
  return moved.getSize() == 2 && moved[0] == 4 && moved[1] == 5 && src.getSize() == 0;
}

bool testMoveAssignment()
{
  topit::Vector< int > src;
  src.pushBack(40);
  src.pushBack(50);
  topit::Vector< int > dst;
  dst.pushBack(1);
  dst = static_cast< topit::Vector< int >&& >(src);
  return dst.getSize() == 2 && dst[0] == 40 && dst[1] == 50 && src.getSize() == 0;
}

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests [] =
  {
    { "Empty vector", testEmptyVector},
    { "Inbound access", testElementAccess},
    { "Out of bound access", testElementsOutOfBoundAccess},
    { "Inbound const access", testElementConstAccess},
    { "Out of bound const access", testElementsOutOfBoundConstAccess},
    { "Push back, size, capacity", testPushBackSizeAndCapacity},
    { "Pop back", testPopBack},
    { "Insert middle", testInsertMiddle},
    { "Insert out of range", testInsertOutOfRange},
    { "Erase element", testErase},
    { "Erase out of range", testEraseOutOfRange},
    { "Copy constructor", testCopyConstructor},
    { "Copy assignment", testCopyAssignment},
    { "Move constructor", testMoveConstructor},
    { "Move assignment", testMoveAssignment},
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
}