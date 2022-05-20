#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP
# include "iterator.hpp"
namespace ft
{
    template <class Iter>
        class reverseIterator : public iterator <typename iterator_traits<Iter>::iterator_category, typename iterator_traits<Iter>::value_type,
            typename iterator_traits<Iter>::difference_type, typename iterator_traits<Iter>::pointer, typename iterator_traits<Iter>:: reference>
        {
            //Menber type//
            public:
                typedef             Iter                                        iterator_type;
                typedef typename    iterator_traits<Iter>::iterator_category    iterator_category;
                typedef typename    iterator_traits<Iter>::value_type           value_type;
                typedef typename    iterator_traits<Iter>::difference_type      difference_type;
                typedef typename    iterator_traits<Iter>::pointer              pointer;
                typedef typename    iterator_traits<Iter>::reference            reference;
            private:
                iterator_type _current;
            //Menber Function//
            public:
                //constructor//
                reverseIterator(): _current() {}
                explicit reverseIterator(iterator_type x): _current(x) {}
                template< class U >
                    reverseIterator( const reverseIterator<U>& other ) {*this = other;}
                //Destructeur//
                ~reverseIterator() {}
                //Operator Overload//
                template< class U >
                    reverseIterator& operator=( const reverseIterator<U>& other )
                    {
                        _current = other.base();
                        return *this;
                    }
                iterator_type base() const
                {
                    return _current;
                }
                reference operator*() const 
                {
                    iterator_type tmp = _current;
                    return (*--tmp);
                }
                pointer operator->() const {return (&(*_current));}
                reference   operator[](difference_type n) const {return *(*this + n);}
                reverseIterator& operator++()
                {
                    --_current;
                    return *this;
                }
                reverseIterator& operator++(int)
                {
                    reverseIterator& tmp(*this);

                    --_current;
                    return tmp;
                }
                reverseIterator& operator--()
                {
                    ++_current;
                    return *this;
                }
                reverseIterator& operator--(int)
                {
                    reverseIterator& tmp(*this);

                    ++_current;
                    return tmp;
                }
                reverseIterator operator+( difference_type n ) const {return reverseIterator(_current - n);}
                reverseIterator operator-( difference_type n ) const {return reverseIterator(_current + n);}
                reverseIterator& operator+=( difference_type n ) 
                {
                    _current -= n;
                    return *this;
                }
                reverseIterator& operator-=( difference_type n ) 
                {
                    _current += n;
                    return *this;
                }
        };
        //Non Menber Function//
        template< class Iterator1, class Iterator2 >
            bool operator==( const ft::reverseIterator<Iterator1>& lhs,
            const ft::reverseIterator<Iterator2>& rhs )
            {
                return (lhs.base() == rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator!=( const ft::reverseIterator<Iterator1>& lhs,
            const ft::reverseIterator<Iterator2>& rhs )
            {
                return (lhs.base() != rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator>( const ft::reverseIterator<Iterator1>& lhs,
            const ft::reverseIterator<Iterator2>& rhs )
            {
                return (lhs.base() > rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator>=( const ft::reverseIterator<Iterator1>& lhs,
            const ft::reverseIterator<Iterator2>& rhs )
            {
                return (lhs.base() >= rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator<( const ft::reverseIterator<Iterator1>& lhs,
            const ft::reverseIterator<Iterator2>& rhs )
            {
                return (lhs.base() < rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator<=( const ft::reverseIterator<Iterator1>& lhs,
            const ft::reverseIterator<Iterator2>& rhs )
            {
                return (lhs.base() <= rhs.base());
            }
        template< class Iter >
            reverseIterator<Iter> operator+( typename ft::reverseIterator<Iter>::difference_type n,
                const ft::reverseIterator<Iter>& it)
            {
                return ft::reverseIterator<Iter>(it.base() - n);
            }
        template< class Iter >
            reverseIterator<Iter> operator-( typename ft::reverseIterator<Iter>::difference_type n,
                const ft::reverseIterator<Iter>& it)
            {
                return ft::reverseIterator<Iter>(it.base() + n);
            }
}
#endif