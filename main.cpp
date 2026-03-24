#include "top-it-vector.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

bool testEmptyVector()
{
  std::cout << __func__ << std::endl;
  using namespace topit;
  Vector< int > v;
  return v.isEmpty();
}

bool TestElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try{
    int & val = v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementsOutOfBoundAcces()
{
  topit::Vector< int > v;
  try{
    int & val = v.at(0);
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

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests [] =
  {
    { "Empty vector", testEmptyVector},
    { "Indbound access", TestElementAccess},
    { "Out of bound access", testElementsOutOfBoundAcces},
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second;
    std::cout << tests[i].first << ": " << tests[i].second() << "\n";
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
  //подсчет сколько пройденыйх/не пройденых
  //выводить только непрошедшие тесты
  //невывводить вовсе если прошло
}