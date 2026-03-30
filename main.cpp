#include "top-it-vector.hpp"
#include <iostream>
#include <iomanip>
#include <utility>
#include <initializer_list>
#include "top-it-iterator.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testSizeOfVector()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v.getSize() == 2;
}

bool testCapacityOfVector()
{
  topit::Vector< int > v;
  bool res = v.getCapacity() == 0;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  res = res && v.getCapacity() == 8;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  return res && v.getCapacity() == 16;
}

bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  bool res = v[0] == 1;
  v.pushBack(2);
  return res && v[1] == 2;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  return v[0] == 1 && v.getSize() == 1 && v.getCapacity() == 8;
}

bool testElementInboundAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
    int& val = v.at(0);
    return val == 1;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  } catch(...)
  {
    return false;
  }
}

bool testElementInboundConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int >& rv = v;
  try
  {
    const int& val = rv.at(0);
    return val == 1;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  } catch(...)
  {
    return false;
  }
}

bool testCopyConstructorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav = v;
  return v == yav;
}

bool testCopyConstructorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  return v == yav;
}

bool testCopyOperatorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav;
  yav = v;
  return v == yav;
}

bool testCopyOperatorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav;
  yav = v;
  return v == yav;
}

bool testMoveConstructorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav(std::move(v));
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}

bool testInitializerList()
{
  topit::Vector< int > v({1, 2});
  return v.getSize() == 2 && (v[0] == 1) && (v[1] == 2);
}

bool testMoveConstructorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav(std::move(v));
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}


bool testMoveOperatorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav;
  yav = std::move(v);
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}

bool testMoveOperatorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav;
  yav = std::move(v);
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}

bool testBegin()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  topit::VecIter< int > it = v.begin();
  return *(it) == 1;
}

bool testConstBegin()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  topit::VecConstIter< int > it = v.cbegin();
  return *(it) == 1;
}

bool testEnd()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  topit::VecIter< int > it = --v.end();
  return *(it) == 3;
}

bool testConstEnd()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  topit::VecConstIter< int > it = --v.cend();
  return *(it) == 3;
}

bool testInsertElementIntoEmptyVector()
{
  topit::Vector< int > v;
  v.insert(3, 4);

  return v.getSize() == 4 && v.getCapacity() == 8 && v[3] == 4;
}

bool testInsertElementIntoNonEmptyVector()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.insert(1, 4);
  return v[0] == 1 && v[1] == 4 && v[2] == 2 && v[3] == 3;
}

bool testInsertFewElementsIntoEmptyVector()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  topit::Vector< int > yav;
  yav.insert(v, 0, 3, 0);

  return yav[0] == 1 && yav[1] == 2 && yav[2] == 3;
}

bool testInsertFewElementsIntoNonEmptyVector()
{
  topit::Vector< int > v;
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);

  topit::Vector< int > yav;
  yav.pushBack(1);
  yav.pushBack(5);
  yav.pushBack(6);

  yav.insert(v, 0, 3, 1);

  return yav[0] == 1 && yav[1] == 2 && yav[2] == 3 && yav[3] == 4 && yav[4] == 5 && yav[5] == 6;
}

bool testInsertElementWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  topit::VecIter< int > it = v.begin();
  v.insert(it, 4);
  return v[0] == 4;
}

bool testInsertSameElementsWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  topit::VecIter< int > it = v.begin();
  v.insert(it, 3, 4);
  return v[0] == 4 && v[1] == 4 && v[2] == 4;
}

bool testInsertElementsFromAnotherVecWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(4);
  v.pushBack(5);
  v.pushBack(6);

  topit::Vector< int > yav;
  yav.pushBack(1);
  yav.pushBack(2);
  yav.pushBack(3);

  topit::VecIter< int > it = v.begin();
  v.insert(it, yav.begin(), yav.end());
  return v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testEraseElementInEmpyVector()
{
  topit::Vector< int > v;
  v.erase(0);
  topit::Vector< int > yav;
  return v == yav;
}

bool testEraseElementInNonEmpyVector()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(0);
  v.erase(2);
  return v[0] == 2;
}

bool testEraseFewElementsInEmpyVector()
{
  topit::Vector< int > v;
  v.erase(0, 4);
  topit::Vector< int > yav;
  return v == yav;
}

bool testEraseFewElementsInNonEmpyVector()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  v.erase(1, 3);
  bool res = v[0] == 1 && v[2] == 4 && v[3] == 5;
  v.erase(0, 2);
  return res && v[0] == 3;
}

bool testEraseElementWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(v.begin());
  return v[0] == 2 && v[1] == 3;
}


bool testEraseFewElementsWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  v.pushBack(6);

  v.erase(v.begin(), 3);
  return v[0] == 4 && v[1] == 5 && v[2] == 6;
}

bool testEraseRangeOfElementsWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  v.pushBack(6);

  topit::VecIter< int > itS = v.begin();
  topit::VecIter< int > itE = ++(++(++v.begin()));
  v.erase(itS, itE);
  return v[0] == 3 && v[1] == 4 && v[2] == 5;
}


int main()
{
  using test_t = std::pair< const char *, bool(*)() > ;
  test_t tests[] = {
    { "Empty vector", testEmptyVector },
    { "Size of vector", testSizeOfVector },
    { "Capacity of vector", testCapacityOfVector },
    { "Push value to the back", testPushBack },
    { "Pop value from back", testPopBack },
    { "Inbound access", testElementInboundAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Inbound const access", testElementInboundConstAccess },
    { "Out of bound const access", testElementOutOfBoundConstAccess },
    { "Copy constructor for empty vector", testCopyConstructorforEmpty },
    { "Copy constructor for non empty vector", testCopyConstructorforNonEmpty },
    { "Copy operator for empty vector", testCopyOperatorforEmpty },
    { "Copy operator for non empty vector", testCopyOperatorforNonEmpty },
    { "Move constructor for empty vector", testMoveConstructorforEmpty },
    { "Move constructor for non empty vector", testMoveConstructorforNonEmpty },
    { "Move operator for empty vector", testMoveOperatorforEmpty },
    { "Move operator for non empty vector", testMoveOperatorforNonEmpty },
    { "Non-empty vector for non-empty initializer list", testInitializerList},
    { "Begin of the vector", testBegin},
    { "Const begin of the vector", testConstBegin},
    { "End of the vector", testEnd},
    { "Const end of the vector", testConstEnd},
    { "Insert element into empty vector", testInsertElementIntoEmptyVector},
    { "Insert element into non empty vector", testInsertElementIntoNonEmptyVector},
    { "Insert few elements into empty vector", testInsertFewElementsIntoEmptyVector},
    { "Insert few elements into non empty vector", testInsertFewElementsIntoNonEmptyVector},
    { "Insert element with iterator", testInsertElementWithIterator},
    { "Insert same elements with iterator", testInsertSameElementsWithIterator},
    { "Insert elements from another vector with iterator", testInsertElementsFromAnotherVecWithIterator},
    { "Erase element in empty vector", testEraseElementInEmpyVector},
    { "Erase element in non empty vector", testEraseElementInNonEmpyVector},
    { "Erase few elements in empty vector", testEraseFewElementsInEmpyVector},
    { "Erase few elements in non empty vector", testEraseFewElementsInNonEmpyVector},
    { "Erase element with iterator", testEraseElementWithIterator},
    { "Erase few elements with iterator", testEraseFewElementsWithIterator},
    { "Erase range of elements with iterator", testEraseRangeOfElementsWithIterator},
  };
  std::cout << "TESTS\n";
  const size_t count = sizeof(tests) / sizeof(test_t);
  bool pass = true;
  size_t countFailedTests = 0;
  size_t countSuccessTests = 0;
  for (size_t i = 0; i < count; ++i)
  {
    std::cout << std::boolalpha;
    bool res = tests[i].second();
    if (res)
    {
      countSuccessTests++;
    } else
    {
      std::cout << i + 1 << ". " << tests[i].first << ": " << res << '\n';
      countFailedTests++;
    }
    pass = pass && res;
  }

  std::cout << "Successful tests: " << countSuccessTests << '\n';
  std::cout << "Failed tests: " << countFailedTests << '\n';
  std::cout << "RESULT: " << pass << '\n';
}