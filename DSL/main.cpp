#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <stack>
#include "Vector.h"
#include <cctype>
#include <locale>
#include <unordered_map>
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

//		DECLARE
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

//		DECLARE Vector3 testVector (1,2,3)
//		PRINT testVector
//		COMPARE testVector1 < testVector2 
//		CALCULATE textVector1 + testVector2


map<string, shared_ptr<Vector>> vectorMap;
map<string, shared_ptr<double>> doubleMap;

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
std::vector<std::string> split(const std::string & txt, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	std::vector<std::string> strs;

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs;
}

shared_ptr<Vector> stringToVector2(string str) {
	string subStr = str.substr(1, str.size() - 1);
	auto points = split(subStr, ',');

	if (points.size() < 2) {
		return shared_ptr<Vector3>(nullptr);
	}


	return shared_ptr<Vector>(new Vector2(atof(points[0].c_str()), atof(points[1].c_str())));
}
shared_ptr<Vector> stringToVector3(string str) {
	string subStr = str.substr(1, str.size() - 2);
	auto points = split(subStr, ',');

	if (points.size() < 3) {
		return shared_ptr<Vector>(nullptr);
	}


	return shared_ptr<Vector>(new Vector3(atof(points[0].c_str()), atof(points[1].c_str()), atof(points[2].c_str())));
}


int calculateVariables(vector<string> args, string varName = "") {
	shared_ptr<Vector> resultV = nullptr;
	shared_ptr<double> resultD = nullptr;

	for (auto& c : args[2]) c = toupper(c);

	if (args[2] == "+") {
		resultV = vectorMap[args[1]]->add(vectorMap[args[3]]);
	}
	else if (args[2] == "-") {
		vectorMap[varName] = vectorMap[args[1]]->substr(vectorMap[args[3]]);
	}
	else if (args[2] == "DOT") {
		resultD = vectorMap[args[1]]->scalarMult(vectorMap[args[3]]);
	}
	else if (args[2] == "CROSS") {
		resultV = vectorMap[args[1]]->crossProd(vectorMap[args[3]]);
	}
	else if (args[2] == "LENGTH") {
		resultD = vectorMap[args[1]]->length();
	}
	else if (args[2] == "DIST") {
		resultD = vectorMap[args[1]]->dist(vectorMap[args[3]]);
	}
	else if (args[2] == "DIR") {
		resultD = vectorMap[args[1]]->direction(vectorMap[args[3]]);
	}
	else if (args[2] == "ANGLE") {
		resultD = vectorMap[args[1]]->angle(vectorMap[args[3]]);
	}


	if (resultV) {
		if (varName != "") vectorMap[varName] = resultV;

		cout << " Ans =	";
		resultV->print();
		cout << endl;
		return 0;
	}
	else if (resultD) {
		if (varName != "") doubleMap[varName] = resultD;
		cout << " Ans = " << *resultD;
		cout << endl;
		return 0;
	}



	return -6;
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
	else if (args[1] == "Vector3") {
		convertResult = stringToVector3(*varDataIt);
	}
	else if (args[1] == "Vector2") {
		convertResult = stringToVector2(*varDataIt);
	}
	else if (args[1] == "Number") {
		doubleMap[*varNameIt] = shared_ptr<double>(new double(atof(varDataIt->c_str())));
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
		dataToPrint.push_back(make_pair(str, vectorMap.find(str) != vectorMap.end() || doubleMap.find(str) != doubleMap.end()));
	}


	for (auto p : dataToPrint) {
		if (p.second) {

			string key = trim(p.first);
			if (vectorMap.find(key) != vectorMap.end()) {
				vectorMap[key]->print();
			}
			else if (doubleMap.find(key) != doubleMap.end()) {
				cout << *doubleMap[key] << "  ";
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

	if (args[0] == "DECLARE") {
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
	string pathToFile = argv[1];


	ifstream input(pathToFile);
	vector<string> code;
	//input >> std::noskipws;

	for (string line; getline(input, line);) {
		//cout << line << endl;
		code.push_back(line);
	}
	for (string line : code) {
		executeLine(line);
	}


	return 0;
}


// PRINT "hey " variable "  dsda "