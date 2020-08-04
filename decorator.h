#ifndef DECORATOR_H
#define DECORATOR_H

#include <iterator>
#include <iostream>

#include "typeDefine.h"
#include "base.h"


namespace _matrix {


	template<typename _Iter>
	struct _2D_Collector_Iterator_Decorator;

	template<typename _Iter>
	std::ostream& operator<< (
		std::ostream& os,
		_2D_Collector_Iterator_Decorator<_Iter>& cid
		);

	// iterator×°ÊÎÆ÷
	template<typename _Iter>
	struct _2D_Collector_Iterator_Decorator {
		/*
			using iterator_category 
			using value_type        
			using difference_type   
			using pointer           
			using reference         
		*/
	public:
		typedef size_t index_t;
		typedef _Iter Decorated_Iterator_t;
		typedef Decorated_Iterator_t* Decorated_Iterator_Pointer_t;
		typedef typename std::iterator_traits<Decorated_Iterator_t>::value_type Data_t;
		typedef typename std::iterator_traits<Decorated_Iterator_t>::difference_type Diff_t;
		typedef typename std::iterator_traits<Decorated_Iterator_t>::reference Refer_t;
		typedef _2D_Shape Shape_t;

		_2D_Collector_Iterator_Decorator(_Iter iter, const Shape_t& shape) : _iter(new _Iter(iter)) {
			//std::cout << "cdtor1\n";
			//_iter = new _Iter(*iter, shape.c);
			//_iter = &iter;
			_shape.r = shape.r;
			_shape.c = shape.c;
			
		}

		_2D_Collector_Iterator_Decorator(_Iter iter, index_t r, index_t c) : _iter(new _Iter(iter)) {
			//std::cout << "cdtor2\n";
			//_iter = &iter;
			_shape.r = r;
			_shape.c = c;
		}

		_2D_Collector_Iterator_Decorator(const _2D_Collector_Iterator_Decorator& ml) = default;

		_2D_Collector_Iterator_Decorator(_2D_Collector_Iterator_Decorator&& ml) = default;

		~_2D_Collector_Iterator_Decorator() { delete _iter; }

		// Ö»¿¼ÂÇrandomµü´úÆ÷
		Refer_t operator() (Diff_t r, Diff_t c) {
			Diff_t trueDiff = static_cast<Diff_t>(r) * _shape.c + static_cast<Diff_t>(c);
			//std::cout << trueDiff << "&&&^^^%%";
			//std::cout << trueDiff - _diff << "&&&^^^%%";

			( *_iter ) += trueDiff - _diff;
			_diff = trueDiff;
			return **_iter;  // return the data's reference
		}
		
		Refer_t at (index_t r, index_t c) {
			return operator() (r, c);
		}
		template<typename _Iter>
		friend std::ostream& operator<< (
			std::ostream& os,
			_2D_Collector_Iterator_Decorator<_Iter>& cid
			);
	private:
		Decorated_Iterator_Pointer_t _iter = nullptr;
		Shape_t _shape;
		Diff_t _diff = 0;
	public:
		Decorated_Iterator_t iter() const { return *_iter; }
		const Shape_t& shape() const { return _shape; }

	};

	template<typename _Iter>
	inline _2D_Collector_Iterator_Decorator<_Iter> makeMat(_Iter& begin, const typename _2D_Collector_Iterator_Decorator<_Iter>::Shape_t& shape) {
		
		return _2D_Collector_Iterator_Decorator<_Iter>(begin, shape);
	}

	template<typename _Iter>
	inline _2D_Collector_Iterator_Decorator<_Iter> makeMat(_Iter& begin, int r, int c) {
		
		return _2D_Collector_Iterator_Decorator<_Iter>(begin, r, c);
	}

	template<typename _Iter>
	inline _2D_Collector_Iterator_Decorator<_Iter> makeMat(_Iter&& begin, const typename _2D_Collector_Iterator_Decorator<_Iter>::Shape_t& shape) {

		return _2D_Collector_Iterator_Decorator<_Iter>(begin, shape);
	}

	template<typename _Iter>
	inline _2D_Collector_Iterator_Decorator<_Iter> makeMat(_Iter&& begin, int r, int c) {

		return _2D_Collector_Iterator_Decorator<_Iter>(begin, r, c);
	}


	template<typename _Iter>
	std::ostream& operator<< (
		std::ostream& os,
		_2D_Collector_Iterator_Decorator<_Iter>& cid
		) {
		os << "VirtualMatrix(\n";
		for (int i = 0; i < cid._shape.r; ++i) {
			
			for (int j = 0; j < cid._shape.c; ++j) {
				os << cid(i, j) << ",\t";
			}
			os << "\n\n";
		}
		return os << ")";
	}

}  // the end of namespace _matrix
#endif // !DECORATOR_H

