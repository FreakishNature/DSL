#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cctype>
#include <locale>
#include "CalculateFunctions.h"
#include <unordered_map>
#include "CalculateExpression.h"
using namespace std;

// VARIABLE DECLARATION CONTROL (IF IN DOUBLE MAP SHOULD NOT BE IN VECTOR MAP, CHECK NAME DECLARATION )

// ERRORS CODE

//		error -1 -- not enough arguments in line
//		error -2 -- not enough arguments in declaring vector
//		error -3 -- not enough arguments in printing vector
//		error -4 -- syntax error
//		error -5 -- no such type
//		error -6 -- error in calculation

// COMMANDS

//		SET
//		CALCULATE 
//		PRINT
//		COMPARE

// CALCULATE OPERATIONS

// + - CROSS DOT ANGLE DIR LENGTH DIST

// COMPARE OPERATIONS

// <= >= < > != ==

// Data types

// Number Vector2 Vector3

// Syntax

//		SET Vector3 testVector (1,2,3)
//		PRINT testVector
//		COMPARE testVector1 < testVector2 
//		CALCULATE textVector1 + testVector2
map<string, shared_ptr<Vector>> vectorMap;
map<string, shared_ptr<double>> numberMap;
map<string, shared_ptr<Matrix>> matrixMap;


vector<string> calculateExpr(vector<string> args) {
	string expr;
	for (int i = 1; i < args.size(); i++) {
		expr.append(args[i] + " ");
	}
	string res = calculateExpr(expr);
	args = { "CALCULATE","0", "+",res };

	return args;
}


string getVariableType(string variable) {
	if (vectorMap.find(variable) != vectorMap.end()) {
		return "Vector";
	}
	else if(numberMap.find(variable) != numberMap.end() || is_number(variable)) {
		return "Number";
	} 
	else if(matrixMap.find(variable) != matrixMap.end()) {
		return "Matrix";
	} 

	throw - 10; // Variable not found
}

void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr)
{
	size_t pos = data.find(toSearch);

	while (pos != std::string::npos)
	{
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

static inline string trim(std::string s) {
	ltrim(s);
	rtrim(s);
	return s;
}

vector<string> splitWithQuotes(string str) {
	str = trim(str);
	vector<string> strings;
	string tmp = "";
	bool quoteStarted = false;
	bool metSpace = true;
	for (auto it = str.begin(); it != str.end(); ++it) {
		if (*it == '\"') {
			if (quoteStarted) {
				strings.push_back(tmp);
				tmp = "";
			}
			quoteStarted = !quoteStarted;

			++it;
			if (it == str.end()) {
				break;
			}

		}

		if (isspace(*it) && !quoteStarted) {
			if (*prev(it) == '\"') {
				continue;
			}
			strings.push_back(tmp);
			tmp = "";
			continue;
		}

		tmp.push_back(*it);

	}
	strings.push_back(tmp);
	return strings;
}
bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
string removeWhiteSpaces(string str) {
	std::string::iterator new_end = std::unique(str.begin(), str.end(), BothAreSpaces);
	str.erase(new_end, str.end());
	return str;
}




int calculateVariables(vector<string> args, string varName = "") {
	string operandA = args[1];
	if (args.size() < 4) {
		if (operandA.find("Vector") != std::string::npos || vectorMap.find(args[1]) != vectorMap.end()) {
			return calculateVectors(args);
		}
		if (operandA.find("Matrix") != std::string::npos || matrixMap.find(args[1]) != matrixMap.end()) {
			return calculateVectors(args);
		}
	}
	string operandB = (args.size() > 3 ? args[3] : "");
	// NUMBER proccesing
	shared_ptr<double> operandADouble(nullptr);
	if (isFloat(operandA)) {
		operandADouble = shared_ptr <double>(new double(atof(operandA.c_str())));
	}

	shared_ptr<double> operandBDouble(nullptr);
	if (isFloat(operandB)) {
		operandBDouble = shared_ptr <double>(new double(atof(operandB.c_str())));
	}

	if (numberMap.find(operandA) != numberMap.end()) {
		operandADouble = numberMap[operandA];
	}

	if (numberMap.find(operandB) != numberMap.end()) {
		operandBDouble = numberMap[operandB];
	}

	if (operandBDouble && operandADouble) {
		calculateNumbers(args,*operandADouble, *operandBDouble,args[2],varName);
	}

	// VECTOR proccessing

	if (args[1].find("Vector") != string::npos ||
		vectorMap.find(args[1]) != vectorMap.end() &&
		args[3].find("Vector") != string::npos &&
		vectorMap.find(args[3]) != vectorMap.end()) {

		calculateVectors(args, varName);
		return 0;
	}


	if (operandBDouble) {
		double number = *operandBDouble;
		shared_ptr<Vector> v(nullptr);

		vector<string> dataTypes = { "Vector2" , "Vector3" }; // TO think about Number type
		// Deteterminating type of variables
		for (string type : dataTypes) {
			if (args[1].find(type) != string::npos) {
				v = type == "Vector2" ? Vector2::parseVector(args[1]) : Vector3::parseVector(args[1]);
			}
		}

		if (vectorMap.find(operandA) != vectorMap.end()) {
			// not foun
			v = vectorMap[operandA];
		}



		if (v) {
			calculateNumberVector(args, number, v, args[2], varName);
		}

	}

	if (operandADouble) {
		double number = *operandADouble;
		shared_ptr<Vector> v(nullptr);

		vector<string> dataTypes = { "Vector2" , "Vector3" }; // TO think about Number type
		// Deteterminating type of variables
		for (string type : dataTypes) {
			if (args.size() > 2)
				if (args[3].find(type) != string::npos) {
					v = type == "Vector2" ? Vector2::parseVector(args[3]) : Vector3::parseVector(args[3]);
				}

		}

		if (vectorMap.find(operandB) != vectorMap.end()) {
			v = vectorMap[operandB];
		}

		if (v) {
			calculateNumberVector(args, number, v, args[2], varName);
		}


	}

	if (
		(
			args[1].find("Vector") != string::npos ||
			vectorMap.find(args[1]) != vectorMap.end()
		) &&
		(
			args[3].find("Vector") != string::npos ||
			vectorMap.find(args[3]) != vectorMap.end())
		) {
		
		calculateVectors(args, varName);
		return 0;
	}
	// Matrix proccesing
	

	if (operandADouble) {
		double number = *operandADouble;
		shared_ptr<Matrix> m(nullptr);

		if (matrixMap.find(operandB) != matrixMap.end()) {
			// not foun
			m = matrixMap[operandB];

			calculateNumberMatrix(args, number, m, args[2], varName);
		}
	}

	if (operandBDouble) {
		double number = *operandBDouble;
		shared_ptr<Matrix> m(nullptr);

		if (matrixMap.find(operandA) != matrixMap.end()) {
			// not foun
			m = matrixMap[operandA];

			calculateNumberMatrix(args, number, m, args[2], varName);
		}


	}

	if (matrixMap.find(operandA) != matrixMap.end() && matrixMap.find(operandB) != matrixMap.end()) {
		calculateMatrices(args, varName);
	}
	/*
	string resultType = args[0];

	string typeOperandA = getVariableType(args[1]);
	string typeOperandB = getVariableType(args[3]);

	if (typeOperandA == typeOperandB && typeOperandA == "Vector") { calculateVectors(args, varName); }
	if (typeOperandA == typeOperandB && typeOperandA == "Number") { calculateNumbers(args, varName); }*/
	
	return 0;
}



int compareVectors(vector<string> args) {
	if (args[2] == "==") {
		if (*vectorMap[args[1]] == *vectorMap[args[3]]) {
			cout << "TRUE" << endl;
		}
		else {
			cout << "FALSE" << endl;
		}
	}
	else if (args[2] == "<=") {
		if (*vectorMap[args[1]] <= *vectorMap[args[3]]) {
			cout << "TRUE" << endl;
		}
		else {
			cout << "FALSE" << endl;
		}
	}
	else if (args[2] == ">=") {
		if (*vectorMap[args[1]] >= *vectorMap[args[3]]) {
			cout << "TRUE" << endl;
		}
		else {
			cout << "FALSE" << endl;
		}
	}
	else if (args[2] == "<") {
		if (*vectorMap[args[1]] < *vectorMap[args[3]]) {
			cout << "TRUE" << endl;
		}
		else {
			cout << "FALSE" << endl;
		}
	}
	else if (args[2] == ">") {
		if (*vectorMap[args[1]] > * vectorMap[args[3]]) {
			cout << "TRUE" << endl;
		}
		else {
			cout << "FALSE" << endl;
		}
	}
	else if (args[2] == "!=") {
		if (*vectorMap[args[1]] != *vectorMap[args[3]]) {
			cout << "TRUE" << endl;
		}
		else {
			cout << "FALSE" << endl;
		}
	}
	return 0;

}
int declareVariable(vector<string> args) {
	auto equalsSignIterator = find(args.begin(), args.end(), "=");

	if (equalsSignIterator == args.end()) { return -4; }
	auto varNameIt = prev(equalsSignIterator, 1);
	auto varDataIt = next(equalsSignIterator, 1);
	if (varDataIt == args.end() || varNameIt == args.end()) { return -4; }

	shared_ptr<Vector> convertResult;
	for (auto& c : *varDataIt) c = toupper(c);

	if (*varDataIt == "CALCULATE") {
		calculateVariables(vector<string>(varDataIt, args.end()), *varNameIt);
		return 0;
	}

	if (*varDataIt == "CALCULATEXPR") {
		int codeResult = calculateVariables(calculateExpr(vector<string>(varDataIt, args.end())),*varNameIt);
		return 0;
	}

	else if (args[1] == "Vector3") {
		convertResult = stringToVector3(*varDataIt);
	}
	else if (args[1] == "Vector2") {
		convertResult = stringToVector2(*varDataIt);
	}
	else if (args[1] == "Number") {
		numberMap[*varNameIt] = shared_ptr<double>(new double(atof(varDataIt->c_str())));
		return 0;
	}
	else if (args[1] == "Matrix") {
		matrixMap[*varNameIt] = shared_ptr<Matrix>(new Matrix(*varDataIt));
		return 0;
	}
	else {
		return -5;
	}

	if (!convertResult) {
		return -2;
	}
	vectorMap[*varNameIt] = convertResult;
}

int printVariable(vector<string> args, string command) {

	if (count_if(command.begin(), command.end(), [](char a) {
		return a == '\"';
	}) % 2 != 0) {

		return -4;
	}

	vector<pair<string, bool>> dataToPrint;

	for (string str : args) {
		dataToPrint.push_back(
			make_pair(str, 
				vectorMap.find(str) != vectorMap.end() || 
				numberMap.find(str) != numberMap.end() ||
				matrixMap.find(str) != matrixMap.end()
			));
	}


	for (auto p : dataToPrint) {
		if (p.second) {

			string key = trim(p.first);
			if (vectorMap.find(key) != vectorMap.end()) {
				vectorMap[key]->print();
			}
			else if (numberMap.find(key) != numberMap.end()) {
				cout << *numberMap[key] << "  ";
			}
			else if (matrixMap.find(key) != matrixMap.end()) {
				matrixMap[key]->print();
			}
		}
		else {
			cout << p.first;
		}
	}
	cout << endl;

	return 0;
}

int executeLine(string line) {
	string lineForArgs = trim(line);
	//lineForArgs = removeWhiteSpaces(line);
	
	auto args = splitWithQuotes(lineForArgs);

	if (args.size() < 2) { return -1; }

	for (auto& c : args[0]) c = toupper(c);

	if (args[0] == "SET") {
		int codeResult = declareVariable(args);
		if (codeResult < 0) { cout << "error code : " << codeResult << endl; }
	}
	else if (args[0] == "PRINT") {
		int codeResult = printVariable(vector<string>(++args.begin(), args.end()), line);
		if (codeResult < 0) { cout << "error code : " << codeResult << endl; }
	}
	else if (args[0] == "CALCULATE") {
		int codeResult = calculateVariables(args);
		if (codeResult < 0) { cout << "error code : " << codeResult << endl; }
	}
	else if (args[0] == "CALCULATEXPR") {
		int codeResult = calculateVariables(calculateExpr(args));
		if (codeResult < 0) { cout << "error code : " << codeResult << endl; }
	}
	else if (args[0] == "COMPARE") {
		compareVectors(args);
	}

}


int main(int argc, char** argv) {
	if (argc < 2) {
		while (true) {
			string line;
			cout << "  >>  ";
			getline(cin, line);
			if (line == "exit") {
				break;
			}
			executeLine(line);
		}

		return 0;
	}

	//string pathToFile = argv[1];


	//ifstream input(pathToFile);
	//vector<string> code;
	////input >> std::noskipws;

	//for (string line; getline(input, line);) {
	//	//cout << line << endl;
	//	code.push_back(line);
	//}
	//for (string line : code) {
	//	executeLine(line);
	//}
	Matrix m("[[[1,1.45,1]],[[1,1.45,1]]]");
	auto p = m.getMatrixSize();
	cout << p.first << "  " << p.second;

	return 0;
}

