#include <boost/format.hpp>
#include <iostream>

int main() {
  boost::format f("Hello, %1%!");
  std::cout << f % "World" << std::endl;
}
