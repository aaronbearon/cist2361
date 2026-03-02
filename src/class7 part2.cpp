// array::max_size
#include <array>
#include <iostream>

int main() {
  std::array<int, 5> myints;
  std::cout << "size of myints: " << myints.size() << '\n';
  std::cout << "max_size of myints: " << myints.max_size() << '\n';
  return 0;
}
