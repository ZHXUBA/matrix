#include <iostream>
#include "matrix.h"
#include "process_matrix.h"

using matrix::MatrixData;
using matrix::Matrix;
using matrix::transpose;
using matrix::__test_inverse;
using std::begin;
using std::end;
using std::cout;

int main() {
	int test_data[] = { 1, 1, 1, 0, 0, 1, 1, 0, 0};

	//Matrix<int> m1(5, 5);
	//Matrix<int>::iter be = m1.begin(), en = m1.end();
	//while (be != en) {
	//	*be = rand() % 10;
	//	++be;
	//}

	Matrix<double> m1(5, 5);

	//m1.importData(begin(test_data), end(test_data));
	m1.importData({
		3, 1, 0, 0, 0,
		0, 3, 1, 0, 0, 
		0, 0, 3, 1, 0,
		0, 0, 0, 3, 1,
		0, 0, 0, 0, 3,
		});

	Matrix<double>m2 = __test_inverse(m1);

	cout << m1;

	cout << m2;

	cout << m2 * m1;

	return 0;
}