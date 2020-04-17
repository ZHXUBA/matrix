#ifndef PROCESS_MATRIX_H
#define PROCESS_MATRIX_H

#include <cassert>
#include "assistant__inverse_matrix.h"
#include "matrix.h"
#include "process_matrix_base_algorithm.h"


//3. 简单计算 mat + mat mat - mat mat * mat  mat * number number * mat  transpose
//4. 复杂计算 det行列式 逆矩阵 .....  pow(mat, int)
//5. 高级计算 梯度 求导类的 .....
// 待添加Strassen算法计算矩阵乘法

namespace matrix {

	template<class T>
	inline Matrix<T> operator+ (const Matrix<T>& mat1, const Matrix<T>& mat2) {
		// 要求T支持 '+' 运算符
		assert(mat1.sameShape(mat2));  // 最后要更改为异常处理
		Matrix<T> res(mat1.shape().r, mat1.shape().c);
		typename Matrix<T>::iter be = res.begin(), en = res.end();
		typename Matrix<T>::iter be1 = mat1.begin(), en1 = mat1.end();
		typename Matrix<T>::iter be2 = mat2.begin(), en2 = mat2.end();
		// 已经强制res mat1 mat2 同形
		while (be != en) {
			*be = *be1 + *be2;
			++be; ++be1; ++be2;
		}
		return res;
	}

	template<class T>
	inline Matrix<T> operator- (const Matrix<T>& mat1, const Matrix<T>& mat2) {
		// 要求T支持 '-' 运算符
		assert(mat1.sameShape(mat2));  // 最后要更改为异常处理
		Matrix<T> res(mat1.shape().r, mat1.shape().c);
		typename Matrix<T>::iter be = res.begin(), en = res.end();
		typename Matrix<T>::iter be1 = mat1.begin(), en1 = mat1.end();
		typename Matrix<T>::iter be2 = mat2.begin(), en2 = mat2.end();
		// 已经强制res mat1 mat2 同形
		while (be != en) {
			*be = *be1 - *be2;
			++be; ++be1; ++be2;
		}
		return res;
	}

	template<class T>
	inline Matrix<T> operator* (const Matrix<T>& mat1, const Matrix<T>& mat2) {
		// 要求T支持 '*' 运算符
		assert(mat1.shape().c == mat2.shape().r);	// 最后要更改为异常处理
		Matrix<T> res(mat1.shape().r, mat2.shape().c);

		const index_t r = mat1.shape().r;
		const index_t c = mat2.shape().c;
		const index_t r_c = mat1.shape().c; // 以强制 mat1.

		// O(n^3) // 非渐进意义上还有提升空间,使用迭代器改写,但是略有麻烦,且意义不大,再说
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

	template<class T, class NUM_T>
	inline Matrix<T> operator* (const Matrix<T>& mat, const NUM_T num) {
		Matrix<T> res(mat.shape().r, mat.shape().c);

		typename Matrix<T>::iter be = mat.begin(), en = mat.end();
		typename Matrix<T>::iter rebe = res.begin(), reen = res.end(); // re(s)en(d)/be(gin)

		while (rebe != reen) {
			*rebe = (*be) * num;
			++rebe; ++be;
		}

		return res;
	}

	template<class T, class NUM_T>
	inline Matrix<T> operator* (const NUM_T num, const Matrix<T>& mat) {
		Matrix<T> res(mat.shape().r, mat.shape().c);

		typename Matrix<T>::iter be = mat.begin(), en = mat.end();
		typename Matrix<T>::iter rebe = res.begin(), reen = res.end(); // re(s)en(d)/be(gin)

		while (rebe != reen) {
			*rebe = (*be) * num;
			++rebe; ++be;
		}

		return res;
	}

	template<class T>
	inline Matrix<T> transpose(const Matrix<T>& mat) {
		Matrix<T> res(mat.shape().c, mat.shape().r);
		for (int i = 0; i < res.shape().r; ++i) {
			for (int j = 0; j < res.shape().c; ++j) {
				res.at(i, j) = mat.at(j, i);
			}
		}
		return res;
	}

	template<class T>
	inline Matrix<T> __test_inverse(const Matrix<T>& mat) {
		// 仅是为了不浪费以前编写的一套高斯消元法求逆矩阵,效率较低,有很多可以优化的地方,
		// 求逆矩阵主要使用LU分解法(便于并行计算),暂时不考虑优化此方法
		// 以前那一套的矩阵数据结构是vector<vector<double>>,
		// 为了适应此套matrix的数据机构必须进行大量的复制操作(效率极低,仅做测试使用)
		// 并且此前编写的那套代码风格与此不同,同样暂不调整
		// 精度很差,代码质量很差,就当是纪念初学C++吧 !!
#include "assistant__inverse_matrix.h"
		
		const int r = mat.shape().r;
		const int c = mat.shape().c;
		Matrix<T> res(r, c);
		_matrix::m_type mat_uv(r, _matrix::row_type(c));
		
		typename Matrix<T>::iter be = mat.begin(), en = mat.end();
		typename Matrix<T>::iter rebe = res.begin(), reen = res.end();

		
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c && be != en; ++j, ++be)
				mat_uv.at(i).at(j) = static_cast<double>(*be);

		_matrix::m_type res_uv = _matrix::toInverseMatrix(mat_uv);
		
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c && rebe != reen; ++j, ++rebe)
				*rebe = static_cast<T>(res_uv.at(i).at(j));
		
		return res;
	}


	template<class T>
	inline Matrix<T> inserve(const Matrix<T>& mat) {
		assert(mat.shape().r == mat.shape().c);  // 最终要改为异常处理
		
		Matrix<T> L(Matrix<T>::ZerosLike(mat));
		Matrix<T> U(Matrix<T>::ZerosLike(mat));
		Matrix<T> invL(Matrix<T>::ZerosLike(mat));
		Matrix<T> invU(Matrix<T>::ZerosLike(mat));

		_matrix::toLU(mat, L, U);

		_matrix::inverseLTM(L, invL);
		_matrix::inverseUTM(U, invU);

		return invU * invL;

	}
}  // the end of namespace matrix

#endif // !PROCESS_MATRIX_H
