
#include <iostream>
#include "func.hpp"

string getInput(string message)
{
  std::cout << message << std::endl;
  string response;
  std::cin >> response;
  return response;
}