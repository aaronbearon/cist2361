#include <conio.h>  // Only for Windows

#include <iomanip>
#include <iostream>
#include <random>
using namespace std;

void getRandomNumbers(int& a, int& b) {
  random_device myEngine;
  uniform_int_distribution<int> randomInt(0, 1000);
  a = randomInt(myEngine);
  b = randomInt(myEngine);
  a = 6;
  b = 996;
}

int countDigits(int n) {
  // Each number always has one digit.
  for (int i = 1; true; i++) {
    // Do this before checking so that 0 and
    // all single-digit numbers divide out to zero.
    n /= 10;
    if (n == 0) {
      return i;
    }
  }
}

void printProblem(int a, int b, int width) {
  cout << " " << setw(width) << a << endl;  // 300
  cout << "+" << setw(width) << b << endl;  //+100
  cout << string(width + 1, '-') << endl;   //----
}

void printSolution(int a, int b, int width) {
  int sum = a + b;

  // extra width on the sum (no leading space or plus)
  cout << setw(width + 1) << sum << endl;
}

int main() {
  cout << "When you're ready, press any key to reveal the answer." << endl;
  int num1, num2;
  getRandomNumbers(num1, num2);

  // Sets the field width based on the number with more digits.
  int fieldWidth = max(countDigits(num1), countDigits(num2));

  printProblem(num1, num2, fieldWidth);

  // Any key can be used like the enter key.
  // Only for Windows
  _getch();

  printSolution(num1, num2, fieldWidth);
  return 0;
}
