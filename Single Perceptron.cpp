#include <iostream>
#include <exception>
#include <math.h>
using namespace std;

// Useful Exceptions
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

template <typename t>
class Matrix {
	private:
	t *data;
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
	void operator=(Matrix<t> mat) {
		data = mat.data;
		rows = mat.rows;
		cols = mat.cols;
	}
	Matrix<t> operator+(Matrix<t> mat) {
		if(rows != mat.rows || cols != mat.cols) {
			throw MatrixOperationException;
		}
		Matrix<t> ret = mat;
		for(int i = 0; i < rows * cols; i++) {
			ret.data[i] = data[i] + mat.data[i];
		}
		return ret;
	}
	Matrix<t> operator-(Matrix<t> mat) {
		if(rows != mat.rows || cols != mat.cols) {
			throw MatrixOperationException;
		}
		Matrix<t> ret = mat;
		for(int i = 0; i < rows * cols; i++) {
			ret.data[i] = data[i] - mat.data[i];
		}
		return ret;
	}
	// Incomplete Function
	Matrix<t> operator*(Matrix<t> mat) {
		if(cols != mat.rows) {
			throw MatrixOperationException;
		}
		Matrix<t> ret = new Matrix<t>(rows, mat.cols);

		return ret;
	}


	// Location Access operation
	t get(int r, int c) {
		if(r >= rows || r < 0 || c >= cols || c < 0) {
			throw MatrixAccessException;
		}
		int i = r * cols + c;
		return data[i];
	}
	void set(t value, int r, int c) {
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