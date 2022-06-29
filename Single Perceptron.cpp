#include <bits/stdc++.h>
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
	Matrix(float** arr, int r, int c) {
		rows = r;
		cols = c;

		data = new float[rows * cols];
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				set(arr[i][j], i, j);
			}
		}
	}

	// Basic matrix operations
	void operator=(Matrix mat) {
		rows = mat.rows;
		cols = mat.cols;
		data = new float[rows * cols];

		for(int i = 0; i < rows * cols; i++) {
			data[i] = mat.data[i];
		}
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

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < mat.cols; j++) {
				temp = 0;
				for(int k = 0; k < cols; k++) {
					temp += get(i, k) * mat.get(k, j);
				}

				ret.set(temp, i, j);
			}
		}

		return ret;
	}

	// Scalar operations
	friend Matrix scalarMul(Matrix, Matrix);
	friend Matrix scalarDiv(Matrix, Matrix);

	// Basic operations with float
	Matrix operator+(float x) {
		Matrix ret = Matrix(rows, cols);
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				ret.set(get(i, j) + x, i, j);
			}
		}
		return ret;
	}
	Matrix operator-(float x) {
		Matrix ret = Matrix(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				ret.set(get(i, j) - x, i, j);
			}
		}
		return ret;
	}
	Matrix operator*(float x) {
		Matrix ret = Matrix(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				ret.set(get(i, j) * x, i, j);
			}
		}
		return ret;
	}
	Matrix operator/(float x) {
		Matrix ret = Matrix(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				ret.set(get(i, j) / x, i, j);
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

// Matrix scalar operations
Matrix scalarMul(Matrix a, Matrix b) {
	if(!(a.cols == b.cols && a.rows == b.rows)) {
		throw new MatrixOperationException();
	}

	Matrix ret = Matrix(a.rows, a.cols);
	for(int i = 0; i < a.rows; i++) {
		for(int j = 0; j < a.cols; j++) {
			ret.set(a.get(i, j) * b.get(i, j), i, j);
		}
	}
	return ret;
}
Matrix scalarDiv(Matrix a, Matrix b) {
	if (!(a.cols == b.cols && a.rows == b.rows)) {
		throw new MatrixOperationException();
	}

	Matrix ret = Matrix(a.rows, a.cols);
	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			ret.set(a.get(i, j) / b.get(i, j), i, j);
		}
	}
	return ret;
}

// Perceptron class
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
		inputs = Matrix(1, inputSize);
		weights = Matrix(inputSize);
		output = Matrix(1, 1);

		srand(time(NULL));

		for (int i = 0; i < inputSize; i++) {
			weights.set((float)rand() / (float)RAND_MAX, i, 0);
		}
		bias =  (float)rand() / (float)RAND_MAX;
	}
	Perceptron(int inSize) {
		learningRate = 0.1;
		inputSize = inSize;
		inputs = Matrix(1, inputSize);
		weights = Matrix(inputSize);
		output = Matrix(1, 1);

		srand(time(NULL));

		for (int i = 0; i < inputSize; i++) {
			weights.set((float)rand() / (float)RAND_MAX, i, 0);
		}
		bias = (float)rand() / (float)RAND_MAX;
	}
	Perceptron(int inSize, float learn) {
		learningRate = learn;
		inputSize = inSize;
		inputs = Matrix(1, inputSize);
		weights = Matrix(inputSize);
		output = Matrix(1, 1);

		srand(time(NULL));

		for (int i = 0; i < inputSize; i++) {
			weights.set((float)rand() / (float)RAND_MAX, i, 0);
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

	// ML Essential Functions
	void predictSingle(Matrix input) {
		inputs = input;
		output = (input * weights) + bias;
		cout << input << output;
	}
	void trainSingle(Matrix input, Matrix out) {
		predictSingle(input);
		error = output.get(0, 0) - out.get(0, 0);

		Matrix delta = Matrix(1, inputSize);
		delta = scalarMul(inputs.transpose(), weights) * (error * learningRate);

		weights = weights - delta;
		bias = bias - error * learningRate;
	}
	void train(Matrix input[], Matrix out[], int tuples, int epochs = 500) {
		float avgError;

		cout << "\nStarting training: " << tuples << " tuples over " << epochs << " epochs\n";
		for(int e = 1; e <= epochs; e++) {
			avgError = 0;
			for (int i = 0; i < tuples; i++) {
				trainSingle(input[i], out[i]);
				avgError += abs(error) / (float)tuples;
			}

			cout << "\nEpoch: " << e << " / " << epochs << ": complete";
			cout << "\nError: " << avgError;
		}
	}
	Matrix* predict(Matrix input[], int tuples) {
		Matrix *ret = new Matrix[tuples];

		for(int i = 0; i < tuples; i++) {
			predictSingle(input[i]);
			ret[i] = output;
		}

		return ret;
	}

	// Debug print operation
	friend ostream& operator<<(ostream&, Perceptron);
};

// Print operations
ostream& operator<<(ostream& out, Matrix mat) {
	for(int i = 0; i < mat.rows; i++) {
		for(int j = 0; j < mat.cols; j++) {
			out << mat.get(i, j) << " ";
		}
		out << "\n";
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


// Implementation Helper functions
void initTruthTable(Matrix table[], int tuples) {
	for(int i = 0; i < tuples; i++) {
		string bin = bitset<4>(i).to_string();
		
		for(int j = 0; j < 4; j++) {
			if(bin[j] == '0') {
				table[i].set(0.0, 0, j);
			} else {
				table[i].set(1.0, 0, j);
			}
		}
	}
}

// Sample implementation for concept check
int main() {
	Perceptron p = Perceptron();

	// Initialising perceptron input pin for binary logical statement table
	float **inp[16];
	Matrix pin[16];
	for(int i = 0; i < 16; i++) {
		inp[i] = new float*[1];
		inp[i][0] = new float[4];
		pin[i] = Matrix(inp[i], 1, 4);
	}

	initTruthTable(pin, 16);


	/*
		Initialising perceptron output pout for the following function:
		(A && B) || (C && D) && !(B || D)
	*/
	float **out[16];
	Matrix pout[16];
	for(int i = 0; i < 16; i++) {
		out[i] = new float*[1];
		out[i][0] = new float[1];

		bool a = pin[i].get(0, 0);
		bool b = pin[i].get(0, 1);
		bool c = pin[i].get(0, 2);
		bool d = pin[i].get(0, 3);
		bool res = (a && b) || (c && d) && !(b || d);

		pout[i] = Matrix(1, 1);
		if(res) {
			pout[i].set(1.0, 0, 0);
		} else {
			pout[i].set(0.0, 0, 0);
		}
	}

	Matrix *predictions = p.predict(pin, 16);
	for(int i = 0; i < 16; i++) {
		cout << &predictions[i] << "\n";
	}
	p.train(pin, pout, 16, 40);

	/*predictions = p.predict(pin, 16);
	for(int i = 0; i < 16; i++) {
		cout << &predictions[i] << "\n";
	}*/
	return 0;
}