#include <iostream>

import Math;
using namespace std;
int main()
{
	Complex cx(11, -1);
	Complex cy(5, 3.2);

	Rational rx(1, 2);
	Rational ry(3, 4);

	double d = -9;

	cout << "Complex x: " << cx << " Complex y: " << cy << endl;
	cout << "Rational x: " << rx << " Rational y: " << ry << endl;
	cout << "Double d: " << d << endl;

	cout << "x+y = " << cx << " + " << cy << " = " << cx + cy << endl;
	cout << "x-y = " << cx << " - " << cy << " = " << cx - cy << endl;
	cout << "x*y = " << cx << " * " << cy << " = " << cx * cy << endl;
	cout << "x/y = " << cx << " / " << cy << " = " << cx / cy << endl;

	cout << "x+y = " << rx << " + " << ry << " = " << rx + ry << endl;
	cout << "x-y = " << rx << " - " << ry << " = " << rx - ry << endl;
	cout << "x*y = " << rx << " * " << ry << " = " << rx * ry << endl;
	cout << "x/y = " << rx << " / " << ry << " = " << rx / ry << endl;

	
	cout << "f(" << cx << ") = " << f(cx) << endl;
	cout << "f(" << rx << ") = " << f(rx) << endl;
	cout << "f(" << d << ") = " << f(d) << endl;
	return 0;
}