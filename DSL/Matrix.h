#pragma once
#include <string>
#include <iostream>
#include <stack>
#include <algorithm>
#include <stdarg.h>
#include <vector>
#include <map>
#include <regex>
using namespace std;

class Matrix {
	vector<vector<double>> matrix;
	vector<int> dimensions;
	void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr);
	std::vector<std::string> split(const std::string& txt, char ch);
	vector<int> getMatrixDimensions(string line);
	vector<int> getMatrixIndeces(string line, int ignoreCharsAmount = 0, ...);
	vector<double> getMatrixNumbers(string line);
public:

	double& get(int i, int j) {
		return matrix[i][j];
	}

	double& operator[](string strIndeces);

	Matrix(string matrix);
	// Example:
	// Matrix m = Matrix("[[1,2,3]]")
	// m.get(0,0) // will return 1
	
	// Matrix m = Matrix("[[1,2,3],[3.5,10.2,77]")
	// m.get(1,1) // will return 10.2
	// m.get() - will return reference so you can change value using assigment
};


