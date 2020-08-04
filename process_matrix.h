#ifndef PROCESS_MATRIX_H
#define PROCESS_MATRIX_H

#include <cassert>
#include "assistant__inverse_matrix.h"
#include "matrix.h"
#include "process_matrix_base_algorithm.h"


//3. �򵥼��� mat + mat mat - mat mat * mat  mat * number number * mat  transpose
//4. ���Ӽ��� det����ʽ ����� .....  pow(mat, int)
//5. �߼����� �ݶ� ����� .....
// �����Strassen�㷨�������˷�

namespace matrix {

	template<typename T>
	Matrix<T> operator+ (const Matrix<T>& mat1, const Matrix<T>& mat2) {
		// Ҫ��T֧�� '+' �����
		assert(mat1.sameShape(mat2));  // ���Ҫ����Ϊ�쳣����
		Matrix<T> res(mat1.shape().r, mat1.shape().c);
		typename Matrix<T>::iter be = res.begin(), en = res.end();
		typename Matrix<T>::iter be1 = mat1.begin(), en1 = mat1.end();
		typename Matrix<T>::iter be2 = mat2.begin(), en2 = mat2.end();
		// �Ѿ�ǿ��res mat1 mat2 ͬ��
		while (be != en) {
			*be = *be1 + *be2;
			++be; ++be1; ++be2;
		}
		return res;
	}

	template<typename T>
	Matrix<T> operator- (const Matrix<T>& mat1, const Matrix<T>& mat2) {
		// Ҫ��T֧�� '-' �����
		assert(mat1.sameShape(mat2));  // ���Ҫ����Ϊ�쳣����
		Matrix<T> res(mat1.shape().r, mat1.shape().c);
		typename Matrix<T>::iter be = res.begin(), en = res.end();
		typename Matrix<T>::iter be1 = mat1.begin(), en1 = mat1.end();
		typename Matrix<T>::iter be2 = mat2.begin(), en2 = mat2.end();
		// �Ѿ�ǿ��res mat1 mat2 ͬ��
		while (be != en) {
			*be = *be1 - *be2;
			++be; ++be1; ++be2;
		}
		return res;
	}

	template<typename T>
	Matrix<T> operator* (const Matrix<T>& mat1, const Matrix<T>& mat2) {
		// Ҫ��T֧�� '*' �����
		assert(mat1.shape().c == mat2.shape().r);	// ���Ҫ����Ϊ�쳣����
		Matrix<T> res(mat1.shape().r, mat2.shape().c);

		const index_t r = mat1.shape().r;
		const index_t c = mat2.shape().c;
		const index_t r_c = mat1.shape().c; // ��ǿ�� mat1.

		// O(n^3) // �ǽ��������ϻ��������ռ�,ʹ�õ�������д,���������鷳,�����岻��,��˵
		for (index_t i = 0; i < r; ++i) { // i_th row
			for (index_t j = 0; j < c; ++j) { // j_th column
				T& temp = res.at(i, j) = static_cast<T>(0);  // or iterator
				for (index_t idx = 0; idx < r_c; ++idx) {
					temp += mat1.at(i, idx) * mat2.at(idx, j);  // or iterator
				}
			}
		}
		return res;
	}

	template<typename T, typename NUM_T>
	Matrix<T> operator* (const Matrix<T>& mat, const NUM_T num) {
		Matrix<T> res(mat.shape().r, mat.shape().c);

		typename Matrix<T>::iter be = mat.begin(), en = mat.end();
		typename Matrix<T>::iter rebe = res.begin(), reen = res.end(); // re(s)en(d)/be(gin)

		while (rebe != reen) {
			*rebe = (*be) * num;
			++rebe; ++be;
		}

		return res;
	}

	template<typename T, typename NUM_T>
	Matrix<T> operator* (const NUM_T num, const Matrix<T>& mat) {
		Matrix<T> res(mat.shape().r, mat.shape().c);

		typename Matrix<T>::iter be = mat.begin(), en = mat.end();
		typename Matrix<T>::iter rebe = res.begin(), reen = res.end(); // re(s)en(d)/be(gin)

		while (rebe != reen) {
			*rebe = (*be) * num;
			++rebe; ++be;
		}

		return res;
	}

	template<typename T>
	Matrix<T> transpose(const Matrix<T>& mat) {
		Matrix<T> res(mat.shape().c, mat.shape().r);
		for (int i = 0; i < res.shape().r; ++i) {
			for (int j = 0; j < res.shape().c; ++j) {
				res.at(i, j) = mat.at(j, i);
			}
		}
		return res;
	}

	template<typename T>
	Matrix<T> __test_inverse(const Matrix<T>& mat) {
		// ����Ϊ�˲��˷���ǰ��д��һ�׸�˹��Ԫ���������,Ч�ʽϵ�,�кܶ�����Ż��ĵط�,
		// ���������Ҫʹ��LU�ֽⷨ(���ڲ��м���),��ʱ�������Ż��˷���
		// ��ǰ��һ�׵ľ������ݽṹ��vector<vector<double>>,
		// Ϊ����Ӧ����matrix�����ݻ���������д����ĸ��Ʋ���(Ч�ʼ���,��������ʹ��)
		// ���Ҵ�ǰ��д�����״�������˲�ͬ,ͬ���ݲ�����
		// ���Ⱥܲ�,���������ܲ�,�͵��Ǽ����ѧC++�� !!
#include "assistant__inverse_matrix.h"
		
		const int r = mat.shape().r;
		const int c = mat.shape().c;
		Matrix<T> res(r, c);
		typename ::_matrix::m_type mat_uv(r, ::_matrix::row_type(c));
		
		typename Matrix<T>::iter be = mat.begin(), en = mat.end();
		typename Matrix<T>::iter rebe = res.begin(), reen = res.end();

		
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c && be != en; ++j, ++be)
				mat_uv.at(i).at(j) = static_cast<double>(*be);

		typename ::_matrix::m_type res_uv = ::_matrix::toInverseMatrix(mat_uv);
		
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c && rebe != reen; ++j, ++rebe)
				*rebe = static_cast<T>(res_uv.at(i).at(j));
		
		return res;
	}

	template<typename T>
	Matrix<T> inserve(const Matrix<T>& mat) {
		assert(mat.shape().r == mat.shape().c);  // ����Ҫ��Ϊ�쳣����
		
		Matrix<T> L(Matrix<T>::ZerosLike(mat));
		Matrix<T> U(Matrix<T>::ZerosLike(mat));
		Matrix<T> invL(Matrix<T>::ZerosLike(mat));
		Matrix<T> invU(Matrix<T>::ZerosLike(mat));

		::_matrix::toLU(mat, L, U);

		::_matrix::inverseLTM(L, invL);
		::_matrix::inverseUTM(U, invU);

		return invU * invL;

	}
}  // the end of namespace matrix

#endif // !PROCESS_MATRIX_H
