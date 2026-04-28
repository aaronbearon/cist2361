// Aaron Blum
// CIST2361: Final Project
// 04/28/2026
// This program calculates and prints home expenses.

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
// Note, the prototypes aren't in the same order as definitions.

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
void printMonthlyTotals(const vector<MonthlySummary>& summaries, bool descending);
void printMonthReport(int month, const MonthlySummary& summaries, const vector<Expense>& expenses);
string moneyToString(double val);

// Sort functions
bool expenseSort(const Expense& a, const Expense& b);
bool monthGreater(const MonthlySummary* a, const MonthlySummary* b);
bool monthLess(const MonthlySummary* a, const MonthlySummary* b);

//// Implementation

int main() {
  const string filename = "expenses.txt";
  auto expenses = readFile(filename);  // requirement 1 2

  printExpensesByMonth(expenses);  // requirement 3

  auto summaries = buildMonthlySummaries(expenses);
  printMostExpensiveMonth(summaries);  // requirement 4

  printMonthlyTotals(summaries, true);                  // requirement 5
  printMonthlyTotals(summaries, false);                 // requirement 5
  int month = inputUserMonth();                         // requirement 6
  printMonthReport(month, summaries[month], expenses);  // requirement 6

  return 0;
}

// Load all the expense data from the file into the main expense vector.
vector<Expense> readFile(const string& filename) {
  ifstream inputFile(filename);
  vector<Expense> validRecords;

  if (!inputFile.is_open()) {
    cout << "Fail: Could not open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  string line;
  while (getline(inputFile, line)) {
    // If the line is just a trailing newline/empty, we skip it.
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

  // Make sure they are sorted.
  sort(validRecords.begin(), validRecords.end(), expenseSort);
  return validRecords;
}

// This reads each file line and and checks whether or not it's valid.
// If not, this file is a bad file and can't be used for this program.
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
    // Attempt conversions, these throw exceptions if they fail.
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
    return true;
  } catch (const invalid_argument& e) {
    return false;
  } catch (const out_of_range& e) {
    return false;
  }
}

// Used for sorting from the <algorithm> header.
// Sorts big vector by month.
bool expenseSort(const Expense& a, const Expense& b) {
  return a.month < b.month;
}

// After sorting, expenses can be properly printed in group by month fashion.
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
}

// Processing function
// Create a vector of 12 structs, one for each month.
// The actual spent amounts each month are added, to get the total.
// The total is assigned to the total actual amount in the corresponding struct.
// The same thing happens for the budgeted amount.
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

// This prints the month with the highest amount spent.
// It also prints the total amount spent for the whole year.
// The total budgeted amount for the year is also included in the output.
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
  cout << "Total spent this month: $" << highest->totalActual << endl;
  cout << "Total budgeted this month: $" << highest->totalBudgeted << endl;

  cout << endl;
}

// Print the month name, followed by the total actual spent.
// These entries should be sorted by the total actual spent.
// Print descending first, then ascending.
void printMonthlyTotals(const vector<MonthlySummary>& summaries, bool descending) {
  // Make a copy so we can sort the copy.
  vector<const MonthlySummary*> index;
  for (int i = 0; i < summaries.size(); i++) {
    index.push_back(&summaries[i]);
  }

  if (descending) {
    sort(index.begin(), index.end(), monthGreater);
    cout << "=== Monthly Totals (Descending) ===" << endl;
  } else {
    sort(index.begin(), index.end(), monthLess);
    cout << "=== Monthly Totals (Ascending) ===" << endl;
  }

  cout << fixed << showpoint << setprecision(2) << endl;
  for (auto summary : index) {
    cout << MONTHS[summary->month] << ": ";
    cout << "$" << summary->totalActual << endl;
  }
  cout << endl;
}

// Used for sorting from the <algorithm> header.
// Sorts monthly summaries by total actual spent descending.
bool monthGreater(const MonthlySummary* a, const MonthlySummary* b) {
  return a->totalActual > b->totalActual;
}

// Used for sorting from the <algorithm> header.
// Sorts monthly summaries by total actual spent ascending.
bool monthLess(const MonthlySummary* a, const MonthlySummary* b) {
  return a->totalActual < b->totalActual;
}

// Get a month number from the user.
int inputUserMonth() {
  while (true) {
    cout << "Please enter a month number to report: ";
    int answer = 0;
    string answerStr;
    getline(cin, answerStr);
    if (isValidInput(answerStr, answer)) {
      return answer - 1;  // 0 - 11
    } else {
      cout << "Invalid month, try again." << endl;
    }
  }
}

// Check that the user's month is valid.
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

// Print a cleanly formatted report for the user-specified month.
void printMonthReport(int month, const MonthlySummary& summaries, const vector<Expense>& expenses) {
  cout << "=== Expense Report for Month: " << month + 1;
  cout << " (" << MONTHS[month] << ") ===" << endl;
  cout << fixed << showpoint << setprecision(2);

  // First, run through the expenses to populate the variables to set up the output.
  size_t maxCategory = 0;
  size_t maxAmount = 0;
  size_t maxBudget = 0;
  size_t maxDifference = 0;
  for (auto expense : expenses) {
    if (month == expense.month) {
      maxCategory = max(maxCategory, expense.category.length());
      maxAmount = max(maxAmount, moneyToString(expense.amount).length());
      maxBudget = max(maxBudget, moneyToString(expense.budgeted).length());
      maxDifference = max(maxDifference, moneyToString(abs(expense.amount - expense.budgeted)).length());
    }
  }

  // Run through the vector again to print out the table.
  for (auto expense : expenses) {
    if (month == expense.month) {
      cout << "Category: " << left << setw(maxCategory) << expense.category << right;
      cout << " | Spent: $" << setw(maxAmount) << moneyToString(expense.amount);
      cout << " | Budgeted: $" << setw(maxBudget) << moneyToString(expense.budgeted);
      cout << " | ";
      if (expense.amount > expense.budgeted) {
        cout << "Over-Budget by $" << setw(maxDifference) << moneyToString(expense.amount - expense.budgeted) << endl;
      } else {
        cout << "Saved          $" << setw(maxDifference) << moneyToString(expense.budgeted - expense.amount) << endl;
      }
    }
  }

  // Finally, print out the difference of actuals and budgets.
  // Either over-budget amount, or savings, depending on which of the two totals was higher.
  double subtractBy = min(summaries.totalActual, summaries.totalBudgeted);
  cout << "Total Over-Budget: $" << summaries.totalActual - subtractBy << endl;
  cout << "Savings: $" << summaries.totalBudgeted - subtractBy << endl;
  cout << endl;
}

// This function returns the string representation of the stringstream.
string moneyToString(double val) {
  stringstream stream;
  stream << fixed << showpoint << setprecision(2) << val;
  return stream.str();
}
