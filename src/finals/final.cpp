#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

const int SIZE = 12;
const string MONTHS[SIZE] = {"January",   "February", "March",    "April",
                             "May",       "June",     "July",     "August",
                             "September", "October",  "November", "December"};

struct Expense {
  int month;
  string category;
  double amount;
  double budgeted;
};

struct MonthlySummary {
  int month;
  double totalActual;
  double totalBudgeted;
};

// Function prototypes
bool parseLine(const string& line, Expense* record);
// bool parseFirstLine(const string& line, int* userMonth);
void processFile(const string& filename);
void sortArray(MonthlySummary summaries[], bool ascending);
void swapItems(MonthlySummary* a, MonthlySummary* b);

int main() {
  const string filename = "expenses.txt";
  processFile(filename);

  return 0;
}

/**
 * Attempts to parse a single line into a DataRecord struct.
 * Uses try-catch to handle mismatched datatypes.
 */
bool parseLine(const string& line, Expense* record) {
  stringstream ss(line);
  vector<string> tokens;
  string temp;

  // Split the line into individual words (tokens)
  while (ss >> temp) {
    tokens.push_back(temp);
  }

  // Check if we have exactly 4 pieces of data
  if (tokens.size() != 4) {
    return false;
  }

  try {
    // Attempt conversions - these throw exceptions if they fail
    record->month = stoi(tokens[0]);
    record->category = tokens[1];
    record->amount = round(stod(tokens[2]) * 100) / 100.0;
    record->budgeted = round(stod(tokens[3]) * 100) / 100.0;
    // Negatives aren't allowed
    if (record->amount < 0 || record->budgeted < 0) {
      return false;
    }
    return true;
  } catch (const invalid_argument& e) {
    return false;
  } catch (const out_of_range& e) {
    return false;
  }
}

// bool parseFirstLine(const string& line, int* userMonth) {
//   if (line.empty()) {
//     return false;
//   }

//   stringstream ss(line);
//   vector<string> tokens;
//   string temp;

//   // Split the line into individual words (tokens)
//   while (ss >> temp) {
//     tokens.push_back(temp);
//   }

//   if (tokens.size() != 1) {
//     return false;
//   }

//   try {
//     // Attempt conversions - these throw exceptions if they fail
//     *userMonth = stoi(tokens[0]);
//     if (*userMonth >= 1 && *userMonth <= 12) {
//       return true;
//     } else {
//       return false;
//     }
//   } catch (const invalid_argument& e) {
//     return false;
//   } catch (const out_of_range& e) {
//     return false;
//   }
// }

// Handles file opening and iterates through each line.
void processFile(const string& filename) {
  ifstream inputFile(filename);
  vector<Expense> validRecords;
  MonthlySummary summaries[SIZE];
  for (int i = 0; i < 12; i++) {
    summaries[i].month = i + 1;
    summaries[i].totalActual = 0;
    summaries[i].totalBudgeted = 0;
  }

  if (!inputFile.is_open()) {
    cout << "Fail: Could not open " << filename << endl;
    return;
  }

  string line;
  // int userMonth;
  // int* ptrMonth = &userMonth;
  // if (getline(inputFile, line)) {
  //   if (!parseFirstLine(line, ptrMonth)) {
  //     cout << "Error, invalid first entry." << endl;
  //     exit(EXIT_FAILURE);
  //   }
  // }

  while (getline(inputFile, line)) {
    // If the line is just a trailing newline/empty, we skip it
    if (line.empty()) continue;

    Expense tempRecord;
    Expense* ptrRecord = &tempRecord;
    if (parseLine(line, ptrRecord)) {
      validRecords.push_back(tempRecord);
      summaries[tempRecord.month - 1].totalActual += tempRecord.amount;
      summaries[tempRecord.month - 1].totalBudgeted += tempRecord.budgeted;
    } else {
      cout << "Error, invalid line." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << fixed << showpoint << setprecision(2);
  cout << "=== Monthly Totals and Monthly Budgets (Unsorted) ===" << endl;
  int actualSum = 0;
  int budgetedSum = 0;
  for (int i = 0; i < SIZE; i++) {
    cout << MONTHS[summaries[i].month - 1] << ": ";
    actualSum += summaries[i].totalActual;
    budgetedSum += summaries[i].totalBudgeted;
    cout << "$" << summaries[i].totalActual << ", $"
         << summaries[i].totalBudgeted << endl;
  }

  cout << endl;
  cout << "=== Monthly Totals (Ascending) ===" << endl;
  sortArray(summaries, true);
  for (int i = 0; i < SIZE; i++) {
    cout << MONTHS[summaries[i].month - 1] << ": ";
    cout << "$" << summaries[i].totalActual << endl;
  }

  cout << endl;
  cout << "=== Monthly Totals (Descending) ===" << endl;
  sortArray(summaries, false);
  for (int i = 0; i < SIZE; i++) {
    cout << MONTHS[summaries[i].month - 1] << ": ";
    cout << "$" << summaries[i].totalActual << endl;
  }

  cout << endl;
  cout << "Month with highest amount spent: " << MONTHS[summaries[0].month - 1] << endl;
  cout << "Total spent: $" << actualSum << endl;
  cout << "Total budgeted: $" << budgetedSum << endl;

  // TODO: Sort the array with actual amounts spent.

  cout << endl;

  inputFile.close();

  // TOTAL GARBAGE FROM GEMINI:
  // Optional: Print total count of successful reads
  // cout << "\nTotal valid records stored: " << validRecords.size() << endl;
}

void sortArray(MonthlySummary summaries[], bool ascending) {
  for (int i = 0, j = 0; i < SIZE; i++, j++) {
    bool swapNeeded = false;
    if (j > 0) {
      double* lValPtr = &(summaries[j - 1].totalActual);
      double* rValPtr = &(summaries[j].totalActual);
      MonthlySummary* lStructPtr = &(summaries[j - 1]);
      MonthlySummary* rStructPtr = &(summaries[j]);
      if ((*lValPtr > *rValPtr && ascending) || (*lValPtr < *rValPtr && !ascending)) {
        swapItems(lStructPtr, rStructPtr);
        swapNeeded = true;
      }
    }

    if (swapNeeded) {
      i--;
      j -= 2;
    } else {
      j = i;
    }
  }
}

void swapItems(MonthlySummary* a, MonthlySummary* b) {
  MonthlySummary temp = *b;
  *b = *a;
  *a = temp;
}
