#include <iostream>
#include <vector>

#include "lambda.cc"

using namespace std;

void test1()
{
    vector<int> v1 = { 1, 2, 3, 4, 1, 1, 0, 8 };
    v1 | (x % 2 == 0) | cout << x * x + 1 << ' ';
}

int main()
{
    test1();
    cout << endl;
    return 0;
}
