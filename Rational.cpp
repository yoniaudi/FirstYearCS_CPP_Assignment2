#include "Rational.h"

// Constructor Functions :

Rational::Rational()
{
	this->_denominator.setCoeff(0, 1);
}

Rational::Rational(const Rational& r)
{
	setNom(r.getNom());
	setDenom(r.getDenom());
}

Rational::Rational(const Polynomial& nom, const Polynomial& denom) : _numerator(nom)
{
	setDenom(denom);
}

Rational::~Rational() {}

// Set Functions :

void Rational::setNom(const Polynomial& nom)
{
	this->_numerator = nom;
}

void Rational::setDenom(const Polynomial& denom)
{
	int realDegree = (int)denom.getDegree(1);
	double ceoff = denom.getCoeff(realDegree);

	if (realDegree == 0 && ceoff == 0.0) {
		this->_denominator = denom;
		this->_denominator.setCoeff(0, 1);
	}
	else {
		this->_denominator = denom;
	}
}

// Get Functions :

const Polynomial& Rational::getNom() const
{
	return this->_numerator;
}

const Polynomial& Rational::getDenom() const
{
	return this->_denominator;
}

// General Functions :

void Rational::print() const
{
	getNom().print();
	cout << "--------------------------" << endl;
	getDenom().print();
}

// Operator Overloading Functions :

Rational& Rational::operator+(const Rational& r) const
{
	Rational* result;

	if (this->getDenom() == r.getDenom())
		result = new Rational(this->getNom() + r.getNom(), this->getNom());
	else {
		if (this->getDenom().getDegree(1) == 0.0 && this->getDenom().getCoeff(0) == 1.0)
			result = new Rational(this->getNom() * r.getDenom() + r.getNom(), r.getDenom());
		else if (r.getDenom().getDegree(1) == 0.0 && r.getDenom().getCoeff(0) == 1.0)
			result = new Rational(this->getNom() + (this->getDenom() * r.getNom()), this->getDenom());
		else {
			result = new Rational((this->getNom() * r.getDenom()) + (this->getDenom() * r.getNom()),
				this->getDenom() * r.getDenom());
		}
	}

	return *result;
}

Rational& Rational::operator+(const Polynomial& p) const
{
	Rational* result = new Rational(this->getNom() + (this->getDenom() * p), this->getDenom());
	return *result;
}

Rational& operator+(const Polynomial& p, const Rational& r)
{
	return r + p;
}

Rational& Rational::operator+(double num) const
{
	Rational* result = new Rational(this->getNom() + (this->getDenom() * num), this->getDenom());
	return *result;
}

Rational& operator+(double num, const Rational& r)
{
	return r + num;
}

Rational& Rational::operator-(const Rational& r) const
{
	Rational* result;

	if (this->getDenom() == r.getDenom())
		result = new Rational(this->getNom() - r.getNom(), r.getDenom());
	else {
		if (this->getDenom().getDegree(1) == 0.0 && this->getDenom().getCoeff(0) == 1)
			result = new Rational(this->getNom() * r.getDenom() - r.getNom(), r.getDenom());
		else if (r.getDenom().getDegree(1) == 0.0 && r.getDenom().getCoeff(0) == 1)
			result = new Rational(this->getNom() - (this->getDenom() * r.getNom()), this->getDenom());
		else {
			result = new Rational(this->getNom() * r.getDenom() - this->getDenom() * r.getNom(),
				this->getDenom() * r.getDenom());
		}
	}

	return *result;
}

Rational& Rational::operator-(const Polynomial& p) const
{
	Rational* result = new Rational(this->getNom() - (this->getDenom() * p), this->getDenom());
	return *result;
}

Rational& operator-(const Polynomial& p, const Rational& r)
{
	Rational* result = new Rational(p * r.getDenom() - r.getNom(), r.getDenom());
	return *result;
}

Rational& Rational::operator-(double num) const
{
	Rational* result = new Rational(this->getNom() - (this->getDenom() * num), this->getDenom());
	return *result;
}

Rational& operator-(double num, const Rational& r)
{
	Rational* result = new Rational(r.getDenom() * num - r.getNom(), r.getDenom());
	return *result;
}

Rational& Rational::operator*(const Rational& r) const
{
	Rational* result = new Rational(this->getNom() * r.getNom(), this->getDenom() * r.getDenom());
	return *result;
}

Rational& Rational::operator*(const Polynomial& p) const
{
	Rational* result = new Rational(this->getNom() * p, this->getDenom());
	return *result;
}

Rational& operator*(const Polynomial& p, const Rational& r)
{
	return r * p;
}

Rational& Rational::operator*(double num) const
{
	Rational* result = new Rational(this->getNom() * num, this->getDenom());
	return *result;
}

Rational& operator*(double num, const Rational& r)
{
	return r * num;
}

Rational& Rational::operator=(const Rational& r)
{
	if (this != &r) {
		this->setNom(r.getNom());
		this->setDenom(r.getDenom());
	}
	return *this;
}

ostream& operator<<(ostream& out, const Rational& r)
{
	out << "numerator=" << r.getNom();
	out << "--------------------------" << endl;
	out << "denominator=" << r.getDenom();
	return out;
}