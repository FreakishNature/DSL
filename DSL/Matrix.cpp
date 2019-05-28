#include "Matrix.h"


void Matrix::findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr)
{
	size_t pos = data.find(toSearch);

	while (pos != std::string::npos)
	{
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

std::vector<std::string> Matrix::split(const std::string& txt, char ch)
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

vector<int> Matrix::getMatrixDimensions(string line)
{
	vector<int> dimensions;
	regex expr("\\[((\\d+(.\\d+)?),?)+\\]");
	do {
		std::vector<std::string> res;
		for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), expr);
			i != std::sregex_iterator();
			++i)
		{
			std::smatch m = *i;
			res.push_back(m.str());
		}

		/*for (auto i : res) {
			std::cout << i << std::endl;
		}*/
		dimensions.push_back(count_if(res[0].begin(), res[0].end(), [](char ch) { return ch == ','; }) + 1);
		line = regex_replace(line, expr, "1");
		//cout << line << endl;
	} while (line.length() > 2);

	if (dimensions.size() != 2) {
		throw - 7;
	}

	return dimensions;
}

vector<int> Matrix::getMatrixIndeces(string line, int ignoreCharsAmount, ...)
{
	vector<int> matrixNumbers;
	string number;

	// getting array of ignored chars
	char* ignoredChars = new char[ignoreCharsAmount];
	va_list args;
	va_start(args, ignoreCharsAmount);
	for (int i = 0; i < ignoreCharsAmount; i++) {
		ignoredChars[i] = va_arg(args, char);
	}
	// Getting numbers
	for (auto it = line.begin(); it != line.end(); ++it) {
		if (isdigit(*it)) {
			number.push_back(*it);
		}
		else if (!number.empty()) {
			for (int i = 0; i < ignoreCharsAmount; i++) {
				// Continue loop on next iteration 
				if (*it == ignoredChars[i]) {
					delete[] ignoredChars;
					throw - 7;
				}
			}
			matrixNumbers.push_back(atof(number.c_str()));
			number = "";
		}
	}

	delete[] ignoredChars;

	return matrixNumbers;
}

vector<double> Matrix::getMatrixNumbers(string line)
{
	vector<double> numbers;
	findAndReplaceAll(line, "]", "");
	findAndReplaceAll(line, "[", "");
	auto strNumbers = split(line, ',');

	for (string number : strNumbers) {
		numbers.emplace_back(atof(number.c_str()));
	}
	return numbers;
}

shared_ptr<Matrix> Matrix::product(shared_ptr<Matrix> m)
{
	if (this->matrix[0].size() != m->matrix.size()) {
		throw - 11;
	}

	shared_ptr<Matrix> res(new Matrix(this->matrix.size(), m->matrix[0].size()));

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < m->matrix[0].size(); j++) {
			double sum = 0;
			for (int k = 0; k < matrix[0].size(); k++) {
				sum += matrix[i][k] * m->matrix[k][j];
			}
			res->get(i, j) = sum;
		}
	}

	return res;
}

shared_ptr<Matrix> Matrix::scalarMult(double n)
{
	shared_ptr<Matrix> res(new Matrix(matrix.size(), matrix[0].size()));
	for (int i = 0; i < this->matrix.size(); i++) {
		for (int j = 0; j < this->matrix[i].size(); j++) {

			res->get(i, j) = n * matrix[i][j];
		}
	}
	return res;
}

shared_ptr<Matrix> Matrix::substraction(shared_ptr<Matrix> m)

{
	if (this->matrix.size() != m->matrix.size() || this->matrix[0].size() != m->matrix[0].size()) {
		cout << "Substraction is not possible "; // sau throw error
	}

	shared_ptr<Matrix> res(new Matrix(matrix.size(), matrix[0].size()));

	for (int i = 0; i < this->matrix.size(); i++) {
		for (int j = 0; j < this->matrix[i].size(); j++)
		{
			res->get(i, j) = this->get(i, j) - m->get(i, j);
		}
	}
	return res;

}
shared_ptr<Matrix> Matrix::addition(shared_ptr<Matrix> m)
{
	if (this->matrix.size() != m->matrix.size() || this->matrix[0].size() != m->matrix[0].size()) {
		cout << "Addition not possible "; // sau throw error
	}

	shared_ptr<Matrix> res(new Matrix(matrix.size(), matrix[0].size()));

	for (int i = 0; i < this->matrix.size(); i++) {
		for (int j = 0; j < this->matrix[i].size(); j++)
		{
			res->get(i, j) = this->get(i, j) + m->get(i, j);
		}
	}

	return res;
}
double& Matrix::operator[](string strIndeces)
{
	auto indeces = getMatrixIndeces(strIndeces);

	if (indeces.size() != 2) {
		throw - 8;
	}

	return get(indeces[0], indeces[1]);
}

void Matrix::print()
{
	cout << "[" << endl;
	for (auto row : matrix) {
		cout << "\t[";
		for (int i = 0; i < row.size(); i++) {
			cout << row[i] << ((i != (row.size() - 1)) ? ",\t" : "");
		}
		cout << "]" << endl;
	}
	cout << "]";
}

Matrix::Matrix(string matrix)
{
    dimensions = getMatrixDimensions(matrix);
    this->matrix.resize(dimensions[1]);
    for (vector<double>& row : this->matrix) {
        row.resize(dimensions[0]);
    }
    auto numbers = getMatrixNumbers(matrix);
    for (int i = 0; i < this->matrix.size(); i++) {
        for (int j = 0; j < this->matrix[i].size(); j++) {
            int index = i * this->matrix[0].size() + j;
            this->matrix[i][j] = numbers[index];
        }
    }
}
Matrix::Matrix(int n, int m)
{
    this->matrix.resize(n);
    for (vector<double>& row : this->matrix) {
        row.resize(m);
    }
}

