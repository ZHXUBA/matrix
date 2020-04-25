#ifndef DECORATOR_H
#define DECORATOR_H

#include <iterator>
#include <iostream>
#include "helper.h"


namespace _matrix {

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
		typedef size_t index_t;
		typedef _Iter Decorated_Iterator_t;
		typedef Decorated_Iterator_t* Decorated_Iterator_Pointer_t;
		typedef typename std::iterator_traits<Decorated_Iterator_t>::value_type Data_t;
		typedef typename std::iterator_traits<Decorated_Iterator_t>::difference_type Diff_t;
		typedef typename std::iterator_traits<Decorated_Iterator_t>::reference Refer_t;
		typedef _2D_Shape Shape_t;

		_2D_Collector_Iterator_Decorator(_Iter& iter, const Shape_t& shape) : _iter(&iter) {
			//std::cout << "cdtor1\n";
			//_iter = new _Iter(*iter, shape.c);
			//_iter = &iter;
			_shape.r = shape.r;
			_shape.c = shape.c;
			
		}

		_2D_Collector_Iterator_Decorator(_Iter& iter, index_t r, index_t c) : _iter(&iter) {
			//std::cout << "cdtor2\n";
			//_iter = &iter;
			_shape.r = r;
			_shape.c = c;
		}

		//~_2D_Collector_Iterator_Decorator() { delete _iter; }

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
		
	private:
		Decorated_Iterator_Pointer_t _iter = nullptr;
		Shape_t _shape;
		Diff_t _diff = 0;

	};



}  // the end of namespace _matrix
#endif // !DECORATOR_H

