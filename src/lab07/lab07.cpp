#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

bool runTopMenu();
void printMenu();
void writeData();
void readData();
string getFileName(const string&);
double computeLowest();
double computeHighest();
double computeSum();
double computeAverage();
void printResult(string label, double value);
bool isValidMainMenuInput(string, int&);
bool isValidDouble(string, double&);

const int MAX_SIZE = 10;
double arr[MAX_SIZE];
int arrSize;
const string ERROR_NO_DATA = "No data: please load data first!";
const string OUT_FILE_MESSAGE = "write to";
const string IN_FILE_MESSAGE = "read from";

int main() {
  // Run everything from here.
  arrSize = 0;
  while (runTopMenu());
  return 0;
}

bool runTopMenu() {
  printMenu();
  cout << "? ";

  string choice;
  getline(cin, choice);

  // Specifically handle mismatched data and disallowed numbers.
  int intSelection;
  if (!isValidMainMenuInput(choice, intSelection)) {
    cout << "That's not one of the 7 options. Please try again." << endl;
    return true;
  }

  if (intSelection >= 3 && intSelection <= 6 && arrSize == 0) {
    cout << ERROR_NO_DATA << endl;
    return true;
  }

  switch (intSelection) {
    case 1:
      writeData();
      return true;
    case 2:
      readData();
      return true;
    case 3:
      printResult("Lowest", computeLowest());
      return true;
    case 4:
      printResult("Highest", computeHighest());
      return true;
    case 5:
      printResult("Sum", computeSum());
      return true;
    case 6:
      printResult("Average", computeAverage());
      return true;
    case 7:
      return false;
    default:
      assert(false);  // should never get here
      return false;
  }
}

void printMenu() {
  cout << endl;
  cout << "----------------------------------------------" << endl;
  cout << "Please select one of the options (1-7) below:" << endl;
  cout << endl;
  cout << "1. Create a data file (user enters up to N numbers and the program "
          "saves them)"
       << endl;
  cout << "2. Load numbers from a file into the array (up to N numbers)"
       << endl;
  cout << "3. Display the lowest number (analysis)" << endl;
  cout << "4. Display the highest number (analysis)" << endl;
  cout << "5. Display the total of the numbers (analysis)" << endl;
  cout << "6. Display the average of the numbers (analysis)" << endl;
  cout << "7. Exit" << endl;
  cout << "----------------------------------------------" << endl;
}

// Data from keyboard to output file
void writeData() {
  string filename = getFileName(OUT_FILE_MESSAGE);

  ofstream outFile;  // no close needed, use function scope destructor
  outFile.open(filename);
  if (!outFile) {
    cout << "Failed to open file." << endl;
    return;
  }

  cout << "Please enter up to " << MAX_SIZE << " numbers. (q to quit)" << endl;
  cout << "Writing data to file..." << endl;
  int count;
  // Only 10 numbers...
  for (count = 0; count < MAX_SIZE; count++) {
    cout << "#" << count + 1 << ": ";
    string answerStr;
    getline(cin, answerStr);
    // or less
    if (answerStr == "q") {
      break;  // Exit to main menu
    }

    double num;
    if (isValidDouble(answerStr, num)) {  // do stuff, test
      outFile << num << endl;
    } else {
      cout << "Error, invalid number, try again." << endl;
      // Try again with bad input detected.
      count--;
    }
  }

  cout << count << " number(s) written to file successfully." << endl;
}

// Data from input file to global array
void readData() {
  // Reset this with any attempt to read from file.
  // Note: instructions say to reset the global array.
  // This implementation is logically equivalent.
  arrSize = 0;

  string filename = getFileName(IN_FILE_MESSAGE);

  ifstream inFile;  // no close needed, use function scope destructor
  inFile.open(filename);
  if (!inFile) {
    cout << "Failed to open file." << endl;
    return;
  }

  cout << "Reading from file to array..." << endl;
  string answerStr;
  for (int count = 0; count < MAX_SIZE; count++) {
    // Stops at file end
    if (!getline(inFile, answerStr)) {
      break;
    }

    double num;
    // The entire intended part of the file must be valid
    if (!isValidDouble(answerStr, num)) {
      cout << "File has invalid data." << endl;
      arrSize = 0;  // clear out any invalid data
      return;
    }

    arr[count] = num;
    arrSize++;
  }

  cout << arrSize << " number(s) read from file successfully." << endl;
}

string getFileName(const string& message) {
  string filename;
  while (true) {
    cout << "What file do you want to " << message << "?" << endl;
    cout << "Please enter the filename below." << endl;
    getline(cin, filename);
    if (filename.empty()) {
      cout << "Filename can't be empty" << endl;
    } else {
      return filename;
    }
  }
}

// The four functions below are based only on the array elements with file data.

// Smallest
double computeLowest() {
  double min = 0;
  for (int i = 0; i < arrSize; i++) {
    if (i == 0 || min > arr[i]) {
      min = arr[i];
    }
  }
  return min;
}

// Largest
double computeHighest() {
  double max = 0;
  for (int i = 0; i < arrSize; i++) {
    if (i == 0 || max < arr[i]) {
      max = arr[i];
    }
  }
  return max;
}

// Total
double computeSum() {
  double sum = 0;
  for (int i = 0; i < arrSize; i++) {
    sum += arr[i];
  }
  return sum;
}

// Average
double computeAverage() {
  double sum = computeSum();
  double avg = sum / arrSize;
  return avg;
}

// Display the result with a label.
void printResult(string label, double value) {
  cout << label << ": " << value << endl;
}

// This is how you implement the try-catch block.
// It's called from the menu selection.
bool isValidMainMenuInput(string answerStr, int& answer) {
  try {
    answer = stoi(answerStr);
    return answer >= 1 && answer <= 7;
  } catch (const invalid_argument& e) {
    return false;
  } catch (const out_of_range& e) {
    return false;
  }
}

// This is how you implement the try-catch block.
// It's called from user numeric inputs.
bool isValidDouble(string answerStr, double& answer) {
  try {
    answer = stod(answerStr);
    return true;
  } catch (const invalid_argument& e) {
    return false;
  } catch (const out_of_range& e) {
    return false;
  }
}
