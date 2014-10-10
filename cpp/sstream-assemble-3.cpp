// Compiled and executed successfully
// http://www.dreamincode.net/forums/topic/95826-stringstream-tutorial/
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  stringstream ss2;
  ss2 << "Deekshith " << 21 << " coding";
  cout << ss2.str()<<endl;
}

