#include "Vector.h"



shared_ptr<double> Vector2::dist(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector2") {
		return nullptr;
	}
	shared_ptr<Vector2> convertedV = shared_ptr<Vector2>(std::dynamic_pointer_cast<Vector2>(v));

	return shared_ptr<double>(new double(sqrt((convertedV->x - x) * (convertedV->x - x) + (convertedV->y - y) * (convertedV->y - y))));
}

shared_ptr<Vector> Vector2::add(shared_ptr<Vector> v)
{

	if (v->getType() != "Vector2") {
		return nullptr;
	}
	shared_ptr<Vector2> convertedV = shared_ptr<Vector2>(std::dynamic_pointer_cast<Vector2>(v));

	return shared_ptr<Vector>(new Vector2(this->x + convertedV->x, this->y + convertedV->y));
}

shared_ptr<Vector> Vector2::substr(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector2") {
		return nullptr;
	}
	shared_ptr<Vector2> convertedV = shared_ptr<Vector2>(std::dynamic_pointer_cast<Vector2>(v));

	return shared_ptr<Vector>(new Vector2(this->x - convertedV->x, this->y - convertedV->y));
}

shared_ptr<double> Vector2::scalarMult(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector2") {
		return nullptr;
	}

	shared_ptr<Vector2> convertedV = shared_ptr<Vector2>(std::dynamic_pointer_cast<Vector2>(v));
	return shared_ptr<double>(new double(this->x * convertedV->x + (this->y * convertedV->y)));
}

shared_ptr<Vector> Vector2::crossProd(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector2") {
		return nullptr;
	}

	return shared_ptr<Vector>();
}

shared_ptr<double> Vector2::length()
{

	double res = sqrt(pow(x, 2) + pow(y, 2));
	return shared_ptr<double>(new double(res));
}

shared_ptr<double> Vector2::direction(shared_ptr<Vector> v)
{
	double theta = atan(y / x) * 180 / PI;
	cout << "		";
	if (x >= 0 && y >= 0) {
		theta = theta;
		cout << "The angle is in the 1st quadrant" << endl;
	}
	else if (x < 0 && y >= 0) {
		theta = 180 - theta;
		cout << "The angle is in the 2nd quadrant" << endl;
	}
	else if (x < 0 && y < 0) {
		theta = 180 + theta;
		cout << "The angle is in the 3rd quadrant" << endl;
	}
	else {
		theta = 360 - theta;
		cout << "The angle is in the 4th quadrant" << endl;
	}

	return shared_ptr<double>(new double(theta));
}

shared_ptr<double> Vector2::angle(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector2") {
		return nullptr;
	}

	double  dotP = *scalarMult(v);
	double v1 = *this->length();
	double v2 = *v->length();

	return shared_ptr<double>(new double(acos(dotP / (v1 * v2)) * 180 / PI));
}

shared_ptr<double> Vector3::dist(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector3") {
		return nullptr;
	}
	shared_ptr<Vector3> convertedV = shared_ptr<Vector3>(std::dynamic_pointer_cast<Vector3>(v));

	return shared_ptr<double>(new double(sqrt((convertedV->x - x) * (convertedV->x - x) + (convertedV->y - y) * (convertedV->y - y) + (convertedV->z - z) * (convertedV->z - z))));
}

shared_ptr<Vector> Vector3::add(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector3") {
		return nullptr;
	}
	shared_ptr<Vector3> convertedV = shared_ptr<Vector3>(std::dynamic_pointer_cast<Vector3>(v));

	return shared_ptr<Vector>(new Vector3(this->x + convertedV->x, this->y + convertedV->y, this->z + convertedV->z));
}

shared_ptr<Vector> Vector3::substr(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector3") {
		return nullptr;
	}
	shared_ptr<Vector3> convertedV = shared_ptr<Vector3>(std::dynamic_pointer_cast<Vector3>(v));


	return shared_ptr<Vector>(new Vector3(this->x - convertedV->x, this->y - convertedV->y, this->z - convertedV->z));
}

shared_ptr<double> Vector3::scalarMult(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector3") {
		return nullptr;
	}

	return shared_ptr<double>();
}

shared_ptr<Vector> Vector3::crossProd(shared_ptr<Vector> v)
{
	if (v->getType() != "Vector3") {
		return nullptr;
	}

	return shared_ptr<Vector>();
}

shared_ptr<double> Vector3::length()
{

	double res = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	return shared_ptr<double>(new double(res));
}

shared_ptr<double> Vector3::direction(shared_ptr<Vector> v)
{
	// UPGRAADE
	double theta = atan(y / x) * 180 / PI;
	cout << "		";
	if (x >= 0 && y >= 0) {
		theta = theta;
		cout << "The angle is in the 1st quadrant" << endl;
	}
	else if (x < 0 && y >= 0) {
		theta = 180 - theta;
		cout << "The angle is in the 2nd quadrant" << endl;
	}
	else if (x < 0 && y < 0) {
		theta = 180 + theta;
		cout << "The angle is in the 3rd quadrant" << endl;
	}
	else {
		theta = 360 - theta;
		cout << "The angle is in the 4th quadrant" << endl;
	}

	return shared_ptr<double>(new double(theta));
}

shared_ptr<double> Vector3::angle(shared_ptr<Vector> v)
{
	return shared_ptr<double>();
}

