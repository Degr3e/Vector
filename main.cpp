#include "top-it-vector.hpp"
#include <iostream>
#include <iomanip>

bool testEmptyVector()
{
  using namespace topit;
  Vector< int > v;
  return v.isEmpty();
}

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests [] = 
  {
    { "Empty vector", testEmptyVector}
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
}