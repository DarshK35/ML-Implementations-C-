#include <iostream>
#include <exception>
#include <math.h>
using namespace std;

// Useful Exceptions
struct MatrixInverseException : exception {
	const char *what() const noexcept {
		return "Matrix inapplicable for operation";
	}
};
struct MatrixOperationException : exception {
	const char* what() const noexcept {
		return "Invalid Matrix sizes";
	}
};
struct MatrixAccessException : exception {
	const char* what() const noexcept {
		return "Array index out of bounds";
	}
};

/*
	Matrix is stored as a single long array storing elements row-wise
	Eg:
		[5 7 9]
		[2 4 5]
	is stored as [5 7 9 2 4 5]
*/

class Matrix {
	private:
	float *data;
	int rows, cols;

	public:
	// Constructors
	Matrix() {
		this = new Matrix(5);
	}
	Matrix(int n) {
		rows = n;
		cols = 1;

		data = new t[rows * cols];
	}
	Matrix(int r, int c) {
		rows = r;
		c *(r - 1)
	}

	// Basic operations
	void operator=(Matrix mat) {
		data = mat.data;
		rows = mat.rows;
		cols = mat.cols;
	}
	Matrix operator+(Matrix mat) {
		if(rows != mat.rows || cols != mat.cols) {
			throw MatrixOperationException;
		}
		Matrix ret = mat;
		for(int i = 0; i < rows * cols; i++) {
			ret.data[i] = data[i] + mat.data[i];
		}
		return ret;
	}
	Matrix operator-(Matrix mat) {
		if(rows != mat.rows || cols != mat.cols) {
			throw MatrixOperationException;
		}
		Matrix ret = mat;
		for(int i = 0; i < rows * cols; i++) {
			ret.data[i] = data[i] - mat.data[i];
		}
		return ret;
	}
	Matrix operator*(Matrix mat) {
		if(cols != mat.rows) {
			throw MatrixOperationException;
		}
		int temp;
		Matrix ret = new Matrix(rows, mat.cols);

		for(int i = 0; i < ret.rows; i++) {
			for(int j = 0; j < ret.cols; j++) {
				temp = 0;
				for(int k = 0; k < cols; k++) {
					temp += get(i, k) * mat.get(k, j);
				}

				ret.set(i, j) = temp;
			}
		}

		return ret;
	}

	// Other Operations
	Matrix transpose() { 
		Matrix ret = new Matrix(cols, rows);

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				ret.set(j, i) = get(i, j);
			}
		}

		return ret;
	}

	// Location Access operation
	float get(int r, int c) {
		if(r >= rows || r < 0 || c >= cols || c < 0) {
			throw MatrixAccessException;
		}
		int i = r * cols + c;
		return data[i];
	}
	void set(float value, int r, int c) {
		if(r >= rows || r < 0 || c >= cols || c < 0) {
			throw MatrixAccessException;
		}
		int i = r * cols + c;
		data[i] = value;
	}
};

class perceptron {
	private:
	Matrix<float> inputs, weights, output;
	float bias;

	public:
	perceptron() {
		inputs = Matrix<float>(5);
		weights =  Matrix<float>(5);
		bias = 0;
	}

	perceptron(int inSize) {

	}

};