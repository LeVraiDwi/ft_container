#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include "iterator.hpp"
# include "iteratorVector.hpp"
# include "reverseIterator.hpp"

namespace ft
{
    template < typename T, class Allocator = std:: allocator<T> >
    class vector
    {
        //=========================Menber Types======================//
        public:
            typedef T value_type;
            typedef Allocator allocator_type;
            typedef typename allocator_type::size_type size_type;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef vector_iterator<pointer> iterator;
            typedef vector_iterator<const_pointer> const_iterator;
            typedef reverse_iterator<const_iterator> const_reverse_iterator;
	    	typedef reverse_iterator<iterator> reverse_iterator;
        //==========================================================//
        //========Private Menber====================================//
        private:
            pointer         _arr;
            size_type       _size;
            size_type       _capacity;
            allocator_type  _alloc;

            void        _delete(size_type cap)
            {
                for(size_type i = 0; i < _size; i++)
                    _alloc.destroy(_arr + i);
                _alloc.deallocate(_arr, cap);
            }
            template <class InputIterator>
                size_type   _dist(InputIterator first, InputIterator last)
                {
                    size_type res = 0;

                    while (first != last)
                    {
                        res++;
                        first++;
                    }
                    return (res);
                }
        //==========================================================//
        //====================Menber Functions=======================//
        public:
        //Constructeur//
            vector(): _arr(NULL), _size(0), _capacity(0) { }
            explicit vector (const allocator_type& alloc = allocator_type()): _arr(NULL), _size(0), _capacity(0) { _alloc = alloc;}
            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()): _size(n), _capacity(n), _alloc(alloc)
            {
                _arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _capacity; i++)
                    _alloc.construct(_arr + i, val);
            }
            template <class InputIterator>
                vector (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type()): _size(0), _alloc(alloc)
                {
                    InputIterator   tmp = first;
                    while (tmp != last)
                    {
                        _size++;
                        tmp++;
                    }
                    _capacity = _size;
                    _arr = _alloc.allocate(_capacity);
                    for (size_type i = 0; i < _capacity; i++)
                    {
                        _alloc.construct(_arr + i, *(first));
                        first++;
                    }
                }
            vector (const vector& x): _arr(NULL), _size(0), _capacity(0) {*this = x;}
        //operator =//
            vector& operator = (const vector& x)
            {
                if (_arr)
                    _delete(_capacity);
                _size = x._size;
                _capacity = _size;
                _alloc = this->_alloc;
                _arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _capacity; i++)
                {
                    _alloc.construct(_arr + i, x._arr[i]);
                }
                return *this;
            }
        //Destructeur//
            ~vector()
            {
                if (_arr)
                {
                    clear();
                    _alloc.deallocate(_arr, _capacity);
                }
            }
        //Allocator//
            allocator_type get_allocator() const {return _alloc;}
        // Element access//
            reference operator[](size_type n) {return _arr[n];}
            const_reference operator[](size_type n) const  {return _arr[n];}
            reference at(size_type n){
                if (n >= _size)
                    throw std::out_of_range("vector");
                return _arr[n];
            }
            const_reference at(size_type n) const{
                if (n >= _size)
                    throw std::out_of_range("vector");
                return _arr[n];
            }
            reference front() {return _arr[0];}
            const_reference front() const{return _arr[0];}
            reference back() {return _arr[_size];}
            const_reference back() const {return _arr[_size];}
            pointer data() {return _arr;}
            const_pointer data() const {return _arr;}
        //Capacity//
            bool        empty() const{ return (begin() == end());}
            size_type   size() const {return _size;}
            size_type   max_size() const {return _alloc.max_size();}
            size_type	capacity() const {return (_capacity);}
            void        reserve( size_type new_cap )
            {
                pointer new_arr;
                if (new_cap > _alloc.max_size())
                    throw std::length_error("vector");
                if (new_cap > _capacity)
                {
                    new_arr = _alloc.allocate(new_cap);
                    for (size_type i = 0; i < new_cap; i++)
                        _alloc.construct(new_arr + i, _arr[i]);
                    _delete(_capacity);
                    _capacity = new_cap;
                    _arr = new_arr;
                }
            }
        //Modifiers//
            void    clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_arr + i);
                _size = 0;
            }
            void resize(size_type count, value_type value = value_type())
            {
                pointer     new_arr;
                size_type   old_cap;

                if (count > max_size())
                    throw std::length_error("vector");
                old_cap = _capacity;
                if (_capacity < count)
                {
                    if (!_capacity)
                        _capacity = count;
                    while (_capacity < count)
                        _capacity *= 2;
                    new_arr = _alloc.allocate(_capacity);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.construct(new_arr + i, _arr[i]);
                    for (size_type i = _size; i < _capacity; i++)
                        _alloc.construct(new_arr + i, value);
                    _delete(old_cap);
                    _arr = new_arr;
                }
                else if (_size > count)
                    for (size_type i = _size - 1; i >= (int)count; i--)
                        _alloc.destroy(_arr + i);
                else
                    for (size_type i = _size; i < count; i++)
                        _alloc.construct(_arr + i, value);
                _size = count;
            }
            iterator insert(iterator pos, const_reference value)
            {
                insert(pos, 1, value);
                return pos;
            }
            void insert( iterator pos, size_type count, const_reference value )
            {
                size_type   dst = _dist(begin(), pos);
                iterator    old_end = end() - 1;

                resize(_size + count);
                for(iterator it = end() - 1; it != begin()+ (dst + count); it++)
                {
                    *it = *old_end;
                    old_end--;
                }
                for (iterator it = begin() + dst; it != begin() + (dst + count); it++)
                    it = value;
            }
            template< class InputIt >
                void insert(iterator pos, InputIt first, InputIt last)
                {
                    size_type   dst = _dist(begin(), pos);
                    size_type   distance = _dist(first, last);
                    iterator    old_end = end() - 1;
                    value_type  values[distance];

                    resize(_size + distance);
                    for(size_type i = 0; first != last; i++)
                    {
                        values[i] = *first;
                        first++;
                    }
                    for (iterator it = end() - 1; it >= begin() + dst + distance; it--)
                    {
                        *it = *old_end;
                        old_end++;
                    }
                    for(size_type i = 0; i < distance; i++)
                        *(begin() + dst + i) = values[i];
                }
                iterator erase(iterator pos)
                {
                    for (size_type i = pos - this->begin(); i < this->size() - 1; i++)
                        *(_arr + i) = *(_arr + i + 1);
                    _alloc.destroy(_arr + _size - 1);
                    --_size;
                    return pos;
                }
                iterator erase(iterator first, iterator last)
                {
                    size_type   first_dst = _dist(begin(), first);
                    size_type   last_dst  = _dist(begin(), last);
                    iterator    first_end = begin() + first_dst;
                    for (iterator it = begin() + last_dst; it != end(); it++)
                    {
                        *first_end =*it;
                        first_end++;
                    }
                    while (last_dst != _size)
                    {
                        _alloc.destroy(_arr + last_dst);
                        last_dst++;
                    }
                    _size -= _dist(first, last);
                    return (first);
                }
                void swap(vector& other) 
                {
                    size_type	size_tmp = _size;
				    size_type	capacity_tmp = _capacity;
				    pointer		arr_tmp = _arr;

	    			_size = other._size;
	    			_capacity = other._capacity;
	    			_arr = other._arr;
	    			other._size = size_tmp;
	    			other._capacity = capacity_tmp;
	    			other._arr = arr_tmp;
                }
                void push_back(const_reference value) {resize(1, value);}
                void pop_back() 
                {
                    if (!_size)
                        _size -= 1;
                    else
                        resize(_size - 1);
                }
        //iterator//
            iterator begin() {return iterator(_arr);}
            const_iterator begin() const {return const_iterator(_arr);}
            iterator end() {return iterator(_arr + _size);}
            const_iterator end() const {return const_iterator(_arr + _size);}
            iterator rbegin() {return reversse_iterator(end());}
            const_iterator rbegin() const {return const_reverse_iterator(end());}
            iterator rend() {return iterator(begin());}
            const_iterator rend() const {return const_reverse_iterator(begin());}
    };
    //==================================Non MEmber Function============================//
    /*template<class T, class Alloc>
        bool    operator==(const ft::vector<T, alloc>& lhs, const ft::vector<T, Alloc>& rhs)
        {
            if (lhs.size() != rhs.size())
                return false;
            return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
        }*/ //need equal
    template<class T, class Alloc>
        bool    operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
        {
            return (!(lhs == rhs));
        }
    /*template<class T, class Alloc>
        bool    operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
        {
            return (ft::lexicographical_comapre(lhs.begin(), lhs.end9), rhs.begin(), rhs.end()));
        }*/ //need lexico
    template<class T, class Alloc>
        bool    operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
        {
                return (!(rhs < lhs));
        }
    template<class T, class Alloc>
        bool    operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
        {
            return (rhs < lhs);
        }
    template<class T, class Alloc>
        bool    operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
        {
            return (!(rhs > lhs));
        }
    template <class T, class Alloc>
		void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
		{
			x.swap(y);
		}
}
#endif