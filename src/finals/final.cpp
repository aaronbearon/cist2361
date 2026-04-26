#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

//// Static data

const int SIZE = 12;
const string MONTHS[SIZE] = {"January",   "February", "March",    "April",
                             "May",       "June",     "July",     "August",
                             "September", "October",  "November", "December"};

//// Data structures

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

//// Function prototypes
// Note, prototypes aren't in the same order as definitions.

// File input functions
vector<Expense> readFile(const string& filename);
bool parseLine(const string& line, Expense* record);

// User input functions
int inputUserMonth();
bool isValidInput(string answerStr, int& answer);

// Processing functions
vector<MonthlySummary> buildMonthlySummaries(const vector<Expense>& expenses);

// Output functions
void printExpensesByMonth(const vector<Expense>& expenses);
void printMostExpensiveMonth(const vector<MonthlySummary>& summaries);
void printMonthlyTotals(const vector<MonthlySummary>& summaries, bool ascending);
void printMonthReport(int month, const MonthlySummary& summaries, const vector<Expense>& expenses);
string toCurrency(double amount);

// Sort functions
bool monthLess(const MonthlySummary* a, const MonthlySummary* b);
bool monthGreater(const MonthlySummary* a, const MonthlySummary* b);
bool expenseSort(const Expense& a, const Expense& b);

//// Implementation

int main() {
  const string filename = "expenses.txt";
  auto expenses = readFile(filename);  // requirement 1 2

  printExpensesByMonth(expenses);  // requirement 3

  auto summaries = buildMonthlySummaries(expenses);
  printMostExpensiveMonth(summaries);  // requirement 4

  printMonthlyTotals(summaries, false);  // requirement 5
  printMonthlyTotals(summaries, true);   // requirement 5
  int month = inputUserMonth();          // requirement 6
  printMonthReport(month, summaries[month], expenses);    // requirement 6

  return 0;
}

vector<Expense> readFile(const string& filename) {
  ifstream inputFile(filename);
  vector<Expense> validRecords;

  if (!inputFile.is_open()) {
    cout << "Fail: Could not open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  string line;
  while (getline(inputFile, line)) {
    // If the line is just a trailing newline/empty, we skip it
    if (line.empty()) continue;

    Expense tempRecord;
    if (parseLine(line, &tempRecord)) {
      validRecords.push_back(tempRecord);
    } else {
      cout << "Error, invalid line." << endl;
      exit(EXIT_FAILURE);
    }
  }

  inputFile.close();

  // make sure they are sorted
  sort(validRecords.begin(), validRecords.end(), expenseSort);
  return validRecords;
}

bool expenseSort(const Expense& a, const Expense& b) {
  return a.month < b.month;
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
    record->month = stoi(tokens[0]) - 1;
    record->category = tokens[1];
    record->amount = round(stod(tokens[2]) * 100) / 100.0;
    record->budgeted = round(stod(tokens[3]) * 100) / 100.0;
    // Check for valid values
    if (record->month < 0 || record->month > 11) {
      return false;
    }
    if (record->amount < 0 || record->budgeted < 0) {
      return false;
    }
    if (record->category.size() > 12) {
      record->category.erase(12);
    }
    return true;
  } catch (const invalid_argument& e) {
    return false;
  } catch (const out_of_range& e) {
    return false;
  }
}

void printExpensesByMonth(const vector<Expense>& expenses) {
  int currentMonth = -1;
  for (auto expense : expenses) {
    if (currentMonth != expense.month) {
      currentMonth = expense.month;
      cout << endl;
      cout << MONTHS[expense.month] << endl;
    }

    cout << fixed << showpoint << setprecision(2);
    cout << expense.category << " Actual: $" << expense.amount;
    cout << " Budget: $" << expense.budgeted << endl;
  }

  /*

  January:
  Mortgage Actual: $1200.45 Budget: $1200
  Utilities 350 300

  February:
  Utilities 350 300
  Groceries 500 450

  */
}

// Processing
vector<MonthlySummary> buildMonthlySummaries(const vector<Expense>& expenses) {
  vector<MonthlySummary> summaries;
  for (int i = 0; i < SIZE; i++) {
    MonthlySummary month = {i, 0, 0};
    summaries.push_back(month);
  }
  for (auto expense : expenses) {
    summaries[expense.month].totalActual += expense.amount;
    summaries[expense.month].totalBudgeted += expense.budgeted;
  }
  return summaries;
}

void printMostExpensiveMonth(const vector<MonthlySummary>& summaries) {
  const MonthlySummary* highest = &summaries[0];
  for (int i = 0; i < summaries.size(); i++) {
    const MonthlySummary* summary = &summaries[i];
    if (summary->totalActual > highest->totalActual) {
      highest = summary;
    }
  }

  cout << endl;
  cout << fixed << showpoint << setprecision(2) << endl;
  cout << "Month with highest amount spent: " << MONTHS[highest->month] << "." << endl;
  cout << "Total spent: $" << highest->totalActual << endl;
  cout << "Total budgeted: $" << highest->totalBudgeted << endl;

  cout << endl;
}

void printMonthlyTotals(const vector<MonthlySummary>& summaries, bool ascending) {
  // Make a copy so we can sort the copy.
  vector<const MonthlySummary*> index;
  for (int i = 0; i < summaries.size(); i++) {
    index.push_back(&summaries[i]);
  }

  if (ascending) {
    sort(index.begin(), index.end(), monthLess);
    cout << "=== Monthly Totals (Ascending) ===" << endl;
  } else {
    sort(index.begin(), index.end(), monthGreater);
    cout << "=== Monthly Totals (Descending) ===" << endl;
  }

  cout << fixed << showpoint << setprecision(2) << endl;
  for (auto summary : index) {
    cout << MONTHS[summary->month] << ": ";
    cout << "$" << summary->totalActual << endl;
  }
  cout << endl;
}

bool monthLess(const MonthlySummary* a, const MonthlySummary* b) {
  return a->totalActual < b->totalActual;
}

bool monthGreater(const MonthlySummary* a, const MonthlySummary* b) {
  return a->totalActual > b->totalActual;
}

int inputUserMonth() {
  while (true) {
    cout << "Please enter a month number to report: ";
    int answer = 0;
    string answerStr;
    getline(cin, answerStr);
    if (isValidInput(answerStr, answer)) {
      return answer - 1; // 0 - 11
    } else {
      cout << "Invalid month, try again." << endl;
    }
  }
}

bool isValidInput(string answerStr, int& answer) {
  try {
    answer = stoi(answerStr);
    return answer >= 1 && answer <= 12;  // Month number must be in this range.
  } catch (const invalid_argument& e) {
    return false;
  } catch (const out_of_range& e) {
    return false;
  }
}

void printMonthReport(int month, const MonthlySummary& summaries, const vector<Expense>& expenses) {
  cout << "=== Expense Report for Month: " << month + 1;
  cout << " (" << MONTHS[month] << ") ===" << endl;
  cout << fixed << showpoint << setprecision(2);
  // int maxCategory = 0;
  // int maxAmount = 0;
  // int maxBudget = 0;
  // for (auto expense : expenses) {
  //   if (month == expense.month) {
  //     maxCategory = max((size_t)maxCategory, expense.category.length());
  //     maxAmount = max((size_t)maxAmount, to_string(expense.amount).length());
  //   }
  // }

  for (auto expense : expenses) {
    if (month == expense.month) {
      cout << "Category: " << setw(13) << expense.category << " | Spent: ";
      cout << setw(10) << toCurrency(expense.amount) << " | Budgeted: " << setw(10) << toCurrency(expense.budgeted) << " | ";
      if (expense.amount > expense.budgeted) {
        cout << "Over-Budget by ";
        cout << setw(10) << toCurrency(expense.amount - expense.budgeted) << endl;
      } else {
        cout << "Saved          ";
        cout << setw(10) << toCurrency(expense.budgeted - expense.amount) << endl;
      }
    }
  }

  double subtractBy = min(summaries.totalActual, summaries.totalBudgeted);
  cout << "Total Over-Budget: $" << summaries.totalActual - subtractBy << endl;
  cout << "Savings: $" << summaries.totalBudgeted - subtractBy << endl;
}

// // Print the data stored in the previously loaded summaries array.
// void printYearlyReport(MonthlySummary summaries[]) {
//   cout << fixed << showpoint << setprecision(2);
//   cout << "=== Monthly Totals and Monthly Budgets (Unsorted) ===" << endl;
//   int actualSum = 0;
//   int budgetedSum = 0;
//   for (int i = 0; i < SIZE; i++) {
//     cout << MONTHS[summaries[i].month - 1] << ": ";
//     actualSum += summaries[i].totalActual;
//     budgetedSum += summaries[i].totalBudgeted;
//     cout << "$" << summaries[i].totalActual << ", $"
//          << summaries[i].totalBudgeted << endl;
//   }

//   cout << endl;
// }

string toCurrency(double amount) {
  stringstream out;
  out << "$" << fixed << setprecision(2) << amount;
  return out.str();
}
