#ifndef ITERATOR_HPP
# define ITERATOR_HPP
namespace ft
{
    //iterator tag//
    struct  intput_iterator_tag {};
    struct  output_iterator_tag {};
    struct  forward_iterator_tag        : public intput_iterator_tag {};
    struct  bidirectional_iterator_tag  : public forward_iterator_tag {};
    struct  random_access_iterator_tag  : public bidirectional_iterator_tag {};
    
    template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        struct iterator
        {
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category  iterator_category;
        };

    template< class Iter >
        struct iterator_traits
        {
            typedef typename    Iter::difference_type   difference_type;
            typedef typename    Iter::value_type        value_type;
            typedef typename    Iter::pointer           pointer;
            typedef typename    Iter::reference         reference;
            typedef typename    Iter::iterator_category iterator_category;
        };

    template< class T >
        struct iterator_traits<T*>
        {
            typedef ptdiff_t                    difference_type;
            typedef T                           value_type;
            typedef T*                          pointer;
            typedef T&                          reference;
            typedef random_access_iterator_tag  iterator_category; 
        }

    template< class T >
        struct iterator_traits<const T*>
        {
            typedef ptdiff_t                    difference_type;
            typedef const T                     value_type;
            typedef const T*                    pointer;
            typedef T&                          reference;
            typedef random_access_iterator_tag  iterator_category; 
        }
}
#endif