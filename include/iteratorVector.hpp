#ifndef ITERATORVECTOR_HPP
# define ITERATORVECTOR_HPP
# include "iterator.hpp"

namespace ft
{
    template <class Iter>
        class vector_iterator
        {
            //Menber Type//
            public:
                typedef             Iter                                                iterator_type;
                typedef typename    ft::iterator_traits<iterator_type>::value_type      value_type;
                typedef typename    ft::iterator_traits<iterator_type>::reference       reference;
                typedef typename    ft::iterator_traits<iterator_type>::pointer         pointer;
                typedef typename    ft::iterator_traits<iterator_type>::difference_type difference_type;
                typedef typename    ft::iterator_traits<iterator_type>::iterator_type   iterator_category;
            private:
                iterator_type   _ptr;
            //Menber Function//
            public:
                //Constructeur//
                vector_iterator(): _ptr(NULL) {}
                vector_iterator(pointer ptr): _ptr(ptr) {}
                template <class It>
                    vector_iterator(const vector_iterator<It>& other) {*this = other;}
                //Destructeur//
                ~vector_iterator() {};
                //Operator Overload//
                template <class It>
                    vector_iterator&    operator=(const vector_iterator<It>& rhs)
                    {
                        this->_ptr = rhs.base();
                        return *this;
                    }
                pointer             base() const {return _ptr; }
                pointer             operator->() const {return _ptr;}
                reference           operator*() const {return *_ptr;}
                reference           operator[](difference_type n) const {return *(_ptr + n);}
                vector_iterator&    operator++()
                {
                    _ptr++;
                    return *this;
                }
                vector_iterator&    operator++(int)
                {
                    vector_iterator tmp = *this;

                    _ptr++;
                    return (tmp);
                }
                vector_iterator&    operator--()
                {
                    _ptr--;
                    return *this;
                }
                vector_iterator&    operator--(int)
                {
                    vector_iterator tmp = *this;

                    _ptr++;
                    return tmp;
                }
                vector_iterator     operator+(difference_type n) {return vector_iterator(_ptr + n);}
                vector_iterator     operator-(difference_type n) {return vector_iterator(_ptr - n);}
                vector_iterator     operator-=(difference_type n)
                {
                    _ptr -= n;
                    return (*this);
                }
        };
    //Non Menber Function//
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator-(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return lhs.base() - rhs.base();
        }
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator+(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return lhs.base() + rhs.base();
        }
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator==(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return (lhs.base() == rhs.base());
        }
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator!=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return (!(lhs == rhs));
        }
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator>(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return (lhs.base() > rhs.base());
        }
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator>=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return (lhs.base() >= rhs.base());
        }
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator<(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return (lhs.base() < rhs.base());
        }
    template <class iter1, class iter2>
        typename ft::vector_iterator<iter1>::difference_type
        operator<=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
        {
            return (lhs.base() <= rhs.base());
        }
}
#endif