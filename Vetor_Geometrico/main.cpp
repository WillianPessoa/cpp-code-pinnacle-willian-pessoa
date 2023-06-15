#include <iostream>
#include "vetor.cc"

using namespace std;

int main( int argc, char* argv[]) {
  Vetor< 3, double> a, b;
  double x = 5, y= 6, z = 7;

  a = { x, y, z };
  b = { 1, 2, 3 };

  for (auto caso: {1, 2, 3, 4, 5, 6, 7}) {
      switch( caso ) {
          case 1: cout << a << endl; break;
          case 2: cout << a + b << endl; break;
          case 3: {
              Vetor< 3, double> c;
              c = a ** b;
              cout << c << endl;
              break;
          }
          case 4: cout << a * b << endl; break;
          case 5: cout << a * 3.0 << endl; break;
          case 6: cout << 2.1 * a << endl; break;
          case 7: cout << a + b + a * 2.0 << endl; break;
      }
  }

  return 0;
}
