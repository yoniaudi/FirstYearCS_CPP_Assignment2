#include "Polynomial.h"

double Polynomial::_maxDegree = 0;
double* Polynomial::_maxDegreeArr = new double[1]();
int Polynomial::_polyCount = 0;

// Constructor Functions :

Polynomial::Polynomial(int degree)
{
	setId();
	setDefaultDegree(degree);
}

Polynomial::Polynomial(double* arr, int degree)
{
	setId();
	setDefaultDegree(degree);
	setArr(arr, degree + 1);
}

Polynomial::Polynomial(const Polynomial& p)
{
	setId();
	setDefaultDegree(p.getDegree(0));
	setArr(p.getArr(), p.getArrSize());
}

Polynomial::~Polynomial()
{
	int arrSize = _polyCount--;
	double realDegree = getDegree(1);

	// Update Max Degree array before destruction :
	for (int i = 0; i < arrSize; i++) {
		if (_maxDegreeArr[i] == realDegree) {
			_maxDegreeArr[i] = _maxDegreeArr[arrSize - 1];
			_maxDegreeArr = (double*)realloc(_maxDegreeArr, sizeof(double) * _polyCount);
			break;
		}
	}

	if (this->_arr != NULL) delete[] this->_arr;
}

// Set Functions :

void Polynomial::setDefaultDegree(double newDefaultDegree)
{
	if (newDefaultDegree >= 0.0) {
		int oldArrSize = getArrSize();
		int newArrSize = (int)newDefaultDegree + 1;
		double oldDefaultDegree = getDegree(0);
		double* newArr = NULL, * oldArr = NULL;

		if (newDefaultDegree == 0.0)
			newArr = new double[1]();
		else {
			oldArr = getArr();
			newArr = new double[newArrSize]();
			if (oldArr != NULL) copy(oldArr, oldArr + oldArrSize, newArr);
		}

		setArr(newArr, newArrSize);
		updateRealDegree();
		this->_defaultDegree = newDefaultDegree;
	}
}

void Polynomial::setCoeff(int index, double value)
{
	int defaultDegree = (int)getDegree(0);

	if (index >= 0 && index <= defaultDegree) {
		this->_arr[index] = value;
	}
	else if (index > defaultDegree) {
		setDefaultDegree(index);
		this->_arr[index] = value;
	}
	updateRealDegree();
}

void Polynomial::setArr(double* newArr, int newArrSize)
{
	if (newArr != NULL) {
		if (this->_arr == NULL) this->_arr = new double[newArrSize]();
		else if (this->_arrSize < newArrSize)
			this->_arr = (double*)realloc(this->_arr, newArrSize * sizeof(double));

		for (int i = 0; i < newArrSize; i++) {
			this->_arr[i] = newArr[i];
		}
	}
	setArrSize(newArrSize);
	updateRealDegree();
}

void Polynomial::setArrSize(int arrSize)
{
	this->_arrSize = arrSize;
}

void Polynomial::setId()
{
	this->_id = ++_polyCount;
	_maxDegreeArr = (double*)realloc(_maxDegreeArr, sizeof(double) * _polyCount);
	_maxDegreeArr[_polyCount - 1] = 0;
}

// Get Functions :

double Polynomial::getMaxDegree()
{
	double biggestDegree = 0;

	for (int i = 0; i < _polyCount; i++)
		if (biggestDegree < _maxDegreeArr[i])
			biggestDegree = _maxDegreeArr[i];

	_maxDegree = biggestDegree;
	return _maxDegree;
}

double* Polynomial::getMaxDegreeArr()
{
	return _maxDegreeArr;
}

int Polynomial::getPolyCount()
{
	return _polyCount;
}

double Polynomial::getDegree(bool realDegree) const
{
	if (realDegree) return this->_realDegree;
	return this->_defaultDegree;
}

double Polynomial::getCoeff(int index) const
{
	if (index >= 0 && index <= (this->_arrSize - 1))
		return this->_arr[index];
	return 0;												// Flag return 0 value -> cout << "Index doesn't exist" << endl;
}

double* Polynomial::getArr() const
{
	return this->_arr;
}

int Polynomial::getId() const
{
	return this->_id;
}

int Polynomial::getArrSize() const
{
	return this->_arrSize;
}

int Polynomial::getPolynomialNumber() const
{
	return this->_id;
}

void Polynomial::print() const
{
	int realDegree = (int)getDegree(1);
	double ceoff = getCoeff(realDegree);

	cout << "Polynomial = ";
	if (realDegree == 0 && ceoff == 0.0) cout << "0" << endl;
	else {
		for (int i = 0; i <= realDegree; i++) {
			if (i == 0) {
				cout << getCoeff(i);
				continue;
			}
			cout << "+(" << getCoeff(i) << ")*X^" << i;
		}
		cout << endl;
	}
}

void Polynomial::updateRealDegree()
{
	double oldRealDegree = this->_realDegree;

	// Updates Real degree :
	int i = getArrSize() - 1;
	if (i > -1) {
		for (; i > 0; i--) {
			if (this->_arr[i] != 0.0) {
				this->_realDegree = (double)i;
				break;
			}
		}
		if (this->_arr[i] == 0.0 && i == 0)
			this->_realDegree = (double)i;
	}

	double newRealDegree = this->_realDegree;

	// Updates Global Max degree :
	if (newRealDegree != oldRealDegree)
		updateMaxDegreeArr(newRealDegree, oldRealDegree);
}

void Polynomial::updateMaxDegreeArr(double newRealDegree, double oldRealDegree)
{
	int i, arrSize = _polyCount;

	for (i = 0; i < arrSize; i++)
		if (_maxDegreeArr[i] == oldRealDegree) {
			_maxDegreeArr[i] = newRealDegree;
			break;
		}
}

// Operator Overloading Functions :

Polynomial& Polynomial::operator+(const Polynomial& p) const
{
	Polynomial* result = new Polynomial();
	int thisArrSize = this->getArrSize(), otherArrSize = p.getArrSize();
	double thisRealDegree = this->getDegree(1), otherRealDegree = p.getDegree(1);

	int newArrSize = thisArrSize > otherArrSize ? thisArrSize : otherArrSize;
	double realDegree = thisRealDegree > otherRealDegree ? thisRealDegree : otherRealDegree;
	double* newArr = new double[newArrSize]();

	for (int i = 0; i <= realDegree; i++) {
		if (i <= thisRealDegree && i <= otherRealDegree) newArr[i] = this->getCoeff(i) + p.getCoeff(i);
		else if (i <= thisRealDegree) newArr[i] = this->getCoeff(i);
		else if (i <= otherRealDegree) newArr[i] = p.getCoeff(i);
	}
	result->setArr(newArr, newArrSize);
	result->setDefaultDegree(newArrSize -1);
	
	return *result;
}

Polynomial& Polynomial::operator+(double num) const
{
	Polynomial* result = new Polynomial(*this);
	result->setCoeff(0, this->getCoeff(0) + num);
	return *result;
}

Polynomial& operator+(double num, const Polynomial& p)
{
	return (p + num);
}

Polynomial& Polynomial::operator-(const Polynomial& p) const
{
	double num = 0;
	int thisArrSize = this->getArrSize(), otherArrSize = p.getArrSize();
	double thisRealDegree = this->getDegree(1), otherRealDegree = p.getDegree(1);

	Polynomial* result = new Polynomial();
	int newArrSize = thisArrSize > otherArrSize ? thisArrSize : otherArrSize;
	double realDegree = thisRealDegree > otherRealDegree ? thisRealDegree : otherRealDegree;
	double* newArr = new double[newArrSize]();

	for (int i = 0; i <= realDegree; i++) {
		if (i <= thisRealDegree && i <= otherRealDegree) {
			num = this->getCoeff(i) - p.getCoeff(i);
			if (num == 0.0 || num == -0.0) newArr[i] = 0;
			else newArr[i] = num;
		}
		else if (i <= thisRealDegree) newArr[i] = this->getCoeff(i);
		else if (i <= otherRealDegree) {
			num = p.getCoeff(i);
			if (num == 0.0) newArr[i] = 0;
			else newArr[i] = -num;
		}
	}

	result->setArr(newArr, newArrSize);
	result->setDefaultDegree(newArrSize - 1);
	return *result;
}

Polynomial& Polynomial::operator-(double num) const
{
	Polynomial* result = new Polynomial(*this);
	result->setCoeff(0, this->getCoeff(0) - num);
	return *result;
}

Polynomial& operator-(double num, const Polynomial& p)
{
	Polynomial* result = new Polynomial();
	*result = (p - num) * (-1);
	int size = result->getArrSize();
	for (int i = 0; i < size; i++)
		if (result->getArr()[i] == -0.0)
			result->setCoeff(i, 0);

	return *result;
}

Polynomial& Polynomial::operator*(const Polynomial& p) const
{
	double number = 0, realDegree1 = this->getDegree(1), realDegree2 = p.getDegree(1);
	int i, j, newArrSize = (int)(realDegree1 + realDegree2 + 1);
	double* newPolyArr = new double[newArrSize]();

	for (i = 0; i < realDegree1 + 1; i++) {
		if (this->getCoeff(i) == 0) continue;
		for (j = 0; j < realDegree2 + 1; j++) {
			if (p.getCoeff(j) == 0) continue;
			number = (this->getCoeff(i) * p.getCoeff(j));
			newPolyArr[i + j] += (number == -0.0 ? 0 : number);						// Fix -0 in array
		}
	}

	Polynomial* result = new Polynomial(newPolyArr, newArrSize - 1);

	return *result;
}

Polynomial& Polynomial::operator*(double num) const
{
	int realDegree = (int)this->getDegree(1);
	int arrSize = this->getArrSize();
	double number = 0, * newArr = new double[arrSize]();

	for (int i = 0; i <= realDegree; i++) {
		newArr[i] = num * this->getArr()[i];
		if (newArr[i] == -0.0)
			newArr[i] = 0;
	}

	Polynomial* result = new Polynomial(*this);
	result->setArr(newArr, arrSize);
	return *result;
}

Polynomial& operator*(double num, const Polynomial& p)
{
	return (p * num);
}

Polynomial& Polynomial::operator=(const Polynomial& p)
{
	if (this != &p) {
		this->_defaultDegree = p.getDegree(0);
		this->setArr(p.getArr(), p.getArrSize());
		this->setId();
	}
	return *this;
}

Polynomial& Polynomial::operator=(double number)
{
	this->setDefaultDegree(0);
	this->setCoeff(0, number);
	return *this;
}

bool Polynomial::operator==(const Polynomial& p) const
{
	int thisRealDegree = this->getDegree(1), otherRealDegree = p.getDegree(1);

	if (thisRealDegree != otherRealDegree) return false;
	else
		for (int i = 0; i < thisRealDegree + 1; i++)
			if (this->getCoeff(i) != p.getCoeff(i))
				return false;

	return true;
}

double& Polynomial::operator[](int i)
{
	if (i >= 0 && i < this->getArrSize())
		return this->getArr()[i];
	else {
		cout << "Error: Polynomial[" << i << "] -> Index \"" << i << "\" is out of range." << endl;
		throw ("Error: Index is out of range");				// Check this condition
	}
}

const double Polynomial::operator[](int i) const
{
	double realDegree = this->getDegree(1);
	if (0 <= i && i <= (int)realDegree)
		return this->getCoeff(i);
	return 0;
}

ostream& operator<<(ostream& out, const Polynomial& p)
{
	int realDegree = (int)p.getDegree(1);
	double ceoff = p.getCoeff(realDegree);

	out << "Polynomial = ";
	if (realDegree == 0 && ceoff == 0.0) out << "0" << endl;
	else {
		for (int i = 0; i <= realDegree; i++) {
			if (i == 0) {
				out << p.getCoeff(i);
				continue;
			}
			out << "+(" << p.getCoeff(i) << ")*X^" << i;
		}
		out << endl;
	}
	return out;
}