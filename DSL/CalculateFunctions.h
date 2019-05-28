#pragma once
#include <vector>
#include <memory>
#include "Vector.h"
#include <string>
#include <map>
#include "Matrix.h"
#include <sstream>
using namespace std;

extern map<string, shared_ptr<Vector>> vectorMap;
extern map<string, shared_ptr<double>> numberMap;
extern map<string, shared_ptr<Matrix>> matrixMap;


int calculateVectors(vector<string> args, string varName = "");
int calculateMatrices(vector<string> args, string varName = "");
int calculateNumbers(vector<string> args, double a, double b, string operation, string varName = "");
int calculateNumberVector(vector<string> args, double a, shared_ptr<Vector> b, string operation, string varName = "");
int calculateNumberMatrix(vector<string> args, double a, shared_ptr<Matrix> b, string operation, string varName = "");
bool isFloat(string number);
bool is_number(const std::string& s);


