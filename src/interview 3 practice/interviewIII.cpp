#include <iostream>
using namespace std;

/*
QUESTION 1
Write a function that receives an integer and returns:
1 if positive, -1 if negative, 0 if zero.
Also print the classification.

ANSWER:
The classification is printed out inside the function.
It's based on whether the int is positive, negative, or zero.
*/
// PROTOTYPE:
int getIntType(int n);

/*
QUESTION 2
Create a function that receives three integers and returns the largest.
Explain how it generalizes the 2-number case.

ANSWER:
If you #include <cmath>, you can call the max function.
That library function automatically returns the larger of two numbers.
*/
// PROTOTYPE:
int getMaxOfThree(int a, int b, int c);

/*
QUESTION 3
Write a function that receives an array and its size and returns BOTH:
- sum
- average (use reference parameters)
Explain why references are useful.

ANSWER:
Reference parameters allow you to change the content of data
    in the calling function from the receiving function.
They're useful if you want to "return" multiple values from a function.
That's because functions only return one value.

*/
// PROTOTYPE:
void getSumAndAverage(const double array[], const int size, double& sum,
                      double& average);

/*
QUESTION 4
Write a function that swaps two integers using pointers.
Explain step-by-step how memory is modified.

ANSWER:
The function receives aptr and bptr, which are pointer-to-int variables.
Assume, they point to a, b respectively, which contain 5 and 10 respectively.
A third pair is created in the function. It is cptr, pointing to c of the int
type. The c variable can be assigned an initialization value (like 0). That
means each int variable has a value stored in a memory address. Each pointer
variable is assigned a unique one of those memory addresses.

The value that's in the address which is stored in bptr
    becomes the new value that's in the address which is stored in cptr.
That's what happens in the statement *cptr = *bptr happens.
The c pair is like a temp.
Once the b value goes to the c value, the a value goes to b value.
Then, a's value becomes the value that's stored in c, basically swaping a and b.

*/
// PROTOTYPE:
void swapInts(int* aptr, int* bptr);

/*
QUESTION 5
Define a struct Student.
Write a function that receives a Student and determines if the student
is passing (grade >= 70).
*/
// PROTOTYPE:

/*
QUESTION 6 — C-STRINGS
Write a function that counts characters in a C-string WITHOUT strlen().
Also count only alphabetic characters.

ANSWER:
*/
// PROTOTYPE:

/*
QUESTION 7 — C-STRINGS
Write a function that reverses a C-string in place (no extra array).

ANSWER:
*/
// PROTOTYPE:

/*
QUESTION 8 — STRING CLASS
Write a function that counts vowels AND consonants in a string.

ANSWER:
*/
// PROTOTYPE:

/*
QUESTION 9 — VECTORS
Write a function that returns BOTH:
- largest value
- index of largest value

ANSWER:
*/
// PROTOTYPE:

/*
QUESTION 10 — STRUCT + VECTOR
Define struct Course.
Write a function that returns total credits from a vector of Course.

ANSWER:
*/
// PROTOTYPE:

int main() {
  // No implementation
  int a = 89;
  int b = 32;
  int* aptr = &a;
  int* bptr = &b;
  cout << *aptr << " " << *bptr << endl;
  swapInts(aptr, bptr);
  cout << *aptr << " " << *bptr << endl;
  return 0;
}

// Function #1
int getIntType(int n) {
  if (n < 0) {
    cout << "It's negative." << endl;
    return -1;
  } else if (n > 0) {
    cout << "It's positve." << endl;
    return 1;
  } else {
    cout << "It's zero." << endl;
    return 0;
  }
}

// Function #2
int getMaxOfThree(int a, int b, int c) {
  if (a >= b && a >= c) {
    return a;
  } else if (b >= c) {
    return b;
  } else {
    return c;
  }
}

// Function #3
void getSumAndAverage(const double array[], const int size, double& sum,
                      double& average) {
  int currSum = 0;
  for (int i = 0; i < size; i++) {
    currSum += array[i];
  }

  sum = currSum;
  average = sum / size;
}

// Function #4
void swapInts(int* aptr, int* bptr) {
  int c = 0;
  int* cptr = &c;
  *cptr = *bptr;
  *bptr = *aptr;
  *aptr = *cptr;
}
