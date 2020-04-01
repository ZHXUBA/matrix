#include<iostream>
#include"matrix.h"

using matrix::MatrixData;
using matrix::Matrix;
using std::begin;
using std::end;
using std::cout;

int main() {
	int test_data[] = { 1, 2, -12, 4, 5, 6 };

	Matrix<int> test_M_1(2, 3);
	test_M_1.importData({
		5, 4, 3,
		2, 1, 0,
		});
	cout << test_M_1;

	cout << test_M_1.row(0);

	cout << test_M_1.col(2);

	test_M_1.reshape(3, 2);
	cout << test_M_1;

	cout << test_M_1.reshape(1, 6);

	return 0;
}