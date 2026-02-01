// This program calculates Miles Per Gallon

// Aaron Blum
// CIST2361: Week 2 in class
// 01/22/2026
#include <iostream>
using namespace std;

// Print problem assumptions / inputs.
void printGallonsAndMiles(double gallons, double miles) {
  cout << "The car can hold " << gallons << " gallons and drive ";
  cout << miles << " miles from a full tank." << endl;
}

// Calculate the miles per gallon for the given parameters.
double calculateMpg(double gallons, double miles) { return miles / gallons; }

// Print the answer with units.
void printMpg(double mpg) {
  cout << "The car's miles per gallon is " << mpg << "." << endl;
}

// Run miles per gallon.
int main() {
  const double gallons = 15;
  const double miles = 375;
  printGallonsAndMiles(gallons, miles);
  double mpg = calculateMpg(gallons, miles);
  printMpg(mpg);
  return 0;
}
