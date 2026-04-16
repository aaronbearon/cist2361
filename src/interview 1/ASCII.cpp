// Aaron Blum
// CIST2361: Interview 1
// 04/16/2026
// This program prints letters and their ASCII values.

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

void printMenu();
void DisplayUppercaseASCII();
void DisplayLowercaseASCII();
bool runTopMenu();
bool isValidInt(string answerStr, int& answer);

int main() {
  // Keep going until user selects exit.
  while (runTopMenu());
  return 0;
}

void printMenu() {
  cout << endl;
  cout << "----------------------------------------------" << endl;
  cout << "Please select one of the options (1-3) below:" << endl;
  cout << endl;
  cout << "MENU" << endl;
  cout << "1. Uppercase Letters and ASCII" << endl;
  cout << "2. Lowercase Letters and ASCII" << endl;
  cout << "3. Exit" << endl;
  cout << "----------------------------------------------" << endl;
}

bool runTopMenu() {
  printMenu();
  // Pass a string into the "validator" function.
  string choice;
  cout << "Enter your choice: ";
  getline(cin, choice);
  int answer = 0;
  if (!isValidInt(choice, answer)) {
    // This error message is for a completly illegal int.
    cout << "Error, invalid int. Please try again." << endl;
    return true;
  }

  // A switch statement works well for a menu driven program.
  switch (answer) {
    case 1:
      DisplayUppercaseASCII();
      return true;
    case 2:
      DisplayLowercaseASCII();
      return true;
    case 3:
      return false;
    default:
      // This error message is for a legal int that is not 1-3.
      cout << "Invalid choice. Please try again." << endl;
      return true;
  }
}

// This is how you implement the try-catch block.
// It's called from the menu selection.
bool isValidInt(string answerStr, int& answer) {
  try {
    answer = stoi(answerStr);
    return true;
  } catch (const invalid_argument& e) {
    return false;
  }
}

// Use static_cast to convert a char to int.
// The int version becomes the char's ASCII value.
void DisplayUppercaseASCII() {
  cout << "Uppercase letters and their ASCII values:" << endl;
  for (char c = 'A'; c <= 'Z'; c++) {
    cout << c << " = " << static_cast<int>(c) << endl;
  }
}

// Same here but with lowercase letters.
void DisplayLowercaseASCII() {
  cout << "Lowercase letters and their ASCII values:" << endl;
  for (char c = 'a'; c <= 'z'; c++) {
    cout << c << " = " << static_cast<int>(c) << endl;
  }
}
