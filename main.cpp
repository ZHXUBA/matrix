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
	//test_M_1.importData(begin(test_data), end(test_data));
	cout << test_M_1;

	cout << test_M_1.row(0);

	cout << test_M_1.col(2);

	test_M_1.reshape(3, 2);
	cout << test_M_1;

	cout << test_M_1.reshape(1, 6);

	test_M_1.reshape(2, 3);

	cout << Matrix<int>::DiagonalLike(test_M_1, begin(test_data), end(test_data));

	cout << Matrix<int>::UnitsLike(test_M_1);

	cout << Matrix<int>::ZerosLike(test_M_1);


	return 0;
}