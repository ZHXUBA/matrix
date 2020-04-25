#include <iostream>
#include <iterator>
#include <algorithm>
#include "matrix.h"
#include "process_matrix.h"
#include "process_matrix_base_algorithm.h" 

#include "decorator.h"

using matrix::MatrixData;
using matrix::Matrix;
using matrix::transpose;
using matrix::__test_inverse;
using _matrix::toLU;
using _matrix::_2D_Collector_Iterator_Decorator;
using std::begin;
using std::end;
using std::cout;

int main() {

	Matrix<double> m1(3, 3);

	m1.importData({
		1, 1, 4,
		0, 1, 2,
		2, -1, 0,
		});


	Matrix<double>::iter iter = m1.begin();


	
	_2D_Collector_Iterator_Decorator<Matrix<double>::iter> iter_(*&m1.begin(), m1.shape());


	cout << iter_(0, 0) << " ";
	cout << iter_(0, 1) << " ";
	cout << iter_(2, 1) << " ";

	int a[6] = {1, 2, 3, 4, 5, 6};
	int* b = &a[0];
	_2D_Collector_Iterator_Decorator<int*> iter_2(b, 2, 3);

	cout << iter_2(1, 0);
	//Matrix<double> l(Matrix<double>::Zeros(3, 3));
	//Matrix<double> u(Matrix<double>::Zeros(3, 3));

	//Matrix<double> invL(Matrix<double>::Zeros(3, 3));
	//Matrix<double> invU(Matrix<double>::Zeros(3, 3));

	//_matrix::toLU(m1, l, u);
	//_matrix::inverseLTM(l, invL);
	//_matrix::inverseUTM(u, invU);

	////invU.at(0, 3) = -4.5;

	///*cout << l << "\n" << u;

	//cout << invL << "\n" << invU;*/

	//cout << "\n" << invU * invL;


	//cout << "\n" << invU * invL * m1;
	//
	//cout << "***********************************\n";
	//
	//cout << __test_inverse(m1);

	//cout << __test_inverse(m1) * m1;

	//cout << "************************************\n";

	//cout << matrix::inserve(m1);


	return 0;
}