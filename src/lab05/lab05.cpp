// Aaron Blum
// CIST2361: Lab 05
// 02/17/2026
// This program is another math tutor.

#include <cmath>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
using namespace std;

void printMenu() {
  cout << "Please select one of the options (1-6) below:" << endl;
  cout << endl;
  cout << "1. Modulus (Remainder)" << endl;
  cout << "2. Addition" << endl;
  cout << "3. Multiplication" << endl;
  cout << "4. Division (Integer division (math floor))" << endl;
  cout << "5. Subtraction (Answer can't be negative)" << endl;
  cout << "6. Exit the program" << endl;
}

void makeRandomNumber(int min, int max, int& n) {
  n = rand() % (max - min + 1) + min;
}

// This is how you implement the try-catch block.
// It's called from the menu selection.
// It's also used to validate the user's answer to a problem.
bool isValidInput(string answerStr, int& answer) {
  try {
    answer = stoi(answerStr);
    return answer >= 0;  // don't allow negative numbers
  } catch (const invalid_argument& e) {
    return false;
  } catch (const out_of_range& e) {
    return false;
  }
}

// Return false if the user is trying to exit the problem; otherwise true to
//  continue this operation type.
bool checkAnswer(int a, int b, int expect, string operation) {
  // Loop until the user enters a valid response.
  while (true) {
    cout << "What is the " << operation << " of " << a << " and " << b << "? "
         << endl;
    string answerStr;  // Must read a string because 'm' is a valid option.
    cin >> answerStr;

    if (answerStr == "m") {
      return false;  // Exit to main menu
    }

    int answer;
    if (isValidInput(answerStr, answer)) {
      if (answer == expect) {
        cout << "Correct!" << endl;
      } else {
        cout << "Wrong!" << endl;
      }

      return true;  // keep going with the next problem
    } else {
      cout << "Error, you must enter either a positive integer answer, ";
      cout << "or a lowercase m to return to the menu." << endl;
    }
  }
}

// Five operation functions below
void modulus() {
  while (true) {
    int a, b;
    makeRandomNumber(0, 99, a);
    makeRandomNumber(1, 99, b);
    int expect = a % b;

    if (!checkAnswer(a, b, expect, "modulus")) {
      return;
    }
  }
}

void addition() {
  while (true) {
    int a, b;
    makeRandomNumber(0, 99, a);
    makeRandomNumber(0, 99, b);
    int expect = a + b;
    if (!checkAnswer(a, b, expect, "sum")) {
      return;
    }
  }
}

void multiplication() {
  while (true) {
    int a, b;

    // This is basically a 1 or a 0 for true or false.
    if (rand() % 2) {
      makeRandomNumber(0, 9, a);
      makeRandomNumber(0, 99, b);
    } else {
      makeRandomNumber(0, 99, a);
      makeRandomNumber(0, 9, b);
    }

    int expect = a * b;
    if (!checkAnswer(a, b, expect, "product")) {
      return;
    }
  }
}

// This is integer division
void division() {
  while (true) {
    int a, b;
    makeRandomNumber(0, 99, a);

    // No division by zero
    makeRandomNumber(1, 99, b);
    int expect = a / b;
    if (!checkAnswer(a, b, expect, "integer division")) {
      return;
    }
  }
}

void subtraction() {
  while (true) {
    int a, b;
    makeRandomNumber(0, 99, a);
    makeRandomNumber(0, 99, b);
    // Answer can't be negative
    if (a < b) {
      int temp = a;
      a = b;
      b = temp;
    }

    int expect = a - b;
    if (!checkAnswer(a, b, expect, "difference")) {
      return;
    }
  }
}

bool runTopMenu() {
  printMenu();
  string choice;
  cin >> choice;
  int intSelection;

  // Specifically handle mismatched data and disallowed numbers.
  if (isValidInput(choice, intSelection) && intSelection >= 1 &&
      intSelection <= 6) {
    if (intSelection == 6) {
      return false;
    }

    switch (intSelection) {
      case 1:
        modulus();
        break;
      case 2:
        addition();
        break;
      case 3:
        multiplication();
        break;
      case 4:
        division();
        break;
      case 5:
        subtraction();
        break;
    }
  } else {
    cout << "That's not one of the 6 options. Please try again." << endl;
  }

  return true;
}

int main() {
  // Seed once, use later
  srand(time(0));

  while (runTopMenu());
}
