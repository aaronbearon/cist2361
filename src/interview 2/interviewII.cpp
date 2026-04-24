// Aaron Blum
// CIST2361: Interview 2
// 04/23/2026
#include <iostream>
#include <string>
using namespace std;

/*
QUESTION 1 — Variables and Control Flow
Write a C++ program that reads an integer from the user and prints whether
the number is positive, negative, or zero.

ANSWER:
The function doesn't return anything or take any arguments.
The user prompted for an int of a specific classification.
Then, the classification is printed out.
It's based on whether the int is positive, negative, or zero.
*/

// PROTOTYPE:
void printIntType();

/*
QUESTION 2 — Functions and Modularity
Create a function that receives two integers and returns the larger value.
Explain how this function would be called from main().

ANSWER:
To call this function from main, create two int variables in main.
Then, pass them into the function call, which is used in the place of an int.
Example statement below:
cout << getMax(x, y) << endl;

This would print 5 if x is 5 and y is 3.
*/

// PROTOTYPE:
int getMax(int a, int b);

/*
QUESTION 3 — Arrays and Loops
Given an array of integers, write code to find the sum and average of its
elements. What loop structure would you use and why?

ANSWER:
The best loop structure for this problem would be to use a for loop.
The reason why, is because the number of elements in the array is known.
You want a loop that iterates a specific number of times.

A sum variable is declared before the for loop.
After the loop, an average variable is declared.
It's set to the sum divided by the element count.
Afterwards, sum and average are printed out.

Note: they're all ints except for the double average variable.
*/

// PROTOTYPE:
void printSumAndAverage(const int array[], const int size);

/*
QUESTION 4 — Pointers (Core Concept)
What is a pointer in C++?
Write a function that uses a pointer to modify a variable declared in main().

ANSWER:
A pointer is a specialized variable designed to store a memory address.
The pointer can access and modify the value stored in the memory address that's
  stored in the pointer variable.
This even works if the pointer variable and actual value are in different
  functions.
*/

// PROTOTYPE:
void updateValue(int* intPtr);

/*
QUESTION 5 — Structs (Basic Data Organization)
Define a struct called Student with the fields: name, id, and grade.
Write a function that creates one student and prints its information.

ANSWER:
The function doesn't return anything or take any arguments.
The Student struct is defined in the function.
An instance of student is declared and fields are initialized in one statement.
The fields are printed out in the function.
*/

// PROTOTYPE:
void printStudentFields();

int main() {
  return 0;
}

// Function #1
void printIntType() {
  cout << "Please enter either a positive int, negative int, or 0: ";
  int n;
  cin >> n;
  if (n < 0) {
    cout << "It's negative." << endl;
  } else if (n > 0) {
    cout << "It's positive." << endl;
  } else {
    cout << "It's zero." << endl;
  }
}

// Function #2
int getMax(int a, int b) {
  if (a >= b) {
    return a;
  } else {
    return b;
  }
}

// Function #3
void printSumAndAverage(const int array[], const int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += array[i];
  }

  double average = sum * 1.0 / size;
  cout << "Sum of elements is " << sum << endl;
  cout << "Average of elements is " << average << endl;
}

// Function #4
void updateValue(int* intPtr) {
  *intPtr += 100;
}

// Function #5
void printStudentFields() {
  struct Student {
    string name;
    int id;
    double grade;
  };

  Student student = {"Thomas", 736247987, 96.37};
  cout << "Here's the student's information below:" << endl;
  cout << "Name: " << student.name << endl;
  cout << "ID: " << student.id << endl;
  cout << "Grade: " << student.grade << endl;
}
