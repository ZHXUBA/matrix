#include "matrix.h"


#ifndef PROCESS_MATRIX_BASE_ALGORITHM_H

#define PROCESS_MATRIX_BASE_ALGORITHM_H

namespace _matrix {

	template<class T>
	using M = matrix::Matrix<T>;
	
	typedef matrix::index_t index_t;

	template<class T>
	void toLU(const M<T>& src, M<T>& toL, M<T>& toU) {
		const index_t size = src.shape().r;
		// L的对角
		for (index_t i = 0; i < size; ++i)
			toL.at(i, i) = static_cast< typename M<T>::value_t >(1);
		// L的第一行
		for (index_t j = 0; j < size; ++j)
			toU.at(0, j) = src.at(0, j);
		// U的第一列
		typename M<T>::value_t tmp = toU.at(0, 0);
		for (index_t i = 0; i < size; ++i)
			toL.at(i, 0) = src.at(i, 0) / tmp;

		for (index_t r = 0; r < size; ++r) {
			for (index_t j = r; j < size; ++j) {
				typename M<T>::value_t sum = static_cast< typename M<T>::value_t >(0);
				for (index_t k = 0; k < r; ++k) {
					sum += toL.at(r, k) * toU.at(k, j);
				}
				toU.at(r, j) = src.at(r, j) - sum;
			}
			for (index_t i = r + 1; i < size; ++i) {
				typename M<T>::value_t sum = static_cast< typename M<T>::value_t >(0);
				for (index_t k = 0; k < r; ++k) {
					sum += toL.at(i, k) * toU.at(k, r);
				}
				toL.at(i, r) = (src.at(i, r) - sum) / toU.at(r, r);
			}
		}
	}

	template<class T>
	void inverseLTM(const M<T>& src, M<T>& to) {
		const index_t size = src.shape().r;
		
		for (index_t i = 0; i < size; ++i)
			to.at(i, i) = static_cast< typename M<T>::value_t >(1) / src.at(i, i);

		for (index_t i = 0; i < size; ++i) {
			for (index_t j = i + 1; j < size; ++j) {
				typename M<T>::value_t sum = static_cast<typename M<T>::value_t>(0);
				for (index_t k = i; k <= j; ++k)
					sum += src.at(j, k) * to.at(k, i);
				to.at(j, i) = -1 * to.at(i, i) * sum;
			}
		}
	}

	template<class T>
	void inverseUTM(const M<T>& src, M<T>& to) {
		const index_t size = src.shape().r;

		for (index_t j = 0; j < size; ++j)
			to.at(j, j) = static_cast<typename M<T>::value_t>(1) / src.at(j, j);
		
		for (int j = size - 1; j >= 0; --j) {
			for (index_t i = size - 1; i > j; --i) {
				typename M<T>::value_t sum = static_cast<typename M<T>::value_t>(0);
				for (int k = j; k <= i; ++k)
					sum += src.at(j, k) * to.at(k, i);
				to.at(j, i) = -1 * sum / src.at(j, j);
			}
			//if (j == 0) break;
		}
	}


} // the end of namespace _matrix


#endif

