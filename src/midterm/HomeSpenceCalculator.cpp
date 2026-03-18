// Aaron Blum
// CIST2361: Midterm Project
// 03/18/2026
// This program calculates and prints home expenses.

#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>  // Required for number formatting.
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

const string MONTHS[] = {"JANUARY",   "FEBRUARY", "MARCH",    "APRIL",
                         "MAY",       "JUNE",     "JULY",     "AUGUST",
                         "SEPTEMBER", "OCTOBER",  "NOVEMBER", "DECEMBER"};

const string SHORT_MONTHS[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                               "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

const string UTILITIES[] = {"Electricity", "Water", "Gas", "Internet"};

const string MEALS[] = {"Groceries", "Restaurants"};

struct LineItem {
  string category;
  int actual;
  int budget;
};

void displayMenu();
void inputStartEndMonth(int& startMonth, int& endMonth);
void inputSameMonthly(LineItem& item, int numMonths);
void inputItemized(LineItem& item, string category,
                   const string subcategories[], int startMonth, int endMonth,
                   const int SIZE);
void inputTotal(LineItem& item, int startMonth, int endMonth);
int inputInt(string prompt);
void displayTable(const LineItem items[], const int SIZE, int startMonth,
                  int endMonth);
string asCurrency(int amount);
string asVariance(int amount);
void displaySummary(const LineItem items[], const int SIZE);

// global input stream, so we can override with a file for testing
istream* input = &cin;

int main() {
  ifstream inFile;  // no close needed, use function scope destructor
  inFile.open("sample.txt");
  if (inFile) {
    input = &inFile;
  }

  LineItem items[] = {
      {"Mortage / Rent", 0, 0}, {"Home Insurance", 0, 0},
      {"Utilities", 0, 0},      {"Maintenance & Repairs", 0, 0},
      {"Renovations", 0, 0},    {"Meals", 0, 0},
  };

  displayMenu();

  int startMonth, endMonth;
  inputStartEndMonth(startMonth, endMonth);
  int numMonths = endMonth - startMonth + 1;

  // first two categories, input monthly, but same every month
  inputSameMonthly(items[0], numMonths);
  inputSameMonthly(items[1], numMonths);

  // utilities is itemized with subcategories and different each month
  inputItemized(items[2], "UTILITIES", UTILITIES, startMonth, endMonth, 4);

  // next two categories just take a single value
  inputTotal(items[3], startMonth, endMonth);
  inputTotal(items[4], startMonth, endMonth);

  // meals is itemized with subcategories and different each month
  inputItemized(items[5], "MEALS", MEALS, startMonth, endMonth, 2);

  displayTable(items, 6, startMonth, endMonth);
  displaySummary(items, 6);
  return 0;
}

// Required menu function.
void displayMenu() {
  cout << "Which months do you want to calculate expenses for below?" << endl;
  cout << endl;
  for (int i = 0; i < 12; i++) {
    cout << (i + 1) << ". " << MONTHS[i] << endl;
  }

  cout << endl;
}

void inputStartEndMonth(int& startMonth, int& endMonth) {
  while (true) {
    startMonth = inputInt("Enter start month (1-12)");
    if (startMonth >= 1 && startMonth <= 12) {
      break;
    } else {
      cout << "Error: Month must be between 1 and 12. Please try again."
           << endl;
    }
  }

  while (true) {
    endMonth = inputInt("Enter end month (>= start)");
    if (endMonth >= startMonth && endMonth <= 12) {
      break;
    } else {
      cout << "Error: Month must be between " << startMonth
           << " and 12. Please try again." << endl;
    }
  }
}

void inputSameMonthly(LineItem& item, int numMonths) {
  item.actual = inputInt(item.category + " -- enter actual monthly");
  item.budget = inputInt(item.category + " -- enter budgeted monthly");
  item.actual *= numMonths;
  item.budget *= numMonths;
}

void inputItemized(LineItem& item, string category,
                   const string subcategories[], int startMonth, int endMonth,
                   const int SIZE) {
  item.actual = 0;
  item.budget = 0;
  for (int month = startMonth; month <= endMonth; month++) {
    for (int i = 0; i < SIZE; i++) {
      int actual = inputInt(category + " for " + MONTHS[month - 1] + " -- " +
                            subcategories[i] + " actual");
      int budget = inputInt(category + " for " + MONTHS[month - 1] + " -- " +
                            subcategories[i] + " budgeted");
      item.actual += actual;
      item.budget += budget;
    }
  }
}

void inputTotal(LineItem& item, int startMonth, int endMonth) {
  item.actual =
      inputInt(item.category + " -- total actual for " +
               SHORT_MONTHS[startMonth - 1] + "-" + SHORT_MONTHS[endMonth - 1]);
  item.budget =
      inputInt(item.category + " -- total budgeted for " +
               SHORT_MONTHS[startMonth - 1] + "-" + SHORT_MONTHS[endMonth - 1]);
}

int inputInt(string prompt) {
  int value = 0;
  int& v = value;
  int* w = &value;
  while (true) {
    cout << prompt << ": ";
    *input >> value;
    if (input->fail()) {
      cout << "Error: Please enter a valid integer." << endl;
      input->clear();
      input->ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      if (input != &cin) {
        cout << value << endl;  // for file read, debug print the value
      }
      return value;
    }
  }
}

// Display formatted table.
// Note: This is a fixed table designed with enough spacing for big enough
// numbers. Not for overly large numbers.
void displayTable(const LineItem items[], const int SIZE, int startMonth,
                  int endMonth) {
  cout << endl;
  cout << "Homeowner Expenses (" << SHORT_MONTHS[startMonth - 1] << "-"
       << SHORT_MONTHS[endMonth - 1] << ")" << endl;
  cout << "Category                    Actual     Budget     Variance" << endl;
  cout << "----------------------------------------------------------" << endl;
  int totalActual = 0;
  int totalBudget = 0;
  int totalVariance = 0;
  for (int i = 0; i < SIZE; i++) {
    totalActual += items[i].actual;
    totalBudget += items[i].budget;
    int variance = items[i].actual - items[i].budget;
    totalVariance += variance;
    cout << left << setw(23) << items[i].category << right << setw(11)
         << asCurrency(items[i].actual) << right << setw(11)
         << asCurrency(items[i].budget) << right << setw(13)
         << asVariance(variance) << endl;
  }
  cout << "----------------------------------------------------------" << endl;
  cout << left << setw(23) << "TOTAL" << right << setw(11)
       << asCurrency(totalActual) << right << setw(11)
       << asCurrency(totalBudget) << right << setw(13)
       << asVariance(totalVariance) << endl;
}

// Display the over-budget items.
void displaySummary(const LineItem items[], const int SIZE) {
  cout << endl;
  cout << "Over-budget items: ";
  int totalSaved = 0;
  int totalOverrun = 0;
  bool first = true;
  for (int i = 0; i < SIZE; i++) {
    int variance = items[i].actual - items[i].budget;
    if (variance > 0) {
      // Comma required after the first item.
      if (!first) {
        cout << ", ";
      }

      cout << items[i].category << " (" << asVariance(variance) << ")";
      totalOverrun += variance;
      first = false;
    } else {
      totalSaved += -variance;
    }
  }

  if (first) {
    cout << "None";
  }

  // Print a period after the list of over-budget items.
  cout << "." << endl;
  if (totalOverrun - totalSaved > 0) {
    cout << "Overrun: " << asCurrency(totalOverrun - totalSaved) << endl;
  } else {
    cout << "Amount saved: " << asCurrency(totalSaved - totalOverrun) << endl;
  }

  cout << endl;
}

string asCurrency(int amount) {
  ostringstream oss;
  oss.imbue(locale("en_US.UTF-8"));
  oss << "$" << amount;
  return oss.str();
}

string asVariance(int amount) {
  if (amount < 0) {
    return "-" + asCurrency(-amount);
  } else  if (amount > 0) {
    return "+" + asCurrency(amount);
  } else {
    return asCurrency(0);
  }
}
