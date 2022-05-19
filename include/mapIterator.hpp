#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP
# include "iterator.hpp"
# include "tree.hpp"

namespace ft
{
    template <class Node>
        class map_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
        {
            public:
                typedef Node*   iterator_type;
                typedef Node    iterator_value;
                typedef typename Node::value_type value_type;
                typedef value_type& reference;
                typedef value_type* pointer;
            
            private:
                iterator_type   _ptr;
                iterator_type   _get_successor(iterator_type node)
                {
                    iterator_type   ret;

                    std::cout << "succe" << std::endl;

                    if (!node)
                        return (NULL);
                    if (node->right)
                    {
                        std::cout << "succe r" << std::endl;
                        ret = node->right;
                        while (ret->left)
                            ret = ret->left;
                    }
                    else
                    {
                        ret = node->parent;
                        std::cout << "succe l" << std::endl;
                        while (ret && !_is_left(node))
                        {
                            node = ret;
                            ret = ret->parent;
                        }
                    }
                    return ret;
                }
                iterator_type   _get_predecessor(iterator_type node)
                {
                    iterator_type res;

                    if (!node)
                        return NULL;
                    if (node->left)
                    {
                        res = node->left;
                        while (res->right)
                            res = res->right;
                    }
                    else
                    {
                        res = node->parent;
                        while (res && _is_left(node))
                        {
                            node = res;
                            res = res->parent;
                        }
                    }
                    return res;
                }
                bool    _is_left(iterator_type node)
                {
                    iterator_type   next;

                    if (!node->left)
                        return false;
                    next = node->left;
                    if (next->is_init)
                        return true;
                    return false;
                }
                bool    _is_right(iterator_type node)
                {
                    iterator_type   next;

                    if (!node->right)
                        return false;
                    next = node->right;
                    if (next->is_init)
                        return true;
                    return false;
                }

            public:
                explicit map_iterator(iterator_type ptr = NULL): _ptr(ptr) {}
                map_iterator(const map_iterator& other) {*this = other;}
                ~map_iterator() {}
                template <class Iter>
                    map_iterator&   operator=(const Iter& other)
                    {
                        if (this != other)
                            _ptr = other.base();
                        return *this;
                    }
                iterator_type   base() {return _ptr;}
                iterator_type base() const {return _ptr;}
                reference   operator*() const {return _ptr->pair;}
                pointer     operator->() const {return &(_ptr->pair);}
                map_iterator&   operator++()
                {
                    std::cout << "++" << std::endl;
                    _ptr = _get_successor(_ptr);
                    std::cout << "++ end" << std::endl;
                    return (*this);
                }
                map_iterator    operator++(int)
                {
                    map_iterator    tmp(*this);

                    ++*this;
                    return tmp;
                }
                map_iterator&   operator--()
                {
                    _ptr = _get_predecessor(_ptr);
                    return *this;
                }
                map_iterator    operator--(int)
                {
                    map_iterator    tmp(*this);

                    --*this;
                    return tmp;
                }
                bool    operator==(const map_iterator& rhs)
                {
                    return _ptr == rhs._ptr;
                }
                bool    operator!=(const map_iterator& rhs)
                {
                    return _ptr != rhs._ptr;
                }
        };

    template <class Node>
        class const_map_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
        {
            public:
                typedef Node*   iterator_type;
                typedef Node    iterator_value;
                typedef typename iterator_value::value_type value_type;
                typedef value_type& reference;
                typedef value_type* pointer;
            
            private:
                iterator_type   _ptr;
               iterator_type   _get_successor(iterator_type node)
                {
                    iterator_type   ret;

                    if (!node)
                        return (NULL);
                    if (node->right)
                    {
                        ret = node->right;
                        while (ret->left)
                            ret = ret->left;
                    }
                    else
                    {
                        ret = node->parent;
                        while (ret && !_is_left(node))
                        {
                            node = ret;
                            ret = ret->parent;
                        }
                    }
                    return ret;
                }
                iterator_type   _get_predecessor(iterator_type node)
                {
                    iterator_type res;

                    if (!node)
                        return NULL;
                    if (node->left)
                    {
                        res = node->left;
                        while (res->right)
                            res = res->right;
                    }
                    else
                    {
                        res = node->parent;
                        while (res && _is_left(node))
                        {
                            node = res;
                            res = res->parent;
                        }
                    }
                    return res;
                }
                bool    _is_left(iterator_type node)
                {
                    iterator_type   next;

                    if (!node->left)
                        return false;
                    next = node->left;
                    if (next->is_init)
                        return true;
                    return false;
                }
                bool    _is_right(iterator_type node)
                {
                    iterator_type   next;

                    if (!node->right)
                        return false;
                    next = node->right;
                    if (next->is_init)
                        return true;
                    return false;
                }

            public:
                explicit const_map_iterator(iterator_type ptr = NULL): _ptr(ptr) {}
                const_map_iterator(const const_map_iterator& other) {*this = other;}
                ~const_map_iterator() {}
                template <class Iter>
                    const_map_iterator&   operator=(const Iter& other)
                    {
                        if (this != other)
                            _ptr = other.base();
                        return *this;
                    }
                iterator_type   base() {return _ptr;}
                iterator_type base() const {return _ptr;}
                reference   operator*() const {_ptr->value;}
                pointer     operator->() const {return &(_ptr->value);}
                const_map_iterator&   operator++()
                {
                    _ptr = _get_successor(_ptr);
                    return (*this);
                }
                const_map_iterator    operator++(int)
                {
                    const_map_iterator    tmp(*this);

                    ++*this;
                    return tmp;
                }
                const_map_iterator&   operator--()
                {
                    _ptr = _get_predecessor(_ptr);
                    return *this;
                }
                const_map_iterator    operator--(int)
                {
                    const_map_iterator    tmp(*this);

                    --*this;
                    return tmp;
                }
                bool    operator==(const const_map_iterator& rhs)
                {
                    return _ptr == rhs._ptr;
                }
                bool    operator!=(const const_map_iterator& rhs)
                {
                    return _ptr != rhs._ptr;
                }
        };
} // namespace ft

#endif