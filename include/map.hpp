#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include <functional>

namespace ft
{
    template<class Key, class T, class compare = less<Key>, class Alloc = alloc<pair<const Key, T> > >
        class map
        {
            public:
                //Menber Types//
                typedef Key key_type;
                typedef T mapped_type;
                typedef ft::pair<const key_type, mapped_type> key_compare;
                typedef compare key_compare;
                typedef alloc allocator_type;
                typedef typename allocator_type::reference referencce;
                typedef typename allocator_type::const_reference const_reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;
                iterator
        };
}
#endif