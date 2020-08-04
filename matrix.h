#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<initializer_list>
#include<iterator>
#include"tools.h"
#include"matrixIterator.h"
#include"typeDefine.h"

/*
1. MatrixData 's Iterator    
2. 异常处理(参数检测, 范围检测)  
3. 简单计算 mat + mat mat - mat mat * mat mat * number number * mat pow(mat, int) transpose
4. 复杂计算 det行列式 逆矩阵 
5. 高级计算 梯度 求导类的
6. 随机数矩阵*
*/


namespace matrix {

    const index_t __unorflag__ = -1;  // 特殊标志
    
    template<class T>
    class MatrixData {
    public:
        // 作用 : 作为矩阵Matrix的物理抽象

        typedef T value_t;

        typedef MDIterator<value_t> iter;

        // 属性 :
        value_t* data;
        shape_t shape;
        // conductors and dtors
        MatrixData(index_t r, index_t c) {
            shape.r = r;
            shape.c = c;
            data = new value_t[r * c];
        }

        MatrixData(const shape_t& sh) : shape(sh){
            data = new value_t[sh.r, sh.c];
        }

        MatrixData(const MatrixData& other) {
            shape.r = other.shape.r;
            shape.c = other.shape.c;
            data = new value_t[shape.r * shape.c];
            // copy data
            for (index_t i = 0; i < shape.r; ++i) {
                for (index_t j = 0; j < shape.c; j++) {
                    *(data + shape.c * i + j) = *(other.data + shape.c * i + j);
                }
            }

        }

        ~MatrixData() { delete[] data; }
        // begin, end return MDIter
        MDIterator<value_t> begin() {
            return MDIterator<value_t>(*data, shape.c);
        }
        MDIterator<value_t> end() {
            return MDIterator<value_t>(*(data + shape.c * shape.r), shape.c);
        }
        const MDIterator<value_t> begin() const {
            return MDIterator<value_t>(*data, shape.c);
        }
        const MDIterator<value_t> end() const {
            return MDIterator<value_t>(*(data + shape.c * shape.r), shape.c);
        }
        // import data
        void importData(value_t* begin, value_t* end) { // [ begin, end )
            value_t* dataptr = data;
            index_t flagLen = shape.r * shape.c;
            while (begin != end && (flagLen--)) {
                *dataptr = *begin;
                ++dataptr;
                ++begin;
            }
        }
        void importData(const std::initializer_list<value_t> & il) { // [ begin, end )
            value_t* dataptr = data;
            auto begin = il.begin();
            auto end = il.end();
            index_t flagLen = shape.r * shape.c;
            while (begin != end && (flagLen--)) {
                *dataptr = *begin;
                ++dataptr;
                ++begin;
            }
        }
        // get value
        const value_t& operator() (index_t ri, index_t ci) const {
            return *(data + shape.c * ri + ci);
        }
        value_t& operator() (index_t ri, index_t ci) {
            return *(data + shape.c * ri + ci);
        }
        const value_t& operator() (index_t idx) const { return *(data + idx); }
        value_t& operator() (index_t idx) { return *(data + idx); }
        // some other opertors overload
        MatrixData& operator= (const MatrixData& other) {
            if (this == &other) return *this;
            if (!this->sameShape(other)) {
                // resize
                shape.r = other.shape.r;
                shape.c = other.shape.c;
                // delete old data(memory)
                delete [] data;
                // create new memory
                data = new value_t[shape.r * shape.c];
            }
            // copy data
            for (index_t i = 0; i < shape.r; ++i) {
                for (index_t j = 0; j < shape.c; j++) {
                    *(data + shape.c * i + j) = *(other.data + shape.c * i + j);
                }
            }
            return *this;
        }
        bool operator== (const MatrixData& other) const {
            if (this == &other) return true;
            if (shape.r != other.shape.r || shape.c != other.shape.c)
                return false;
            for (index_t i = 0; i < shape.r; ++i) {
                for (index_t j = 0; j < shape.c; ++j) {
                    if (*(data + shape.c * i + j) != *(other.data + shape.c * i + j))
                        return false;
                }
            }
            return true;
        }
        // shape
        bool sameShape(const MatrixData& other) const {
            return (shape.r == other.shape.r) && (shape.c == other.shape.c);
        }

    };

    template<class _Tp, class DATAS_T=MatrixData<_Tp>>
    class Matrix {
    public:
        typedef DATAS_T datas_t;
        typedef _Tp value_t;
        typedef MDIterator<value_t> iter;

    private:
        datas_t* _data = nullptr;

    public:
        /*Matrix() {
            _data.shape.r = __unorflag__;
            _data.shape.c = __unorflag__;
        }*/
        Matrix(index_t r, index_t c) : _data(new datas_t(r, c)) { }
        Matrix(const shape_t& shape) : _data(new datas_t(shape)) { }
        explicit Matrix(datas_t dat) : _data(new datas_t(dat)) { }
        Matrix(const Matrix& other) : _data(new datas_t(*other._data)) { }
        Matrix(Matrix&& other) noexcept : _data(other._data) {
            other._data = nullptr;
        }
        Matrix(std::initializer_list<std::initializer_list<value_t>> il) {
            index_t r = il.size();
            index_t c = 0;

            for (auto& ill : il) {
                c < ill.size() && (c = ill.size());
            }
            _data = new datas_t(r, c);
            iter begin = this->begin();
            for (auto& ill : il) {
                for (auto& e : ill) {
                    *begin = e; ++begin;
                }
            }
        }

        ~Matrix() { delete _data; }
        //being end return MDIterator
        iter begin() { return _data->begin(); }
        iter end() { return _data->end(); }

        const iter begin() const { return _data->begin(); }
        const iter end() const { return _data->end(); }

        // get properpy(-ies)
        const shape_t& shape() const {
            return _data->shape;
        }

        const datas_t& data() const { return *_data; }

        datas_t& data() { return *_data; }

        // get value
        value_t& at(index_t ri, index_t ci) {
            return (*_data)(ri, ci);
        }

        const value_t& at(index_t ri, index_t ci) const {
            return (*_data)(ri, ci);
        }

        // get row/col as a Matrix
        Matrix<value_t> row(index_t ri) { // error------
            const index_t c = shape().c;
            Matrix<value_t> ro(1, c);
            //for (index_t i = 0; i < c; ++i) {
            //	(*ro._data)(0, i) = (*_data)(ri, i);				 // 待改为迭代器 -ed
            //}
            iter begin = this->begin(), end = this->end();
            iter robegin = ro.begin(), roend = ro.end();
            while (ri--) { begin.nextRow(); }
            for (; robegin != roend; ++begin, ++robegin) {
                *robegin = *begin;
            }
            return ro;
        }

        Matrix<value_t> col(index_t ci) {
            const index_t r = shape().r;
            Matrix<value_t> co(r, 1);
            //for (index_t i = 0; i < r; ++i) {
            //	(*co._data)(i, 0) = (*_data)(i, ci);				 // 待改为迭代器  -ed
            //}
            iter begin = this->begin(), end = this->end();
            iter cobegin = co.begin(), coend = co.end();
            begin += ci;
            for (; cobegin != coend; begin.nextRow(), ++cobegin) {
                *cobegin = *begin;
            }
            return co;
        }

        //reshape
        Matrix<value_t>& reshape(index_t r, index_t c) { // 待添加异常处理(前后元素个数不一样,不能整除,r,c都为-1)
            if (r == __unorflag__) r = (_data->shape.r) * (_data->shape.c) / c;
            else if (c == __unorflag__)  c = (_data->shape.r) * (_data->shape.c) / r;
            _data->shape.r = r;
            _data->shape.c = c;
            return *this;
        }

        // import data
        void importData(value_t* begin, value_t* end) { // [ begin, end )
            iter _begin = this->begin(), _end = this->end();
            while (begin != end && _begin !=_end) {
                *_begin = *begin;				 // 待改为迭代器  -ed
                ++_begin;
                ++begin;
            }
        }

        void importData(const std::initializer_list<value_t> & il) {
            auto begin = il.begin();
            auto end = il.end();
            iter _begin = this->begin(), _end = this->end();
            while (begin != end && (_begin != _end)) {
                *_begin = *begin;				 // 待改为迭代器  -ed
                ++_begin;
                ++begin;
            }
        }
        
        // operator overload
        Matrix<value_t>& operator= (const Matrix<value_t> & other) {
            if (this == &other) return *this;
            if (_data) delete _data;
            _data = new datas_t(*other._data);
            return *this;
        }

        Matrix<value_t>& operator= (Matrix<value_t>&& other) noexcept {

            if (this == &other) return *this;
            if (_data) delete _data;
            _data = other._data;
            other._data = nullptr;
            return *this;
        }

        bool operator== (const Matrix<value_t>& other) const {
            return *(_data) == *(other._data);
        }
        
        template<typename _NumType>
        Matrix<value_t> operator+= (const _NumType num) {
            // 广播机制
            iter begin = this->begin();
            iter end = this->end();
            for (; begin != end; ++begin) {
                *begin += num;
            }
            return *this;
        }

        template<typename _NumType>
        Matrix<value_t> operator-= (const _NumType num) {
            // 广播机制
            iter begin = begin();
            iter end = end();
            for (; begin != end; ++begin) {
                *begin -= num;
            }
            return *this;
        }

        Matrix<value_t>& operator() (std::initializer_list<value_t> il) {
            this->importData(il);
            return *this;
        }
        // get some special matrix(-s)
        static Matrix<value_t> Zeros(index_t r, index_t c) {
            Matrix<value_t> zeros(r, c);
            //for (index_t i = 0; i < r; ++i) {
            //	for (index_t j = 0; j < c; ++j) {				 // 待改为迭代器  -ed
            //		zeros.at(i, j) = static_cast<value_t>(0); // 待添加异常处理(cast error)				 // 待改为迭代器
            //	}
            //}
            iter _begin = zeros.begin(), _end = zeros.end();
            for (; _begin != _end; ++_begin) {
                *_begin = static_cast<value_t>(0);	// 待添加异常处理(cast error)	
            }
            return zeros;
        }

        template<class OTHER_T>
        static Matrix<value_t> ZerosLike(const Matrix<OTHER_T>& m) {
            return Zeros(m.shape().r, m.shape().c);
        }

        static Matrix<value_t> Units(index_t r) {
            Matrix<value_t> units(Zeros(r, r));
            //for (int i = 0; i < r; ++i) {
            //	units.at(i, i) = static_cast<value_t>(1);				 // 待改为迭代器  -ed
            //}
            iter be = units.begin(), en = units.end();
            for (; be != en; ) {
                *be = static_cast<value_t>(1);
                ++be;
                if (be != en) be.nextRow();
            }
            return units;
        }

        template<class OTHER_T>
        static Matrix<value_t> UnitsLike(const Matrix<OTHER_T>& m) { // 待添加异常处理(m非方阵)
            return Units(m.shape().r);
        }

        static Matrix<value_t> Diagonal(index_t r, value_t* begin, value_t* end) {
            Matrix<value_t> diag(Zeros(r, r));
            //for (int i = 0; i < r && begin != end; ++i) {
            //	diag.at(i, i) = *begin;				 // 待改为迭代器  -ed
            //	++begin;
            //}
            iter be = diag.begin(), en = diag.end();
            for (; be != en && begin != end; ++begin) {
                *be = *begin;
                ++be;
                if (be != en) be.nextRow();
            }
            return diag;
        }

        static Matrix<value_t> Diagonal(const std::initializer_list<value_t> & il) {
            const int r = il.size();
            Matrix<value_t> diag(Zeros(r, r));
            auto begin = il.begin();
            auto end = il.end();
            //for (int i = 0; i < r && begin != end; ++i) {
            //	diag.at(i, i) = *begin;				 // 待改为迭代器  -ed
            //	++begin;
            //}
            iter be = diag.begin(), en = diag.end();
            for (; be != en && begin != end; ++begin) {
                *be = *begin;
                ++be;
                if (be != en) be.nextRow();
            }
            return diag;
        }

        template<class OTHER_T>
        static Matrix<value_t> DiagonalLike(const Matrix<OTHER_T> & m, value_t* begin, value_t* end) { // 待添异常处理(m非方阵)
            const int r = m.shape().r;
            //Matrix<value_t> diag(Zeros(r, r));
            //for (int i = 0; i < r && begin != end; ++i) {
            //	diag.at(i, i) = *begin;				 // 待改为迭代器  -ed
            //	++begin;
            //}
            return Diagonal(r, begin, end);
            //return diag;
        }
        
        static Matrix<value_t> TriMatrix(index_t r, value_t* begin, value_t* end, bool isUpper = true) { // 待改为迭代器  -ed
            if (r == __unorflag__)  r = static_cast<index_t>( (sqrt( 1 + 8 * (end - begin) ) - 1.0) / 2.0 ); // 自动适配
            Matrix<value_t> tri(Zeros(r, r));		
            iter be = tri.begin(), en = tri.end();
            if (isUpper) {
                for (index_t i = 0; i < r; ++i) {
                    for (index_t j = i; j < r && begin != end; ++begin, ++j) {
                        *be = *begin;
                        ++be;
                    }
                    if (be != en) be += i + 1;
                }
            } else {
                for (index_t i = 0; i < r; ++i) {
                    for (index_t j = 0; j <= i && begin != end; ++begin, ++j) {
                        *be = *begin;	
                        ++be;
                    }
                    if (be != en) be += (r - i - 1);
                }
            }
            return tri;
        }

        static Matrix<value_t> TriMatrix(index_t r, const std::initializer_list<value_t> & il, bool isUpper = true) {
            auto begin = il.begin();
            auto end = il.end();
            if (r == __unorflag__)  r = static_cast<index_t>((sqrt(1 + 8 * (end - begin)) - 1.0) / 2.0); // 自动适配
            Matrix<value_t> tri(Zeros(r, r));
            iter be = tri.begin(), en = tri.end();
            if (isUpper) {
                for (index_t i = 0; i < r; ++i) {
                    for (index_t j = i; j < r && begin != end; ++begin, ++j) {
                        *be = *begin;
                        ++be;
                    }
                    if (be != en) be += i + 1;
                }
            }
            else {
                for (index_t i = 0; i < r; ++i) {
                    for (index_t j = 0; j <= i && begin != end; ++begin, ++j) {
                        *be = *begin;
                        ++be;
                    }
                    if (be != en) be += (r - i - 1);
                }
            }
            return tri;
        }
        
        // same shape
        bool sameShape(const Matrix& other) const { return _data->sameShape(*other._data); }

        // stdout friend function
        friend std::ostream& operator << (std::ostream& os, const Matrix<value_t>& m) {
            return os << "Matrix" << *m._data;
        }

    };

    template<class T>
    inline std::ostream& operator << (std::ostream& os, const MatrixData<T> & m) {
        /*style:
            MatrixData(
            0, 0, 0,
            0, 0, 0,
            0, 0, 0,
            )+'\n'
        
        */
        auto be = m.begin();
        auto en = m.end();
        os << "(\n";
        for (index_t i = 0; i < m.shape.r; ++i) {
            for (index_t j = 0; j < m.shape.c && be != en; ++j, ++be) {
                os << *be << ",\t";				 // 待改为迭代器  -ed
            }
            os << "\n\n";
        }
        os << ")\n";
        return os;
    }

}// end of namespace matrix
#endif