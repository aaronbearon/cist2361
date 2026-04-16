#include <iostream>
using namespace std;

void exampleFunction(int x, int y, int& a, int& b, int*& aa, int* bb);

int main() {
  int a = 10;
  int* ptr1 = &a;
  int* ptr2 = &a;
  int b = 20;

  exampleFunction(1, 2, a, b, ptr1, ptr2);
  cout << *ptr1 << " " << *ptr2 << endl;

  return 0;
}

void exampleFunction(int x, int y, int& a, int& b, int*& aa, int* bb) {
  int z = 78;
  aa = &b;
  bb = &b;
}
