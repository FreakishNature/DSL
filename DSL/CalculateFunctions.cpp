#include "CalculateFunctions.h"

int calculateVectors(vector<string> args, string varName) {
	shared_ptr<Vector> resultV = nullptr;
	shared_ptr<double> resultD = nullptr;

	// In operation operandA = vectorMap[args[1]] , creates an empty object with key args[1] 
	bool foundA = false;
	bool foundB = false;

	shared_ptr<Vector> operandA;
	shared_ptr<Vector> operandB;

	vector<string> dataTypes = { "Vector2" , "Vector3" }; // TO think about Number type
	// Deteterminating type of variables
	for (string type : dataTypes) {
		if (args[1].find(type) != string::npos) {
			operandA = type == "Vector2" ? Vector2::parseVector(args[1]) : Vector3::parseVector(args[1]);
			foundA = true;
		}
		if (args.size() > 2) {
			if (args[3].find(type) != string::npos) {
				operandB = type == "Vector2" ? Vector2::parseVector(args[3]) : Vector3::parseVector(args[3]);
				foundB = true;
			}
		}
	}

	if (!foundA) {
		operandA = vectorMap[args[1]];
	}
	if (args.size() > 3 && !foundB)
		operandB = vectorMap[args[3]];

	for (auto& c : args[2]) c = toupper(c);

	// Detecting operationg and calculating
	{
		if (args[2] == "+") {
			resultV = operandA->add(operandB);
		}
		else if (args[2] == "-") {
			resultV = operandA->substr(operandB);
		}
		else if (args[2] == "DOT") {
			resultD = operandA->dotMult(operandB);
		}
		else if (args[2] == "CROSS") {
			resultV = operandA->crossProd(operandB);
		}
		else if (args[2] == "LENGTH") {
			resultD = operandA->length();
		}
		else if (args[2] == "DIST") {
			resultD = operandA->dist(operandB);
		}
		else if (args[2] == "DIR") {
			resultD = operandA->direction(operandB);
		}
		else if (args[2] == "ANGLE") {
			resultD = operandA->angle(operandB);
		}
	}
	// Printing result
	{
		if (resultV) {
			if (varName != "") vectorMap[varName] = resultV;
			cout << " Ans =	";
			resultV->print();
			cout << endl;
			return 0;
		}
		else if (resultD) {
			if (varName != "") numberMap[varName] = resultD;
			cout << " Ans = " << *resultD;
			cout << endl;
			return 0;
		}
	}

	throw - 6;
}

int calculateMatrices(vector<string> args, string varName)
{
	return 0;
}

bool isFloat(string myString) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

int calculateNumbers(vector<string> args,double a,double b,string operation, string varName)
{
	double operandA = isFloat(args[1]) ? atof(args[1].c_str()) : *numberMap[args[1]];
	double operandB = isFloat(args[3]) ? atof(args[3].c_str()) : *numberMap[args[3]];
	shared_ptr<double> result;
	// Detecting operationg and calculating
	{
		if (args[2] == "+") {
			result = shared_ptr<double>(new double(operandA + operandB));
		}
		else if (args[2] == "-") {
			result = shared_ptr<double>(new double(operandA - operandB));
		}
		else if (args[2] == "/") {
			result = shared_ptr<double>(new double(operandA / operandB));
		}
		else if (args[2] == "*") {
			result = shared_ptr<double>(new double(operandA * operandB));
		}
		
	}
	if (!result) { return -6; }
	if (varName != "") numberMap[varName] = result;
	cout << " Ans = " << *result;
	cout << endl;

	return 0;
}

int calculateNumberVector(vector<string> args, double a, shared_ptr<Vector> b, string operation, string varName)
{
	shared_ptr<Vector> resultVector;
	shared_ptr<double> resultNumber;

	if (operation == "*") {
		 resultVector = b->scalarMult(a);
	}

	{
		if (resultVector) {
			if (varName != "") vectorMap[varName] = resultVector;
			cout << " Ans =	";
			resultVector->print();
			cout << endl;
			return 0;
		}
		else if (resultNumber) {
			if (varName != "") numberMap[varName] = resultNumber;
			cout << " Ans = " << *resultNumber;
			cout << endl;
			return 0;
		}
	}
	return -6;
}

int calculateNumberMatrix(vector<string> args, double a, shared_ptr<Matrix> b, string operation, string varName)
{
	return 0;
}

bool is_number(const std::string& s) {
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
