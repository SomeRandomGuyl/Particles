#include "Matrices.h"
namespace Matrices
{

//Construct a matrix of the specified size.
//Initialize each element to 0.
Matrix::Matrix(int _rows, int _cols) {
	rows = _rows;
	cols = _cols;
	a.resize(rows);
	for (int i=0; i<rows; i++) {
		a[i].resize(cols);
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			a.at(r).at(c) = 0;
		}
	}
}

Matrix operator+(const Matrix& a, const Matrix& b) {
	// ensure matrices can actually be added
	if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
		// THROW "inner dimensions don't agree"
		throw runtime_error("Error: dimensions must agree");
	}


	Matrix result(a.getRows(), a.getCols());

	for (int r = 0; r < result.getRows(); r++) {
		for (int c = 0; c < result.getCols(); c++) {
			result(r, c) = a(r, c) + b(r, c);
		}
	}

	return result;
}


Matrix operator*(const Matrix& a, const Matrix& b) {

	// ensure matrices can actually be multiplied
	if (a.getCols() != b.getRows()) {
		throw runtime_error("Error: dimensions must agree");
	}

	Matrix result(a.getRows(), b.getCols());

	// formatted as c(i,k) in pseudocode
	// ahh i see. i see. ok
	double currentValue = 0; // accumulator

	// oh good god the formula
	for (int i = 0; i < a.getRows(); i++) {
		for (int k = 0; k < b.getCols(); k++) {

			currentValue = 0;
			for (int j = 0; j < a.getCols(); j++) {
				currentValue += a(i, j) * b(j, k);
			}
			// guessing this goes here?
			result(i, k) = currentValue;

		}
	}

	return result;
}



bool operator==(const Matrix& a, const Matrix& b) {

	// ensure matrices can actually be compared
	if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
		return false;
	}


	for (int r = 0; r < a.getRows(); r++) {
		for (int c=0; c < a.getCols(); c++) {
			if (abs(a(r, c) -  b(r, c)) > 0.001) { return false; }
		}
	}

	return true;
}


bool operator!=(const Matrix& a, const Matrix& b) {
	// ensure they can be compared
	if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
		return true;
	}

	for (int r=0; r<a.getRows(); r++) {
		for (int c=0; c<a.getCols(); c++) {
			if (abs(a(r, c) - b(r, c)) > 0.001) {
				return true;
			}
		}
	}

	return false;

}

// errmmmmm., yeahgh i forgot this one
ostream& operator<<(ostream& os, const Matrix& a) {
	// separate cols by spaces, rows by \n, seems to be in char format
	for (int r=0; r<a.getRows(); r++) {
		for (int c=0; c<a.getCols(); c++) {
			os << setw(10) << a(r, c) << ' ';
		}
		os << '\n';
	}
	return os;
}



RotationMatrix::RotationMatrix(double theta) : Matrix(2,2) {
	//Matrix R(2, 2);
	a.at(0).at(0) = cos(theta);
	a.at(0).at(1) = -sin(theta);
	a.at(1).at(1) = cos(theta);
	a.at(1).at(0) = sin(theta);
}


ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
	//Matrix S(2, 2);
	a.at(0).at(0) = scale;
	a.at(1).at(0) = 0;
	a.at(1).at(1) = scale;
	a.at(0).at(1) = 0;
}


TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {
	//Matrix T(2, nCols);

	for (int i = 0; i < nCols; i++) {
		a.at(0).at(i) = xShift;
		a.at(1).at(i) = yShift;
	}
}

}


