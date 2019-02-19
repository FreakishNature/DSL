#pragma once
#include <iostream>
#include <string>
#include <memory>
#include<math.h>
#define PI 3.14159265

using std::ostream;
using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;

struct Vector {
	virtual shared_ptr<double> dist(shared_ptr<Vector> v) {
		return nullptr;
	}
	virtual shared_ptr<Vector> add(shared_ptr<Vector> v) {
		return nullptr;
	}
	virtual shared_ptr<Vector> substr(shared_ptr<Vector> v) {
		return nullptr;
	}
	virtual shared_ptr<double> scalarMult(shared_ptr<Vector> v) {
		return nullptr;
	}
	virtual shared_ptr<Vector> crossProd(shared_ptr<Vector> v) {
		return nullptr;
	}
	virtual shared_ptr<double> length() {
		return nullptr;
	}
	virtual shared_ptr<double> direction(shared_ptr<Vector> v) {
		return nullptr;
	}
	virtual shared_ptr<double> angle(shared_ptr<Vector> v) {
		return nullptr;
	}



	bool operator <(Vector& v) {
		if (getType() != v.getType()) {
			cout << "Incompatble types" << endl;
			return false;
		}
		if (*(this->length()) < *(v.length())) {
			return true;
		}
		return false;
	}
	bool operator >(Vector& v) {
		if (getType() != v.getType()) {
			cout << "Incompatble types" << endl;
			return false;
		}

		if (*this->length() > * v.length()) {
			return true;
		}
		return false;
	}
	bool operator <=(Vector& v) {
		if (getType() != v.getType()) {
			cout << "Incompatble types" << endl;
			return false;
		}

		if (*this->length() <= *v.length()) {
			return true;
		}
		return false;
	}
	bool operator >=(Vector& v) {
		if (getType() != v.getType()) {
			cout << "Incompatble types" << endl;
			return false;
		}

		if (*this->length() >= *v.length()) {
			return true;
		}
		return false;
	}
	bool operator ==(Vector& v) {

		if (this->getType() != v.getType()) {
			cout << "Incompatble types" << endl;
			return false;
		}

		if (*this->length() == *v.length()) {
			return true;
		}
		return false;
	}
	bool operator !=(Vector& v) {
		if (getType() != v.getType()) {
			cout << "Incompatble types" << endl;
			return false;
		}

		if (*this->length() != *v.length()) {
			return true;
		}
		return false;
	}


	virtual string getType() { return "Vector"; }
	virtual void print() { cout << "" << endl; }

};

class Vector2 :public Vector {
protected:
	double x, y;
public:
	Vector2(double x, double y) :x(x), y(y) {}

	shared_ptr<double> dist(shared_ptr<Vector> v) override;
	shared_ptr<Vector> add(shared_ptr<Vector> v)  override;
	shared_ptr<Vector> substr(shared_ptr<Vector> v)  override;
	shared_ptr<double> scalarMult(shared_ptr<Vector> v)  override;
	shared_ptr<Vector> crossProd(shared_ptr<Vector> v)  override;
	shared_ptr<double> length() override;
	shared_ptr<double> direction(shared_ptr<Vector> v) override;
	shared_ptr<double> angle(shared_ptr<Vector> v) override;

	string getType() override { return "Vector2"; }
	void print() override { cout << "X = " << x << ", " << "Y = " << y << "  "; }
};

class Vector3 : public Vector2 {
	double z;

public:

	Vector3(double x, double y, double z) :Vector2(x, y), z(z) {	}

	shared_ptr<double> dist(shared_ptr<Vector> v) override;
	shared_ptr<Vector> add(shared_ptr<Vector> v)  override;
	shared_ptr<Vector> substr(shared_ptr<Vector> v)  override;
	shared_ptr<double> scalarMult(shared_ptr<Vector> v)  override;
	shared_ptr<Vector> crossProd(shared_ptr<Vector> v)  override;
	shared_ptr<double> length() override;
	shared_ptr<double> direction(shared_ptr<Vector> v) override;
	shared_ptr<double> angle(shared_ptr<Vector> v) override;

	void print() override { cout << "X = " << x << ", " << "Y = " << y << ", " << "Z = " << z << "  "; }
	string getType() override { return "Vector3"; }
};
