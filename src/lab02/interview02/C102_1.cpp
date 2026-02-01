// Name and Phone
#include <iostream>
#include <string>
using namespace std;

int main() {
  cout << "Please enter your name: ";
  string name;
  getline(cin, name);
  cout << "Please enter the last 4 digits of your phone number: ";
  string phone;
  getline(cin, phone);
  cout << "Your name is " << name << "." << endl;
  cout << "The last 4 digits of your phone number are " << phone << "." << endl;
  return 0;
}
