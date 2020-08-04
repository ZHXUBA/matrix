#ifndef MATRIX_TYPEDEFINE_H_
#define MATRIX_TYPEDEFINE_H_

#include "base.h"
#include "decorator.h"

namespace matrix {


	typedef ::int64_t index_t;

	typedef struct MatrixShape : public ::_matrix::_2D_Shape {

	} shape_t;

	template<typename _Iter>
	using VitualMatrix = ::_matrix::_2D_Collector_Iterator_Decorator<_Iter>;

}  // the end of namespace matrix

namespace _matrix {

	using ::matrix::index_t;
	using ::matrix::shape_t;
	using ::matrix::VitualMatrix;
}

#endif // !MATRIX_TYPEDEFINE_H_

