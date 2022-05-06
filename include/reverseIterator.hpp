#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP
# include "iterator.hpp"
namespace ft
{
    template <class Iter>
        class reverse_iterator : public iterator <typename iterator_traits<Iter>::iterator_category, typename iterator_traits<Iter>::value_type,
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
                reverse_iterator(): _current() {}
                explicit reverse_iterator(iterator_type x): _current(x) {}
                template< class U >
                    reverse_iterator( const reverse_iterator<U>& other ) {*this = other;}
                //Destructeur//
                ~reverse_iterator() {}
                //Operator Overload//
                template< class U >
                    reverse_iterator& operator=( const reverse_iterator<U>& other )
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
                reverse_iterator& operator++()
                {
                    --_current;
                    return *this;
                }
                reverse_iterator& operator++(int)
                {
                    reverse_iterator tmp(*this);

                    --_current;
                    return tmp;
                }
                reverse_iterator& operator--()
                {
                    ++_current;
                    return *this;
                }
                reverse_iterator& operator--(int)
                {
                    reverse_iterator tmp(*this);

                    ++_current;
                    return tmp;
                }
                reverse_iterator operator+( difference_type n ) const {return reverse_iterator(_current - n);}
                reverse_iterator operator-( difference_type n ) const {return reverse_iterator(_current + n);}
                reverse_iterator& operator+=( difference_type n ) 
                {
                    _current -= n;
                    return *this;
                }
                reverse_iterator& operator-=( difference_type n ) 
                {
                    _current += n;
                    return *this;
                }
        };
        //Non Menber Function//
        template< class Iterator1, class Iterator2 >
            bool operator==( const std::reverse_iterator<Iterator1>& lhs,
            const std::reverse_iterator<Iterator2>& rhs )
            {
                return (lhs.base() == rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
            const std::reverse_iterator<Iterator2>& rhs )
            {
                return (lhs.base() != rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator>( const std::reverse_iterator<Iterator1>& lhs,
            const std::reverse_iterator<Iterator2>& rhs )
            {
                return (lhs.base() > rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
            const std::reverse_iterator<Iterator2>& rhs )
            {
                return (lhs.base() >= rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator<( const std::reverse_iterator<Iterator1>& lhs,
            const std::reverse_iterator<Iterator2>& rhs )
            {
                return (lhs.base() < rhs.base());
            }
        template< class Iterator1, class Iterator2 >
            bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
            const std::reverse_iterator<Iterator2>& rhs )
            {
                return (lhs.base() <= rhs.base());
            }
        template< class Iter >
            reverse_iterator<Iter> operator+( typename ft::reverse_iterator<Iter>::difference_type n,
                const ft::reverse_iterator<Iter>& it)
            {
                return ft::reverse_iterator<Iter>(it.base() - n);
            }
        template< class Iter >
            reverse_iterator<Iter> operator-( typename ft::reverse_iterator<Iter>::difference_type n,
                const ft::reverse_iterator<Iter>& it)
            {
                return ft::reverse_iterator<Iter>(it.base() + n);
            }
}
#endif