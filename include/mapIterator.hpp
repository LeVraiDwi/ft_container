#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP
# include "iterator.hpp"

namespace ft
{
    template <class Node>
        class map_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
        {
            public:
                typedef Node*   iterator_type;
                typedef Node    iterator_value;
                typedef typename iterator_value::value_type value_type;
                typedef value_type& reference;
                typedef value_type* pointer;
            
            private:
                iterator_type   _ptr;
                iterator_type	_get_successor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->right)
				{
					res = node->right;
					while (res->left)
						res = res->left;
				}
				else
				{
					res = node->parent;
					while (res && !node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
			iterator_type	_get_predecessor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->left)
				{
					res = node->left;
					while (res->right)
						res = res->right;
				}
				else
				{
					res = node->parent;
					while (res && node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
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
                reference   operator*() const {_ptr->value;}
                pointer     operator->() const {return &(_ptr->value);}
                map_iterator&   operator++()
                {
                    _ptr = _get_successor(_ptr);
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
                iterator_type	_get_successor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->right)
				{
					res = node->right;
					while (res->left)
						res = res->left;
				}
				else
				{
					res = node->parent;
					while (res && !node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
			iterator_type	_get_predecessor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->left)
				{
					res = node->left;
					while (res->right)
						res = res->right;
				}
				else
				{
					res = node->parent;
					while (res && node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
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