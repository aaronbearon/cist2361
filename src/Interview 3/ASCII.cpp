// Aaron Blum
// CIST2361: C++ Programming I (48267)
// InterviewIII: ASCII.cpp 04/30/2026
// This program takes a character from the user and prints out its ASCII code.
#include <iostream>
#include <string>
using namespace std;

//// Function Prototypes
void runProgram(bool* again);
char getInput(bool* again);
bool isValidInput(string answerStr, char* key, bool* again);
int getAsciiCode(char key);
void printAsciiCode(char key, int code);

//// Implementation
int main() {
  // Declare a boolean to loop through until false.
  bool repeat = true;
  while (repeat) {
    // Pass it in as a pointer for necessary modification.
    runProgram(&repeat);
  }
  return 0;
}

// Call other functions from here.
void runProgram(bool* again) {
  char key = getInput(again);
  // The again bool may be modified in the getInput branch.
  // If it becomes false, the main loop is over.
  if (!*again) {
    return;
  }
  int code = getAsciiCode(key);
  printAsciiCode(key, code);
}

char getInput(bool* again) {
  // Declare these first.
  string answer = "";
  char input = ' ';
  while (true) {
    cout << "Please enter a character";
    cout << " (or EXIT to exit): ";
    getline(cin, answer);
    // Only "returns" out of the while loop if the input is valid.
    // EXIT allows the input to be valid (the char isn't updated).

    // In the EXIT case, the boolean has become false.
    // So in that case, it returns and the program ends.
    if (isValidInput(answer, &input, again)) {
      return input;
    } else {
      // Error message happens if the input is invalid.
      cout << "Error, only single character";
      cout << " in ASCII range of 32-127 allowed." << endl;
      cout << endl;
    }
  }
}

// This function passes in two pointers.
bool isValidInput(string answerStr, char* input, bool* again) {
  // Controlled exit
  if (answerStr == "EXIT") {
    *again = false;
    return true;
  }

  // Validation check.
  if (answerStr.length() == 1) {
    *input = answerStr[0];
    if (*input >= 32 && *input <= 127) {
      return true;
    }
  }

  return false;
}

// Obtain the ASCII code.
int getAsciiCode(char key) {
  // Cast to an int and return it.
  return (int)key;
}

// Print out the ASCII code.
// Test Examples below:
/*

A = 65
z = 122
5 = 53
@ = 64
space character = 32
multiple characters such as ABC: invalid
empty input: invalid

*/
void printAsciiCode(char key, int code) {
  cout << "ASCII code for char '" << key << "': " << code << "." << endl;
}
