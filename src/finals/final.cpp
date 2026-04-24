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
void processFile(const string& filename, MonthlySummary summaries[]);
void printYearlyReport(MonthlySummary summaries[]);
void sortArray(MonthlySummary summaries[], bool ascending);
void swapItems(MonthlySummary* a, MonthlySummary* b);

int main() {
  const string filename = "expenses.txt";
  MonthlySummary summaries[SIZE];

  processFile(filename, summaries);
  printYearlyReport(summaries);

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

// Handles file opening and iterates through each line.
// Load monthly data from the file into the summaries array.
void processFile(const string& filename, MonthlySummary summaries[]) {
  ifstream inputFile(filename);
  vector<Expense> validRecords;
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

  inputFile.close();
}

// Print the data stored in the previously loaded summaries array.
void printYearlyReport(MonthlySummary summaries[]) {
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
  cout << "Month with highest amount spent: " << MONTHS[summaries[0].month - 1]
       << ", at $" << summaries[0].totalActual << endl;
  cout << "Total spent: $" << actualSum << endl;
  cout << "Total budgeted: $" << budgetedSum << endl;

  cout << endl;
}

// Use pointers and structs to sort the array.
void sortArray(MonthlySummary summaries[], bool ascending) {
  for (int i = 0, j = 0; i < SIZE; i++, j++) {
    bool swapNeeded = false;
    // Check that j isn't 0 to prevent -array index out of bounds.
    if (j > 0) {
      double* lValPtr = &(summaries[j - 1].totalActual);
      double* rValPtr = &(summaries[j].totalActual);
      MonthlySummary* lStructPtr = &(summaries[j - 1]);
      MonthlySummary* rStructPtr = &(summaries[j]);
      if ((*lValPtr > *rValPtr && ascending) ||
          (*lValPtr < *rValPtr && !ascending)) {
        swapItems(lStructPtr, rStructPtr);
        swapNeeded = true;
      }
    }

    // Decrement values if a swap had to be performed.
    // This is a clever sorting algorithm.
    // It ensures that every new unsorted value is swapped to the left until
    //  it's in the correct place.
    if (swapNeeded) {
      i--;
      j -= 2;
    } else {
      j = i;
    }
  }
}

// Use pointers to swap structs in the array.
void swapItems(MonthlySummary* a, MonthlySummary* b) {
  MonthlySummary temp = *b;
  *b = *a;
  *a = temp;
}
