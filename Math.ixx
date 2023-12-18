module;
#include <math.h>
#include <iostream>

export module Math;

export class Complex
{

	double mod;
	double arg;

public:
	Complex() : mod(0), arg(0) {}
	Complex(double re, double im)
	{
		mod = sqrt(re * re + im * im);
		arg = atan2(im, re);
		if (mod < 6.6613381477509392e-15)
			mod = 0;
		if ((arg > 3.1415926535897) && (arg < 3.1415926535898))
			arg = 0;
	}
	Complex(double mod) : mod(mod), arg(0) {}

	Complex static FromExponentialForm(double mod, double arg) {
		Complex result{ mod * cos(arg), mod * sin(arg) };

		return result;
	}
	Complex static FromAlgebraicForm(double re, double im) {
		Complex result{ re, im };

		return result;
	}

	double Re() const {
		return mod * cos(arg);
	}

	double Im() const {
		return mod * sin(arg);
	}

	double Mod() const {
		return mod;
	}

	double Arg() const {
		if (abs(mod * cos(arg)) < 0.000001 && abs(mod * sin(arg)) < 0.000001) {
			return 0;
		}

		return arg;
	}

	explicit operator double() {
		return Re(); 
	}

	Complex operator-() const {
		return Complex(-Re(), -Im());
	}

	Complex& operator++() {
		double re = Re() + 1;
		double im = Im();
		mod = sqrt(re * re + im * im);
		arg = atan2(im, re);

		return *this;
	}

	Complex operator++(int) {
		Complex result(*this);
		++(*this);

		return result;
	}

	Complex& operator--() {
		double re = Re() - 1;
		double im = Im();
		mod = sqrt(re * re + im * im);
		arg = atan2(im, re);

		return *this;
	}

	Complex operator--(int) {
		Complex result(*this);
		--(*this);

		return result;
	}

	Complex& operator+=(Complex value) {
		double re = Re();
		double im = Im();
		re += value.mod * cos(value.arg);
		im += value.mod * sin(value.arg);

		mod = sqrt(re * re + im * im);
		arg = atan2(im, re);

		return *this;
	}

	Complex& operator-=(Complex value) {
		double re = Re();
		double im = Im();
		re -= value.mod * cos(value.arg);
		im -= value.mod * sin(value.arg);

		mod = sqrt(re * re + im * im);
		arg = atan2(im, re);

		return *this;
	}

	Complex& operator*=(Complex value) {
		mod *= value.mod;
		arg += value.arg;

		return *this;
	}

	Complex& operator/=(Complex value) {
		mod /= value.mod;
		arg -= value.arg;

		return *this;
	}

	friend Complex operator+(const Complex&, const Complex&);
	friend Complex operator-(const Complex&, const Complex&);
	friend Complex operator*(const Complex&, const Complex&);
	friend Complex operator/(const Complex&, const Complex&);
	friend Complex operator ""i(long double);
	friend Complex operator ""i(unsigned long long);
	friend std::ostream& operator<<(std::ostream&, const Complex&);
};

export Complex operator+(const Complex& x, const Complex& y) {
	double re = x.mod * cos(x.arg) + y.mod * cos(y.arg);
	double im = x.mod * sin(x.arg) + y.mod * sin(y.arg);

	return Complex(re, im);
}

export Complex operator-(const Complex& x, const Complex& y) {
	double re = x.mod * cos(x.arg) - y.mod * cos(y.arg);
	double im = x.mod * sin(x.arg) - y.mod * sin(y.arg);

	return Complex(re, im);
}

export Complex operator*(const Complex& x, const Complex& y) {
	double re_x = x.mod * cos(x.arg);
	double re_y = y.mod * cos(y.arg);
	double im_x = x.mod * sin(x.arg);
	double im_y = y.mod * sin(y.arg);

	double re = re_x * re_y - im_x * im_y;
	double im = re_x * im_y + im_x * re_y;

	return Complex(re, im);
}

export Complex operator/(const Complex& x, const Complex& y) {
	double re_x = x.mod * cos(x.arg);
	double re_y = y.mod * cos(y.arg);
	double im_x = x.mod * sin(x.arg);
	double im_y = y.mod * sin(y.arg);

	double re = (re_x * re_y + im_x * im_y) / (re_y * re_y + im_y * im_y);
	double im = (re_y * im_x - re_x * im_y) / (re_y * re_y + im_y * im_y);

	return Complex(re, im);
}

export Complex operator ""i(unsigned long long im) {

	return Complex(0.0, (double)im);
}

export Complex operator ""i(long double im) {

	return Complex(0.0, (double)im);
}

export std::ostream& operator<<(std::ostream& os, const Complex& x) {
	double re = x.mod * cos(x.arg);
	double im = x.mod * sin(x.arg);

	os << re << " + (" << im << "i)" ;

	return os;
}

export int FindGreatestCommonDivisor(int a, int b) {
	a = std::abs(a);
	b = std::abs(b);

	while (a != 0 && b != 0) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	return a + b;
}

export int FindLeastCommonMultiple(int a, int b) {
	return abs(a * b) / FindGreatestCommonDivisor(a, b);
}


export class Rational
{

	int nominator;
	int denominator;

	void rationing() {
		int nod = FindGreatestCommonDivisor(nominator, denominator);
		nominator /= nod;
		denominator /= nod;

		if (denominator < 0) {
			denominator *= -1;
			nominator *= -1;
		}
	}

public:
	Rational() : nominator(0), denominator(1) {}
	Rational(int nominator, int denominator) : nominator(nominator), denominator(denominator) { rationing(); }
	Rational(int nominator) : nominator(nominator), denominator(1) { rationing(); }

	int Nominator() const {
		return nominator;
	}

	int Denominator() const {
		return denominator;
	}

	explicit operator double() const {
		return (double)Nominator() / Denominator();
	}

	Rational operator-() const {
		return Rational(-Nominator(), Denominator());
	}


	Rational& operator++(){
		nominator += Denominator();
		rationing();

		return *this;
	}

	Rational operator++(int){
		Rational result(*this);
		++(*this);
		rationing();

		return result;
	}


	Rational& operator--(){
		nominator -= Denominator();
		rationing();

		return *this;
	}

	Rational operator--(int){
		Rational result(*this);
		--(*this);
		rationing();

		return result;
	}

	Rational& operator+=(Rational x) {
		int nok = FindLeastCommonMultiple(Denominator(), x.denominator);
		nominator = nok / Denominator() * Nominator();
		nominator += nok / x.denominator * x.nominator;
		denominator = nok;
		rationing();

		return *this;
	}

	Rational& operator-=(Rational x) {
		int nok = FindLeastCommonMultiple(Denominator(), x.denominator);
		nominator = nok / Denominator() * Nominator();
		nominator -= nok / x.denominator * x.nominator;
		denominator = nok;
		rationing();

		return *this;
	}

	Rational& operator*=(Rational x) {
		nominator *= x.nominator;
		denominator *= x.denominator;
		rationing();

		return *this;
	}

	Rational& operator/=(Rational x) {
		nominator *= x.denominator;
		denominator *= x.nominator;
		rationing();

		return *this;
	}

	friend Rational operator+ (const Rational& x, const Rational& y);
	friend Rational operator- (const Rational& x, const Rational& y);
	friend Rational operator* (const Rational& x, const Rational& y);
	friend Rational operator/(const Rational& x, const Rational& y);
	friend bool operator==(const Rational& x, const Rational& y);
	friend bool operator>(const Rational& x, const Rational& y);
	friend bool operator<(const Rational& x, const Rational& y);
	friend bool operator>=(const Rational& x, const Rational& y);
	friend bool operator<=(const Rational& x, const Rational& y);
	friend std::ostream& operator<<(std::ostream& stream, const Rational& x);

};

export Rational operator+ (const Rational& x, const Rational& y) {
	int denominator = FindLeastCommonMultiple(x.denominator, y.denominator);
	int nominator = denominator / x.denominator * x.nominator;
	nominator += denominator / y.denominator * y.nominator;

	return Rational(nominator, denominator);
}

export Rational operator-(const Rational& x, const Rational& y) {
	int denominator = FindLeastCommonMultiple(x.denominator, y.denominator);
	int nominator = denominator / x.denominator * x.nominator;
	nominator -= denominator / y.denominator * y.nominator;

	return Rational{ nominator, denominator };
}

export Rational operator*(const Rational& x, const Rational& y) {

	return Rational(x.nominator * y.nominator, y.denominator * x.denominator);
}

export Rational operator/(const Rational& x, const Rational& y) {

	return Rational(x.nominator * y.denominator, x.denominator * y.nominator);
}

export bool operator==(const Rational& x, const Rational& y) {

	return x.nominator == y.nominator && x.denominator == y.denominator;
}

export bool operator>(const Rational& x, const Rational& y) {
	int nok = FindLeastCommonMultiple(x.denominator, y.denominator);

	return nok / x.denominator * x.nominator > nok / y.denominator * y.nominator;
}

export bool operator<(const Rational& x, const Rational& y) {
	int nok = FindLeastCommonMultiple(x.denominator, y.denominator);

	return nok / x.denominator * x.nominator < nok / y.denominator * y.nominator;
}

export bool operator>=(const Rational& x, const Rational& y) {
	int nok = FindLeastCommonMultiple(x.denominator, y.denominator);

	return nok / x.denominator * x.nominator >= nok / y.denominator * y.nominator;
}

export bool operator<=(const Rational& x, const Rational& y) {
	int nok = FindLeastCommonMultiple(x.denominator, y.denominator);

	return nok / x.denominator * x.nominator <= nok / y.denominator * y.nominator;
}

export std::ostream& operator<<(std::ostream& os, const Rational& x) {
	os << x.nominator << "/" << x.denominator;
	return os;
}

export Complex f(const Complex& u) {
	Complex a = Complex(1, 10);
	return 2 * u + a / u; 
}

export Rational f(const Rational& r) {
	Rational a(13, 10);
	return 2 * r + a / r;
}

export double f(double x) {
	double a = 1.3;
	return 2 * x + a / x;
}