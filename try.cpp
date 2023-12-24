#include <iostream>
#include "CrazyMath.h"

using namespace std;
using namespace CrazyMath;



int main()
{
    auto f1 = (Pow(X, 3));

    auto df1 = derivative(f1);


    cout << "f(x)\tf'(x)" << endl;
    cout << f1(0.5) << " \t" << df1(0.5) << endl;

    return 0;
}