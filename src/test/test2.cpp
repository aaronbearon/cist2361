#include <iostream>
using namespace std;

void modify(int* a, int* b);

int main() {
  int x = 33;
  int y = 89;
  int* xr = &x;
  int* yr = &y;
  modify(xr, yr);
  cout << x << " " << y << endl;
  return 0;
}

void modify(int* a, int* b) {
  *a = 44;
  a = b;
  *a = 55;
}
