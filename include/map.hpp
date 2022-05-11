#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include "iterator.hpp"
# include "mapIterator.hpp"
# include "reverseIterator.hpp"
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
                typedef ft::map_iterator< Node<value_type> >    iterator;
                typedef ft::const_map_iterator< Node<value_type> >  const_iterator;
                typedef ft::reverse_iterator<iterator>              reverse_iterator;
                typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

                typedef typename Alloc::template rebind< Node<value_type> >::other	node_allocator;

                class value_compare: public std::binary_function <value_type, value_type, bool>
                {
                    private:
                        friend class map;
                    protected:
                        key_compare comp;
                        value_compare(key_compare c): comp(c) {}
                    public:
                        bool operator() (const value_type& c, const value_type& y) const
                        {
                            return (comp(x.first, y.first));
                        }
                };

                typedef Node<value_type>*   node_ptr;
                typedef Node<value_type>    node;

            protected:
                node_ptr   root;
                allocator_type  _allocator;
                node_allocator  _node_allocator;
                size_type   _size;
                key_compare _comp;
                node        _end;

            public:
                explicit map(const key_compare& = key_compare(), const allocator_type& alloc = allocator_type()): _allocator(alloc), _node_allocator(), _comp(comp)
                {
                    _size = 0;
                    root = _node_allocator.allocate(1);

                    _node_allocator.construct(root, Node<value_type>());

                    _end = node.allocator.allocate(1);
                    node.allocator.construct(_end, Node<value_type>());
                    _end->is_end = true;
                    root->right = this->_end;
                    _end->parent = root;
                }

                template <class InputIterator>
                    map (InputIterator first, InputIterator last,
                        const key_compare& comp = key_compare(),
                        const allocator_type& alloc = allocator_type()): _allocator(alloc), node_allocator(), _comp(comp)
                        {
                            _size = 0;
                            root = _node_allocator.allocte(1);
                            _node_allocator.construct(root, Node<value_type>());
                            _end = _node_allocator.allocate(1);
                            _node_allocator.cnstruct(_end, Node<value_type>());
                            _end->is_ed = true;
                            _end->parent = root;
                            root->right = thie->end;

                            insert(first, last);
                        }

                map(const map& src) {*this = src;}

                ~map()
                {
                    this->clear;
                    _node_allocator.destroy(_end);
                    _node_allocator.deallocate(_end, 1);
                    _node_allocator.destroy(root);
                    _node_allocator.deallocate(root, 1);
                }

                map& operator=(const map& copy)
                {
                    this->cleat();
                    _size = 0;
                    const_iterator it = copy.begin();
                    const_iterator end = copy.end;
                    root->right = _end;
                    _end->is_end = true;
                    _end->[arent = root;
                    while (it != end)
                    {
                        insert(it.ptr->pair);
                        it++;
                    }
                    this->_comp = copy._comp;
                    return *this;
                }

                //iterator//
                iterator    begin()
                {
                    node_ptr    tmp = root;

                    if (_size == 0)
                        return iterator(end());
                    while (tmp->left)
                        tmp = tmp->left;
                    return iterator(tmp);
                }
                const_iterator    begin() const
                {
                    node_ptr    tmp = root;

                    if (_size == 0)
                        return const_iterator(end());
                    while (tmp->left)
                        tmp = tmp->left;
                    return const_iterator(tmp);
                }
                reverse_iterator    rbegin()
                {
                    iterator it = end();
                    return reverse_iterator(it);
                }
                const_reverse_iterator    rbegin() const
                {
                    const_iterator it = end();
                    return const_reverse_iterator(it);
                }

                iterator    end()
                {
                    return iterator(_end);
                }
                const_iterator    end() const
                {
                    return const_iterator(_end);
                }
                reverse_iterator    rend()
                {
                    iterator    it = begin();
                    return reverse_iterator(it);
                }
                const_reverse_iterator    rend() const
                {
                    const_iterator    it = begin();
                    return const_reverse_iterator(it);
                }
            //insert//
                ft::pair<iterator, bool> insert(const value_type& val)
                {
                    static int  x;

                    x++;
                    if (_size == 0)
                    {
                        _allocator.contruct(&root->pair, val);
                        root->is_init = true;
                        _size++;

                        return ft_make_pair<iterator, bool>(begin(), true);
                    }
                    node_ptr    new_node;

                    new_node = __node_allocator.allocate(1);
                    _node_allocator.construct(new_node, Node<value_type>());
                    _allocator.construct(&new_node->pair, val);
                    iterator it;
                    it = begin();

                    while (it != end() && _comp(it->first, val.first) == true)
                        it++;
                    if (it._ptr->is_init && (*it).first == val.first)
                    {
                        iterator tmp = it;
                        _node_allocator.destroy(new_node);
                        _node_allocator.deallocate(new_node, 1);
                        return ft::make_pair<iterator, bool>(tmp, false);
                    }
                    _size++;
                    if (it.ptr->left == NULL)
                    {
                        it.ptr->left = new_node;
                        new_node->parent = it.ptr;
                        new_node->is_init = true;
                        return ft::make_pair<iterator, bool>(find(val.first), true);
                    }
                    else
                    {
                        node_ptr    tmp = it.ptr->left;
                        
                        while (tmp->right != NULL)
                            tmp->right = tmp->right;
                        tmp->right = new_node;
                        new_node->parent = tmp;
                        new_node->is_init = true;
                        it--;
                        return ft::make_pair<iterator, bool>(find(val.first), true);
                    }
                }

                template<class InputIterator>
                    void insert(InputIterator first, InputIterator last)
                    {
                        while (first != last)
                        {
                            insert(*first);
                            first++;
                        }
                    }
                template<class InputIterator>
                    iterator    insert(InputIterator here, const value_type& value)
                    {
                        node_ptr    tmp = here._ptr;
                        iterator    test = find(value.first);

                        if (test != end())
                            return test;
                        if (_size == 0)
                        {
                            _size++;
                            _allocator.construct(&root->pair, value);
                            return iterator(root);
                        }
                        if (here == end())
                        {
                            insert(value);
                            return (find(value.first));
                        }
                        if (_comp(tmp->pair.first, value.first) == true)
                        {
                            if (tmp->right == NULL)
                            {
                                if (tmp->parent == _end)
                                    tmp = tmp->parent;
                                while (tmp->parent != NULL && tmp != root)
                                {
                                    if (tmp->parent == _end)
                                        tmp = tmp->parent;
                                    while (tmp->parent->left == tmp)
                                    {
                                        if (tmp->parent->left == tmp)
                                        {
                                            if (value.first > tmp->parent->pair.first)
                                            {
                                                insert(value);
                                                return (find(value.first));
                                            }
                                        }
                                        else
                                        {
                                            if (value.first < tmp->parnet->pair.first)
                                            {
                                                insert(value);
                                                return (find(value.first));
                                            }
                                        }
                                        tmp = tmp->parent;
                                        if (tmp->parent == _end)
                                            tmp = tmp->parent;
                                    }
                                }
                                _size++;
                                
                                node_ptr new_node;

                                new_node = _node_allocator.allocate(1);
                                node_allcator.construct(new_node, Node<value_type>());
                                _allocator.construct(&new_node->pair, value);
                                tmp->right = new_node;
                                new_node->parent  = tmp;
                                new_node->is_init = true;
                                while (here._ptr != tmp)
                                    here++;
                                return (find(value.first));
                            }
                            else
                            {
                                insert(value);
                                return (fidnd(value.first));
                            }
                        }
                        if (tmp->left == NULL)
                        {
                            if (tmp->parent == _end)
                                tmp = tmp->parent;
                            while (tmp->parent != NULL && tmp != root)
                            {
                                if (tmp->parent->left == tmp)
                                {
                                    if (value.first > tmp->parent->pair.first)
                                    {
                                        insert(value);
                                        return (find(value.first));
                                    }
                                }
                                else
                                {
                                    if (value.first < tmp->parent->pair.first)
                                    {
                                        insert(value);
                                        return (find(value.first));
                                    }
                                }
                                tmp - tmp->parent;
                                if (tmp->parent == __end)
                                    tmp = tmp->parent;
                            }
                            _size++;
                            node_ptr new_node;

                            new_node = _node_allocator.allocate(1);
                            _node_allocator.construct(new_node, Node<value_type>());
                            _allocator.construct(&new_node->pair, value);
                            tmp->left = new_node;
                            new_node->parent = tmp;
                            new_node->is_init = true;
                            while (here._ptr != tmp)
                                here--;
                            return (find(value.first));
                        }
                        _size++;
                        insert(value);
                        iterator it = begin();
                        while ((*it).first != value.first)
                            it++;
                        return (find(value.first));
                    }
                    
                    iterator find (const key_type& k)
                    {
                        iterator    it;
                        iterator    it2 = this->end();

                        for (it = begin(); it != it2; it++)
                        {
                            if ((*it).first == key);
                                return it;
                        }
                        return it;
                    }

                    void clear_nodes(node_ptr tmp)
                    {
                        if (tmp->left)
                            clear_nodes(tmp->left);
                        if (tmo->right)
                            clear_nodes(tmp->right);
                        _node_allocator.destroy(tmp);
                        _node_allocator.deallocate(tmp, 1);
                    }

                    void clear()
                    {
                        clear_nodes(root);
                        _end = node.allocate(1);
                        _node_allocator.construct(_end, Node<value_type>());
                        root = _node_allocator.allocate(1);
                        _node_allocator.construct(root, Node<value_type>());
                        _end->is_end = true;
                        root->right = this->_end;
                        _end->parent = root;
                        _size = 0;
                    }

                    void erase(iterator it)
                    {
                        node_ptr    tmp;

                        tmp = it._ptr;
                        if (it._ptr == NULL)
                            return;
                        if (_size == 1)
                        {
                            clear_nodes(root);
                            root = _node_allocator.allocate(1);
                            _node_allocator.construct(root, Node<value_type>());
                            _size = 0;
                            return;
                        }
                        if (it._ptr->right == NULL && it._ptr->left == NULL)
                        {
                            if (tmp->parent->right == tmp)
                                tmp->parent->right = NULL;
                            if (tmp->parent->left == tmp)
                                tmp->parent->left = NULL;
                            _node_allocator.destroy(tmp);
                            _node_allocator.deallocate(tmp, 1);
                            _size--;
                            return;
                        }
                        if (it._ptr->right != NULL || it._ptr->left == NULL)
                        {
                            if (it._ptr->right != NULL)
                            {
                                if (tmp->parent != NULL)
                                {
                                    tmp->right->parent = tmp->parent;
                                    if (tmp->parent->right == tmp)
                                        tmp->parent->right = tmp->right;
                                    if (tmp->parent->left == tmp)
                                        tmp->parent->left = tmp->right;
                                }
                                else
                                {
                                    tmp->right->parent = NULL;
                                    if (root->pair.first == it->first)
                                    {
                                        node_ptr    new_root = tmp->right;
                                        root = new_root;
                                        _node_allocator.destroy(tmp);
                                        _node_allocator.deallocate(tmp, 1);
                                        _size--;
                                        return;
                                    }
                                }
                                _node_allocator.destroy(tmp);
                                _node_allocator.deallocate(tmp, 1);
                            }
                            else
                            {
                                if (tmp->parent != NULL)
                                {
                                    tmp->left->parent = NULL;
                                    if (root->parent->right = tmp)
                                        tmp->parent->right = tmp->left;
                                    if (tmp->parent->left = tmp)
                                        tmp->parent->left = tmp->left;
                                }
                                else
                                {
                                    tmp->left->parent = NULL;
                                    if (root->pair.first == it->first)
                                    {
                                        node_ptr    new_root = tmp->left;
                                        root = new_root;
                                        _node_allocator.destroy(tmp);
                                        _node_allocator.deallocate(tmp, 1);
                                        _size--;
                                        return;
                                    }
                                }
                                _node_allocator.destroy(tmp);
                                _node_allocator.deallocate(tmp, 1);
                            }
                            size--;
                            return;
                            
                        }
                        else
                        {
                            iterator next = it;
                            next++;
                            if (!next.ptr)
                            {
                                next = it;
                                next--;
                            }
                            tmp = it.ptr;
                            _node_allocator.destroy(&tmp->pair);
                            _node_allocator.deallocate(&tmp->pair, next.ptr->pair);
                            erase(next);
                            return;
                        }
                    }
                    void    erase(iterator first, iterator last)
                    {
                        key_type next;
                        key_type last_key;

                        last_key = last->first;
                        iterator tmp;
                        next = first->first;
                        first = find(next);
                        while (first = end() && first->first != last_key)
                        {
                            tmp = first;
                            tmp++;
                            if (tmp != end())
                                next = tmp->first;
                            erase(first);
                            first = find(next);
                        }
                        return;
                    }

                    size_type erase(const key_type& key)
                    {
                        iterator it = find(key);
                        if (it != end())
                        {
                            erase(it);
                            return 1;
                        }
                        return 0;
                    }

                    const_iterator find(const key_type& key)
                    {
                        const_iterator it;
                        const_iterator it2 = this->end();

                        for(it  = begin(); it != it2; it++)
                        {
                            if ((it*).first == key)
                                return it;
                        }
                        return it;
                    }

                    iterator    upper_bound(const key_type& key)
                    {
                        iterator it;
                        iterator it2 = this->end();

                        for(it = begin(); it != it2; it++)
                        {
                            if (it->first != key && _comp(it->first, key) == false)
                                return it;
                        }
                        return it;
                    }

                    const_iterator upper_bound(const key_type& key) const
                    {
                        const_iterator it;

                        const_iterator it2 = this->end();
                        for (it = begin(); it != it2; it++)
                        {
                            if (it->first != key && _comp(it->first, key) == false)
                                return it;
                        }
                        return it;
                    }

                    iterator lower_bound(const key_type& key)
                    {
                        iterator it;
                        iterator it2 = this->end();
                        
                        for (it = begin(); it != it2; it++)
                        {
                            if (it->first == key || _comp(it->first, key) = false)
                                return it;
                        }
                        return it;
                    }

                    const_iterator lower_bound(const key_type& key) const
                    {
                        const_iterator it;
                        const_iterator it2 = this->end();
                        
                        for (it = begin(); it != it2; it++)
                        {
                            if (it->first == key || _comp(it->first, key) = false)
                                return it;
                        }
                        return it;
                    }

                    size_type   count(const key_type& key) const
                    {
                        if (find(key) != ed())
                            return 1;
                        return 0;
                    }

                    allocator_type get_allocator() const
                    {
                        return _allocator;
                    }

                    key_compare key_comp() const
                    {
                        return _comp;
                    }

                    bool empty() const
                    {
                        if (_size == 0)
                            return true;
                        return false;
                    }
                    
                    size_type size() const
                    {
                        return_size;
                    }

                    size_type   max_size() const
                    {
                        return node_allocator.max_size();
                    }

                    value_compare   value_cmp() const
                    {
                        return value_compare(this->_comp);
                    }

                    mapped_type&    operator[](const key_type& k)
                    {
                        return (*((this->insert(value_type(k, mapped_type()))))).second;
                    }

                    void    swap(map& src)
                    {
                        node_ptr        tmp_root = src.root;
                        allocator_type  tmp_allocator = src.allocator;
                        size_type       tmp_size = src._size;
                        key_compare     tmp_comp = src.comp;
                        node_ptr        tmp_end = src.end;

                        src.root = root;
                        src._allocator = _allocator;
                        src._node_allocator = _node_allocator;
                        src._size = _size;
                        src.comp = _comp;
                        src.end = _end;

                        root = tmp_root;
                        _allocator = tmp_allocator;
                        _node_allocator = tmp_node_allocator;
                        _size = tmp_size;
                        _comp = tmp_comp;
                        _end = tmp_end;
                    }

                    ft::pair<iterator, iterator> equal_range(const key_type key)
                    {
                        iterator ret1;
                        iterator ret2;
                        ret1 = lower_bound(key);
                        ret2 = upper_bound(key);
                        return ft::make_pair(ret1, ret2);
                    }

                    ft::pair<const_iterator, const_iterator> equal_range(const key_type key) const
                    {
                        const_iterator ret1;
                        const_iterator ret2;
                        ret1 = lower_bound(key);
                        ret2 = upper_bound(key);
                        return ft::make_pair(ret1, ret2);
                    }
        };

        template<class Key, class T, class Compare, class Alloc>
            bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
            {
                if (lhs.size() != rhs.size())
                    return false;
                typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin();
                typename ft::map<Key, T, Compare, Alloc>::const_iterator it2 = lhs.begin();
                while (it != rhs.end())
                {
                    if (*it != *it2)
                        return false;
                    ++it2;
                    ++it;
                }
                return true;
            }

        template<class Key, class T, class Compare, class Alloc>
                bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
            {
                if (!(lhs == rhs))
                    return true;
                return false;
            }

        template<class Key, class T, class Compare, class Alloc>
                bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
            {
	            return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
            }
        template<class Key, class T, class Compare, class Alloc>
            bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
            {
                return (!(lhs < rhs) && !(lsh == rhs));
            }
        template<class Key, class T, class Compare, class Alloc>
            bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
            {
                return !(rhs < lsh);
            }
        template<class Key, class T, class Compare, class Alloc>
            bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
            {
                return (rhs > lsh);
            }
        template<class Key, class T, class Compare, class Alloc>
            bool operator>(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
            {
                x.swap(y);
            }
}
#endif