#pragma once
#include "Polynomial.h"
class Rational
{
private:

	Polynomial _numerator;
	Polynomial _denominator;

public:
	// Constructor Functions :
	Rational();
	Rational(const Rational&);
	Rational(const Polynomial&, const Polynomial&);
	~Rational();

	// Set Functions :
	void setNom(const Polynomial&);
	void setDenom(const Polynomial&);

	// Get Functions :
	const Polynomial& getNom() const;
	const Polynomial& getDenom() const;

	// General Functions :
	void print() const;

	// Operator Overloading Functions :
	Rational& operator+(const Rational&) const;
	Rational& operator+(const Polynomial&) const;
	friend Rational& operator+(const Polynomial&, const Rational&);
	Rational& operator+(double) const;
	friend Rational& operator+(double, const Rational&);

	Rational& operator-(const Rational&) const;
	Rational& operator-(const Polynomial&) const;
	friend Rational& operator-(const Polynomial&, const Rational&);
	Rational& operator-(double) const;
	friend Rational& operator-(double, const Rational&);

	Rational& operator*(const Rational&) const;
	Rational& operator*(const Polynomial&) const;
	friend Rational& operator*(const Polynomial&, const Rational&);
	Rational& operator*(double num) const;
	friend Rational& operator*(double, const Rational&);

	Rational& operator=(const Rational&);
	friend ostream& operator<<(ostream&, const Rational&);
};