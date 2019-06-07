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
		if (args.size() > 3) {
			if (args[3].find(type) != string::npos) {
				operandB = type == "Vector2" ? Vector2::parseVector(args[3]) : Vector3::parseVector(args[3]);
				foundB = true;
			}
		}
	}

	if (!foundA) {
		if (vectorMap.find(args[1]) == vectorMap.end()) {
			throw - 13;
		}
		operandA = vectorMap[args[1]];
	}
	if (args.size() > 3 && !foundB) {
		if (vectorMap.find(args[3]) == vectorMap.end()) {
			throw - 13;
		}
		operandB = vectorMap[args[3]];
	}
		
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
	shared_ptr<double> resultD;
	shared_ptr<Matrix> resultM;

	shared_ptr<Matrix> operandA;
	shared_ptr<Matrix> operandB;
	string type = "Matrix";
	auto it = args[1].find(type);

	bool foundA = false;
	bool foundB = false;

	if (it != string::npos) {
		string tmpMatrix = args[1].substr(it + 7, args[1].size() - it - 8);
		operandA = shared_ptr<Matrix>(new Matrix(tmpMatrix));
		foundA = true;
	}

	if (args.size() > 3) {
		it = args[3].find(type);

		if (it != string::npos) {
			string tmpMatrix = args[3].substr(it + 7, args[3].size() - it - 8);
			operandB = shared_ptr<Matrix>(new Matrix(tmpMatrix));
			foundB = true;
		}
	}

	if (!foundA) {
		if (matrixMap.find(args[1]) == matrixMap.end()) {
			throw - 13;
		}
		operandA = matrixMap[args[1]];
	}
	
	if (args.size() > 3 && !foundA) {
		if (matrixMap.find(args[3]) == matrixMap.end()) {
			throw - 13;
		}
		operandB = matrixMap[args[3]];
	}

	{
		if (args[2] == "+") {
			resultM = operandA->addition(operandB);
		}
		else if (args[2] == "-") {
			resultM = operandA->substraction(operandB);
		}
		else if (args[2] == "DET") {
			resultD = operandA->determinant();
		}
		else if (args[2] == "PROD") {
			resultM = operandA->product(operandB);
		}
		else if (args[2] == "TRACE") {
			resultD = operandA->trace();
		}
		else if (args[2] == "TRANSP") {
			resultM = operandA->transpose();
		}
		
	}
	// Printing result
	{
		if (resultM) {
			if (varName != "") matrixMap[varName] = resultM;
			cout << " Ans =	";
			resultM->print();
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
	shared_ptr<Matrix> resultM;
	shared_ptr<double> resultD;

	if (args[2] == "*") {
		resultM = b->scalarMult(a);
	}
	else if (args[2] == "POWER") {
		resultM = b->power(a);
	} 

	{
		if (resultM) {
			if (varName != "") matrixMap[varName] = resultM;
			cout << " Ans =	";
			resultM->print();
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
	return 0;
}

bool is_number(const std::string& s) {
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
