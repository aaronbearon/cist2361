// Aaron Blum
// CIST2361: Lab 02
// 01/21/2026
// This program makes a restaurant bill.
#include <iomanip>  // format money
#include <iostream>
using namespace std;

const double taxFraction = 6.75 / 100;
const double tipFraction = 20.0 / 100;

double roundPennies(double amount) { return round(amount * 100) / 100; }

// Verify input and get the base cost of the meal.
double inputMealCost() {
  while (true) {
    cout << "Please enter the meal cost: ";
    double mealCost;
    cin >> mealCost;
    if (mealCost >= 0) {
      return roundPennies(mealCost);
    }
    cout << "Error, cost can't be negative!" << endl;
  }
}

// Calculate the amount of tax as 6.75% of the base cost.
double calculateTax(double mealCost) {
  double tax = roundPennies(mealCost * taxFraction);
  return tax;
}

// Calculate the amount of tip as 20% of the subtotal.
double calculateTip(double subtotal) {
  double tip = roundPennies(subtotal * tipFraction);
  return tip;
}

// Print the results with appropriate names and dollar signs.
// Used to display missing zeros as needed.
void printResults(double mealCost, double tax, double tip, double total) {
  cout << fixed << setprecision(2);
  cout << "Meal cost: $" << mealCost << endl;
  cout << "Tax: $" << tax << endl;
  cout << "Tip: $" << tip << endl;
  cout << "Total: $" << total << endl;
}

// Prepare the restaurant bill.
int main() {
  double mealCost = inputMealCost();
  double tax = calculateTax(mealCost);

  // The tip is on the subtotal including tax.
  double subtotal = mealCost + tax;
  double tip = calculateTip(subtotal);

  // Total is subtotal and tip.
  double total = subtotal + tip;

  // Display results.
  printResults(mealCost, tax, tip, total);
  return 0;
}
