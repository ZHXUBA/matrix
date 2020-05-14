#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

#include "matrix.h"
#include "process_matrix.h"
#include "process_matrix_base_algorithm.h" 
#include "typeDefine.h"

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
using std::vector;

int main() {

	Matrix<int> m1(4, 4);
	
	m1({
		1, 0, 1, 0,
		0, 0, 1, 1,
		1, 0, 1, 0, 
		1, 0, 1, 0,
	});

	m1 = Matrix<int>::Units(7);

	cout << m1 << "\n";

	vector<int> v = {
		1, 0, 1, 0,
		0, 0, 1, 1,
		1, 0, 1, 0,
		1, 0, 1, 0,
	};

	auto p = v.begin();

	auto matl = _matrix::makeMat(p, 4, 4);
	
	cout << matl;

	auto matl2 = _matrix::makeMat(v.begin(), 2, 8);
	
	cout << matl2;

	Matrix<int> m3 = {
		{1, 2, 3},
		{3, 2, 1},
		{6, 4, 0},
	};

	cout << m3;

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