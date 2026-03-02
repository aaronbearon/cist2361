#include <iostream>
using namespace std;

int loop(int);

int main() {
  cout << loop(0) << endl;
  return 0;
}

int loop(int num) {
  if (num < 9) {
    return loop(num + 1) + num;
  } else {
    return num;
  }
}
