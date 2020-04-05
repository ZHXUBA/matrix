#include<iostream>
#include"matrix.h"
#include"process_matrix.h"

using matrix::MatrixData;
using matrix::Matrix;
using matrix::transpose;
using std::begin;
using std::end;
using std::cout;

int main() {
	int test_data[] = { 1, 1, 1, 0, 0, 1};

	Matrix<int> m1(2, 3);
	m1.importData(begin(test_data), end(test_data));

	Matrix<double> m2(2, 3);
	m2.importData({
		2, 2, 2, 
		1, 0, 1,
		});
	m2.reshape(3, 2);

	cout << m1 << m2;
	
	Matrix<double> m12 = (0.5* m2);

	cout << m12;

	cout << transpose(m12);

	return 0;
}