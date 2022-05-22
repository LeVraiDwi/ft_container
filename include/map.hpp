#ifndef MAP_HPP
# define MAP_HPP
# include <functional>
# include <memory>
# include "pair.hpp"
# include "iterator.hpp"
# include "mapIterator.hpp"
# include "reverseIterator.hpp"
# include "algo.hpp"
# include "tree.hpp"

namespace ft {
	template <class Key, class Value, class Cmp= std::less<Key>, class A=  std::allocator< pair<const Key, Value> > >
	class map
	{
		public:
			// types:
			typedef Key 							key_type;
			typedef Value 							mapped_type;
			typedef ft::pair<const Key, Value> 			value_type;
			typedef Cmp 							key_compare;

			//typedef A _allocator;
			typedef A 								allocator_type;
			typedef typename A::reference 			reference;
			typedef typename A::const_reference 	const_reference;
			typedef typename A::pointer 			pointer;
			typedef typename A::const_pointer 		const_pointer;
			typedef tree_node<value_type>* 			Tnode;  
			typedef tree_node<value_type> 			testing;
			typedef map_iterator<value_type> 			iterator; 
			typedef const_map_iterator<value_type> 	const_iterator; 
			typedef typename A::size_type 			size_type;
			typedef typename A::difference_type 	difference_type;
			typedef typename ft::reverseIterator<iterator> reverse_iterator;
			typedef typename ft::reverseIterator<const_iterator> const_reverse_iterator; //...

			protected:
				Tnode 							root;
				A  								_allocator;
				typedef typename A::template 	rebind<testing>::other node_allocator_type;
				node_allocator_type 			node_allocator;
				size_type 						_size;
				Cmp 							_comp;
				Tnode							_end;
			
			//Need this class for value_comp function 
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				public:
					Cmp _comp;
					value_compare (Cmp c) : _comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return _comp(x.first, y.first);
					}
			};
			
			public:

			

			//CONSTRUCTOR
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :  _allocator(alloc), node_allocator(), _comp(comp)
				
			{	
				_size = 0;
				//root->end = false;
				root = node_allocator.allocate(1);
				
				node_allocator.construct(root, tree_node<value_type>());

				_end = node_allocator.allocate(1);
				node_allocator.construct(_end, tree_node<value_type>());

				_end->is_end = true;
				root->right = this->_end;
				_end->parent = root;
				
			}			
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0) :  _allocator(alloc), node_allocator(), _comp(comp)
			{
				_size = 0;
				root = node_allocator.allocate(1);
				node_allocator.construct(root, tree_node<value_type>());
				_end = node_allocator.allocate(1);
				node_allocator.construct(_end, tree_node<value_type>());
				_end->is_end = true;
				_end->parent = root;
				root->right = this->_end;

				insert(first, last);

			}

			map(const map& src) : _allocator(src._allocator),  node_allocator(src.node_allocator), _comp(src._comp)
			{
				_size = 0;
				root = node_allocator.allocate(1);
				node_allocator.construct(root, tree_node<value_type>());
				_end = node_allocator.allocate(1);
				node_allocator.construct(_end, tree_node<value_type>());
				root->right = this->_end;
				_end->is_end = true;
				_end->parent = root;
				this->insert(src.begin(), src.end());
			}
 			
			map& operator=(const map& copy)
			{
				this->clear();
				_size = 0;
				const_iterator it = copy.begin();
				const_iterator end = copy.end();
				root->right = _end;
				_end->is_end = true;
				_end->parent = root;
				while (it != end)
				{
					insert(it.ptr->pair);
					it++;
				}
				
				this->_comp = copy._comp;
			
				return(*this);
				
			}

			~map()
			{	
				this->clear();
				node_allocator.destroy(_end);
				node_allocator.deallocate(_end, 1);
				node_allocator.destroy(root);
				node_allocator.deallocate(root, 1);
				
			}

			//BEGIN
			iterator begin(void)
			{
				if (_size == 0)
					return iterator (end());
				Tnode tmp = root;
				while (tmp->left)
					tmp = tmp->left;
				return iterator(tmp);
			}

			const_iterator begin(void) const
			{
				if (_size == 0)
					return const_iterator (end());
				Tnode tmp = root;
				while (tmp->left)
					tmp = tmp->left;
				return const_iterator(tmp);
			}

			reverse_iterator rbegin(void)
			{
				iterator it = end();
				return reverse_iterator(it); 
				
			}
			
			const_reverse_iterator rbegin(void) const
			{
				const_iterator it = end();
				return const_reverse_iterator(it); 
			}

			//END
			iterator end(void)
			{
				return iterator(_end);
			}

			const_iterator end(void) const
			{
				return const_iterator(_end);
			}

			reverse_iterator rend(void)
			{
				iterator it = begin();
				return reverse_iterator(it);
			}

			const_reverse_iterator rend(void) const
			{
				const_iterator it = begin();
				return const_reverse_iterator(it);

			}

			//INSERT
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				static int x;
				x++;
				if (_size == 0)
				{
					_allocator.construct(&root->pair, val);
					root->is_init = true;
					_size++;
					
					return ft::make_pair<iterator, bool>(begin(), true);
				}
				Tnode new_node;
				new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, tree_node<value_type>());
				_allocator.construct(&new_node->pair, val);
				iterator it;
				it = begin();

				// ADD VALUE AT THE LEFT OF THE BINARY TREE
				while (it != end() && _comp(it->first, val.first) == true)
					it++;
				if (it.ptr->is_init && (*it).first == val.first)
				{
					iterator tmp = it;
					node_allocator.destroy(new_node);
					node_allocator.deallocate(new_node, 1);
					return ft::make_pair<iterator, bool>(tmp, false);
				}
				_size++;
				if (it.ptr->left == NULL)
				{
					it.ptr->left = new_node;
					new_node->parent = it.ptr;
					new_node->is_init = true;
					it--;
					
					return ft::make_pair<iterator, bool>(find(val.first), true);
				}
				else
				{
					Tnode tmp = it.ptr->left;
					while (tmp->right != NULL)
					{
						tmp = tmp->right;
					}
					tmp->right = new_node;
					new_node->parent = tmp;
					new_node->is_init = true;
					it--;
					return ft::make_pair<iterator, bool>(find(val.first), true);
				}
			}
			template< class InputIterator >
			void insert( InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0 )
			{
				while(first != last)
				{
					insert(*first);
					first++;
				}
			}

			template< class InputIterator >
			iterator insert( InputIterator here, const value_type & value )
			{
				Tnode tmp = here.ptr;
				iterator test = find(value.first);
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
							tmp = tmp->parent;
							if (tmp->parent == _end)
							tmp = tmp->parent;
						}
						_size++;
						Tnode new_node;
						new_node = node_allocator.allocate(1);
						node_allocator.construct(new_node, tree_node<value_type>());
						_allocator.construct(&new_node->pair, value);
						tmp->right = new_node;
						new_node->parent = tmp;
						new_node->is_init = true;
						while (here.ptr != tmp)
							here++;
						return (find(value.first));
					}
					else
					{
						insert(value);
						return (find(value.first));
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
						tmp = tmp->parent;
						if (tmp->parent == _end)
							tmp = tmp->parent;
					}
					_size++;
					Tnode new_node;
					new_node = node_allocator.allocate(1);
					node_allocator.construct(new_node, tree_node<value_type>());
					_allocator.construct(&new_node->pair, value);
					tmp->left = new_node;
					new_node->parent = tmp;
					new_node->is_init = true;
					while (here.ptr != tmp)
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

			iterator find( const Key& key )
			{
				iterator it;
				iterator it2 = this->end();
				for (it = begin(); it != it2; it++)
				{
					if ((*it).first == key)
						return it;
				}
				return it;
			}

			void clear_nodes( Tnode tmp )
			{
				if (tmp->left)
					clear_nodes(tmp->left);
				if (tmp->right)
					clear_nodes(tmp->right);
				node_allocator.destroy(tmp);
				node_allocator.deallocate(tmp, 1);
			}

			void clear( void )
			{
				clear_nodes(root);
				_end = node_allocator.allocate(1);
				node_allocator.construct(_end, tree_node<value_type>());
				root = node_allocator.allocate(1);
				node_allocator.construct(root, tree_node<value_type>());
				_end->is_end = true;
				root->right = this->_end;
				_end->parent = root;
				_size = 0;
			}

			void erase( iterator it )
			{
				Tnode tmp;
				tmp = it.ptr;
				if ( it.ptr == NULL)
					return;
				if (_size == 1)
				{
					clear_nodes(root);
					root = node_allocator.allocate(1);
					node_allocator.construct(root, tree_node<value_type>());
					_size = 0;
					return;
				}
				if (it.ptr->right == NULL && it.ptr->left == NULL)
				{
					if (tmp->parent->right == tmp)
						tmp->parent->right = NULL;
					if (tmp->parent->left == tmp)
						tmp->parent->left = NULL;
					node_allocator.destroy(tmp);
					node_allocator.deallocate(tmp, 1);
					_size--;
					return;
				}
				if (it.ptr->right == NULL || it.ptr->left == NULL)
				{
					if (it.ptr->right != NULL)
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
								Tnode new_root = tmp->right;
								root = new_root;
								node_allocator.destroy(tmp);
								node_allocator.deallocate(tmp, 1);
								_size--;
								return ;
							}
						}
						node_allocator.destroy(tmp);
						node_allocator.deallocate(tmp, 1);
					}
					else
					{
						if (tmp->parent != NULL)
						{
							tmp->left->parent = tmp->parent;
							if (tmp->parent->right == tmp)						
								tmp->parent->right = tmp->left;
							if (tmp->parent->left == tmp)
								tmp->parent->left = tmp->left;
						}
						else
						{
							tmp->left->parent = NULL;
							if (root->pair.first == it->first)
							{
								Tnode new_root = tmp->left;
								root = new_root;
								node_allocator.destroy(tmp);
								node_allocator.deallocate(tmp, 1);
								_size--;
								return ;
							}
						}
						node_allocator.destroy(tmp);
						node_allocator.deallocate(tmp, 1);
					}
					_size--;
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
					_allocator.destroy(&tmp->pair);
					_allocator.construct(&tmp->pair, next.ptr->pair);
					erase(next);
					return;
				}
			}

			void erase( iterator first, iterator last )
			{
				Key next;
				Key last_key;
				last_key = last->first;
				iterator tmp;
				next = first->first;
				first = find(next);
				while (first != end() && first->first != last_key)
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

			size_type erase( const Key& key )
			{
				iterator it = find(key);
				if (it != end())
				{
					erase(it);
					return (1);
				}
				return (0);
			}

			const_iterator find( const Key& key ) const
			{
				const_iterator it;
				const_iterator it2 = this->end();
				for (it = begin(); it != it2; it++)
				{
					if ((*it).first == key)
						return it;
				}
				return it;
			}

			iterator upper_bound( const Key& key )
			{
				iterator it;
				iterator it2 = this->end();
				for (it = begin(); it != it2; it++)
				{
					if (it->first != key && _comp(it->first, key) == false)
						return it;
				}
				return it;
			}

			const_iterator upper_bound( const Key& key ) const
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

			iterator lower_bound( const Key& key )
			{
				iterator it;
				iterator it2 = this->end();
				for (it = begin(); it != it2; it++)
				{
					if (it->first == key || _comp(it->first, key) == false)
						return it;
				}
				return it;
			}

			const_iterator lower_bound( const Key& key ) const
			{
				const_iterator it;
				const_iterator it2 = this->end();
				for (it = begin(); it != it2; it++)
				{
					if (it->first == key || _comp(it->first, key) == false)
						return it;
				}
				return it;
			}

			size_type count( const Key& key ) const
			{
				if (find(key) != end())
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
                return _size;
            }

            size_type max_size() const
            {
                return node_allocator.max_size();
            }

			value_compare value_comp() const
			{
				return value_compare(this->_comp);
			}

			mapped_type& operator[](const key_type& k)
			{
				 return (*((this->insert(value_type(k,mapped_type()))).first)).second;
			}


			void	swap(map& src)
			{
				Tnode				tmp_root = src.root; 
				A  					tmp_allocator = src._allocator;
				node_allocator_type	tmp_node_allocator = src.node_allocator;
				size_type 			tmp_size = src._size;
				Cmp 				tmp_comp = src._comp;
				Tnode				tmp_end  = src._end;
	
				src.root = root;
				src._allocator = _allocator;
				src.node_allocator = node_allocator;
				src._size = _size;
				src._comp  = _comp;
				src._end = _end;

				root = tmp_root;
				_allocator = tmp_allocator;
				node_allocator = tmp_node_allocator;
				_size = tmp_size;
				_comp = tmp_comp;
				_end = tmp_end;
			}

			ft::pair<iterator,iterator> equal_range( const Key& key )
			{
					iterator ret1;
					iterator ret2;
					ret1 = lower_bound(key);
					ret2 = upper_bound(key);
					return ft::make_pair(ret1, ret2);
			}

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
					const_iterator ret1;
					const_iterator ret2;
					ret1 = lower_bound(key);
					ret2 = upper_bound(key);
					return make_pair<const_iterator, const_iterator>(ret1, ret2);
			}


			
	};

	template <class Key, class T, class Compare, class Alloc >
  	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it2 = lhs.begin();
		while (it != rhs.end())
		{
			if (*it != *it2)
				return (false);
			++it2;
			++it;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
			if (!(lhs == rhs))
				return true;
			return false;
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs > rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}
#endif
