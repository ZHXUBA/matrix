#ifndef MATRIX_MATRIXITERATOR_H_
#define MATRIX_MATRIXITERATOR_H_

#include"typeDefine.h"

namespace matrix {

	template<class T>
	class MDIterator {
	public:
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef T*									pointer;
		typedef T&									reference;
	private:
		T* ptr = nullptr;
		index_t _c = 0;
	public:
		MDIterator() { }
		MDIterator(const MDIterator& other) {
			ptr = other.ptr;
			_c = other._c;
		}
		MDIterator(T& e, index_t c) : ptr(&e), _c(c) { }
		// some operator(s) overload
		T& operator* () const { return *ptr; }
		T* operator-> () const { return &(operator*()); }
		MDIterator& operator= (const MDIterator& other) {
			if (this == &other) return *this;
			ptr = other.ptr;
			return *this;
		}
		MDIterator& operator++ () { ++ptr; return *this; }
		MDIterator& operator-- () { ++ptr; return *this; }
		MDIterator operator++ (int) {
			value_type* p = ptr; ++ptr; 
			return MDIterator(*p, _c);
		}
		MDIterator operator-- (int) {
			value_type* p = ptr; ++ptr;
			return MDIterator(*p, _c);
		}
		MDIterator& operator+= (difference_type diff) { ptr += diff; return *this; }
		MDIterator& operator-= (difference_type diff) { ptr -= diff; return *this; }
		MDIterator operator+ (difference_type diff) const { return MDIterator(*(ptr + diff), _c); }
		MDIterator operator- (difference_type diff) const { return MDIterator(*(ptr - diff), _c); }
		difference_type operator- (const MDIterator& other) const { return ptr - other.ptr; }
		bool operator< (const MDIterator& other) { return ptr < other.ptr; }
		bool operator== (const MDIterator& other) const { return ptr == other.ptr; }
		bool operator!= (const MDIterator& other) const { return ptr != other.ptr; }
		// the special function of MDIterator
		MDIterator nextRow() { return (*this += _c); }
	};


}  // the end of namespace matrix


#endif // MATRIX_MATRIXITERATOR_H_

