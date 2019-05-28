#include <iostream>
#include <math.h>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

void calculate(string& equation);
string calculateExpr(string equation);
void solve(string& equation);

void removeSpaces(string& equation) {
	for (size_t i = 0; i < equation.length(); i++) {
		if (equation[i] == ' ') {
			equation.replace(i, 1, "");
		}
	}
}

bool hasOperator(string& equation, char oper) {
	for (size_t i = 0; i < equation.length(); i++) {
		if (equation[i] == oper) {
			return true;
		}
	}
	return false;
}

inline bool isOperator(const char& simb) { return (simb == '+' || simb == '-' || simb == '*' || simb == '/' || simb == '^'); }

bool hasOperators(const string & equation) {
	for (size_t i = 0; i < equation.length(); i++) {
		if (equation[i] == '-' && i == 0) {
			continue;
		}
		if (isOperator(equation[i])) {
			return true;
		}
	}
	return false;
}

double solve(double n1, double n2, char oper) {
	double result;
	switch (oper) {
	case '+':
		result = n1 + n2;
		break;
	case '-':
		result = n1 - n2;
		break;
	case '*':
		result = n1 * n2;
		break;
	case '/':
		result = n1 / n2;
		break;
	case '^':
		result = pow(n1, n2);
		break;
	default:
		cout << "Error" << endl;
		exit(1);
	}

	return result;
}

void calculateInBrackets(string & equation) {
	string inBrackets = "";
	bool bracketMet = false;
	size_t startIndex;


	for (size_t i = 0; i < equation.length(); i++) {
		if (equation[i] == '(') {
			bracketMet = true;
			startIndex = i;
			inBrackets = "";
		}
		if (bracketMet && equation[i] != '(' && equation[i] != ')') {
			inBrackets += equation[i];
		}

		if (equation[i] == ')') {
			break;
		}
	}
	int removingLength = inBrackets.length() + 2;
	calculate(inBrackets);
	equation.replace(startIndex, removingLength, inBrackets);

}

int solveWithPowerOperator(string & equation, string & firstNumber, string & secondNumber) {
	bool metOperator = false;

	int endIndex = 0;
	for (size_t i = 0; i < equation.length(); i++) {
		if (metOperator && isOperator(equation[i])) {
			endIndex = i - 1;
			break;
		}

		if (!isOperator(equation[i])) {
			firstNumber += equation[i];
		}

		if (isOperator(equation[i]) && equation[i] != '^') {
			firstNumber = "";
		}

		if (equation[i] == '^') {
			i++;
			metOperator = true;
		}

		if (metOperator) {
			secondNumber += equation[i];
		}
		endIndex = i;
	}

	return endIndex - firstNumber.length() - secondNumber.length();

}

std::pair<int, char> solveByOrderOfTwoOperators(string & equation, string & firstNumber, string & secondNumber, char oper1, char oper2) {

	bool metOperator = false;
	int endIndex = 0;
	char oper;
	for (size_t i = 0; i < equation.length(); i++) {

		if (metOperator && isOperator(equation[i])) {
			endIndex = i - 1;
			break;
		}

		if ((!isOperator(equation[i]) || i == 0) && !metOperator) {
			firstNumber += equation[i];
		}

		if (isOperator(equation[i]) && i != 0) {
			if (equation[i] == oper1 || equation[i] == oper2) {
				oper = equation[i];
				i++;
				metOperator = true;
			}
			else {
				firstNumber = "";
			}
		}

		if (metOperator) {
			secondNumber += equation[i];
		}
		endIndex = i;
	}
	return std::make_pair(endIndex - firstNumber.length() - secondNumber.length(), oper);
}

void solve(string & equation) {
	string firstNumber = "";
	string secondNumber = "";
	int startIndex;
	char oper;
	double n1, n2, result;

	if (hasOperator(equation, '^')) {
		oper = '^';
		startIndex = solveWithPowerOperator(equation, firstNumber, secondNumber);
	}
	else {
		if (hasOperator(equation, '*') || hasOperator(equation, '/')) {
			std::pair<int, char> tmp = solveByOrderOfTwoOperators(equation, firstNumber, secondNumber, '*', '/');

			startIndex = tmp.first;
			oper = tmp.second;
		}
		else {
			std::pair<int, char> tmp = solveByOrderOfTwoOperators(equation, firstNumber, secondNumber, '+', '-');

			startIndex = tmp.first;
			oper = tmp.second;
		}
	}

	n1 = atof(&firstNumber[0]);
	n2 = atof(&secondNumber[0]);
	int removingLength = firstNumber.length() + 1 + secondNumber.length();

	result = solve(n1, n2, oper);
	equation.replace(startIndex, removingLength, std::to_string(result));

}

void calculate(string& equation) {
	removeSpaces(equation);
	while (hasOperator(equation, '(')) {
		calculateInBrackets(equation);
	}
	while (hasOperators(equation)) {
		solve(equation);
	}
}

string calculateExpr(string equation) {
	removeSpaces(equation);
	while (hasOperator(equation, '(')) {
		calculateInBrackets(equation);
	}
	while (hasOperators(equation)) {
		solve(equation);
	}
	return equation;
}

