#include <iostream>
#include <string>
#pragma once
using namespace std;
class Polynomial
{
private:

	static double _maxDegree;
	static double* _maxDegreeArr;
	static int _polyCount;

	int _id;
	int _arrSize = 0;
	double _defaultDegree = 0;
	double _realDegree = 0;
	double* _arr = NULL;

public:
	// Constructor Functions :
	Polynomial(int = 0);
	Polynomial(double*, int);
	Polynomial(const Polynomial&);
	~Polynomial();

	// Set Functions :
	void setId();
	void setDefaultDegree(double);
	void setCoeff(int, double);
	void setArr(double*, int);
	void setArrSize(int);

	// Get Functions :
	static int getPolyCount();
	static double getMaxDegree();
	static double* getMaxDegreeArr();

	int getId() const;
	int getArrSize() const;
	int getPolynomialNumber() const;
	double getDegree(bool) const;
	double getCoeff(int) const;
	double* getArr() const;

	// General Functions :
	void print() const;
	void updateRealDegree();
	void updateMaxDegreeArr(double, double);

	// Operator Overloading Functions :
	Polynomial& operator+(const Polynomial&) const;
	Polynomial& operator+(double) const;
	friend Polynomial& operator+(double, const Polynomial&);
	Polynomial& operator-(const Polynomial&) const;
	Polynomial& operator-(double) const;
	friend Polynomial& operator-(double, const Polynomial&);
	Polynomial& operator*(const Polynomial&) const;
	Polynomial& operator*(double num) const;
	friend Polynomial& operator*(double, const Polynomial&);
	Polynomial& operator=(const Polynomial&);
	Polynomial& operator=(double);
	bool operator==(const Polynomial&) const;
	double& operator[](int);
	const double operator[](int) const;
	friend ostream& operator<<(ostream&, const Polynomial&);

};