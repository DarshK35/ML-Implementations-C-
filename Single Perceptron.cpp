#include <exception>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
		{{5, 7, 9},
		{2, 4, 5}}
	is stored as {5, 7, 9, 2, 4, 5}
*/

class Matrix {
	private:
	float *data;
	int rows, cols;

	public:
	// Constructors
	Matrix() {
		Matrix mat = Matrix(5);
		this->data = mat.data;
		this->rows = mat.rows;
		this->cols = mat.cols;
	}
	Matrix(int n) {
		rows = n;
		cols = 1;

		data = new float[rows * cols];
	}
	Matrix(int r, int c) {
		rows = r;
		cols = c;

		data = new float[rows * cols];
	}
	Matrix(int* arr[], int r, int c) {
		rows = r;
		cols = c;

		data = new float[rows * cols];
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				set(arr[i][j], i, j);
			}
		}
	}

	// Basic operations
	void operator=(Matrix mat) {
		data = mat.data;
		rows = mat.rows;
		cols = mat.cols;
	}
	Matrix operator+(Matrix mat) {
		if(rows != mat.rows || cols != mat.cols) {
			throw new MatrixOperationException();
		}
		Matrix ret = mat;
		for(int i = 0; i < rows * cols; i++) {
			ret.data[i] = data[i] + mat.data[i];
		}
		return ret;
	}
	Matrix operator-(Matrix mat) {
		if(rows != mat.rows || cols != mat.cols) {
			throw new MatrixOperationException();
		}
		Matrix ret = mat;
		for(int i = 0; i < rows * cols; i++) {
			ret.data[i] = data[i] - mat.data[i];
		}
		return ret;
	}
	Matrix operator*(Matrix mat) {
		if(cols != mat.rows) {
			throw new MatrixOperationException();
		}
		int temp;
		Matrix ret = Matrix(rows, mat.cols);

		for(int i = 0; i < ret.rows; i++) {
			for(int j = 0; j < ret.cols; j++) {
				temp = 0;
				for(int k = 0; k < cols; k++) {
					temp += get(i, k) * mat.get(k, j);
				}

				ret.set(temp, i, j);
			}
		}

		return ret;
	}

	// Other Operations
	Matrix transpose() { 
		Matrix ret = Matrix(cols, rows);

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				ret.set(get(i, j), j, i);
			}
		}

		return ret;
	}

	// Location Access operation
	float get(int r, int c) {
		if(r >= rows || r < 0 || c >= cols || c < 0) {
			throw new MatrixAccessException();
		}
		int i = r * cols + c;
		return data[i];
	}
	void set(float value, int r, int c) {
		if(r >= rows || r < 0 || c >= cols || c < 0) {
			throw new MatrixAccessException();
		}
		int i = r * cols + c;
		data[i] = value;
	}

	// Debug Printing operation
	friend ostream& operator<<(ostream&, Matrix);
};

class Perceptron {
	private:
	Matrix inputs, weights, output;
	float bias, learningRate;
	float error;

	int inputSize;

	public:
	// Constructors
	Perceptron() {
		learningRate = 0.1;
		inputSize = 4;
		inputs = Matrix(inputSize);
		weights = Matrix(1, inputSize);
		output = Matrix(1, 1);

		srand(time(NULL));

		for (int i = 0; i < inputSize; i++)
		{
			weights.set((float)rand() / (float)RAND_MAX, 0, i);
		}
		bias = (float)rand() / (float)RAND_MAX;
	}
	Perceptron(int inSize) {
		learningRate = 0.1;
		inputSize = inSize;
		inputs = Matrix(inputSize);
		weights = Matrix(1, inputSize);
		output = Matrix(1, 1);

		srand(time(NULL));

		for (int i = 0; i < inputSize; i++)
		{
			weights.set((float)rand() / (float)RAND_MAX, 0, i);
		}
		bias = (float)rand() / (float)RAND_MAX;
	}
	Perceptron(int inSize, float learn) {
		learningRate = learn;
		inputSize = inSize;
		inputs = Matrix(inputSize);
		weights = Matrix(1, inputSize);
		output = Matrix(1, 1);

		srand(time(NULL));

		for (int i = 0; i < inputSize; i++) {
			weights.set((float)rand() / (float)RAND_MAX, 0, i);
		}
		bias = (float)rand() / (float)RAND_MAX;
	}

	// Helper Functions
	float sigmoidActivation(float x) {
		return 1.0 / (1.0 + expf(-x));
	}
	float sigmoidDerivative(float x) {
		return x * (1.0 - x);
	}

	// ML Essential Functions - INCOMPLETE
	void predictSingle(Matrix input) {
		inputs = input;

	}
	void trainSingle(Matrix input, Matrix output) {

	}
	void train(Matrix input[], Matrix output[], int tuples) {

	}
	void predict(Matrix input[], int tuples) {

	}

	// Debug print operation
	friend ostream& operator<<(ostream&, Perceptron);
};

// Debug Print operations
ostream& operator<<(ostream& out, Matrix mat) {
	string o;
	out << "\nRows: " << mat.rows;
	out << "\nCols: " << mat.cols << "\n";
	for(int i = 0; i < mat.rows; i++) {
		o = "";
		for(int j = 0; j < mat.cols; j++) {
			o += to_string(mat.get(i, j)) + " ";
		}
		o += "\n";
		out << o;
	}
}
ostream& operator<<(ostream& out, Perceptron per) {
	out << "Bias: " << per.bias << "\n";
	out << "Learning Rate: " << per.learningRate << "\n";
	out << "Input size: " << per.inputSize << "\n";
	out << "Input Matrix:" << per.inputs;
	out << "Weight Matrix:" << per.weights;
	out << "Output Matrix: " << per.output;
}

// Sample implementation for concept check
int main() {
	Perceptron p = Perceptron(4);
	cout << p;
	return 0;
}