#include <iostream>
using namespace std;

void doSomething(int a, int& b, int* c, int* d);

int main() {
  int a = 5;
  int b = 5;
  int* c = &a;
  int* d = &b;
  cout << *c << " " << *d << endl;
  doSomething(a, b, c, d);
  // Prints 5 12
  cout << *c << " " << *d << endl;
  return 0;
}

void doSomething(int a, int& b, int* c, int* d) {
  a = 12;
  b = 12;
  c = &a;
  d = &b;
}
