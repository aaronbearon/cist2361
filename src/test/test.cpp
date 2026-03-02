#include <iostream>

using namespace std; 

void doSomething(int&);

int main()

{

 int x = 2;

 cout << x << endl;

 doSomething(x);

 cout << x << endl;

 return 0;

}

void doSomething(int& num)

{

 num = 0;

 cout << num << endl;

}