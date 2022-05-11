#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include "iterator.hpp"
# include "mapIterator.hpp"
# include <functional>
# include <memory>

namespace ft
{
    template<class Key, class T, class compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
        class map
        {
            public:
                //Menber Types//
                typedef Key key_type;
                typedef T mapped_type;
                typedef compare key_compare;
                typedef Alloc allocator_type;
                typedef typename allocator_type::value_type value_type;
                typedef typename allocator_type::reference referencce;
                typedef typename allocator_type::const_reference const_reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;
                typedef typename allocator_type::size_type size_type;
                typedef typename allocator_type::different_type different_type;

                typedef typename Allocator::template rebind<Node<value_type> >::other	node_allocator;

                
        };
}
#endif