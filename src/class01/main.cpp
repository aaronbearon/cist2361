#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string strObj(" C++ on Thursdays ");
  char loveArray[40] = {'L', 'o', 'v', 'e', '\0'};
  strcat(loveArray, strObj.c_str());
  cout << loveArray << endl;
  
  return 0;
}
