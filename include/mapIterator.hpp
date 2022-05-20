#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP
# include "iterator.hpp"
# include "tree.hpp"

namespace ft
{
    template <class T>
    class const_map_iterator;
	
	template <class _Iter>
    class map_reverse_iterator;

	template <typename _T>
	class map_iterator
	{

	public:

		typedef std::ptrdiff_t					difference_type;
		typedef _T 								value_type;
		typedef _T* 							pointer;
		typedef _T* 							rpointer;
		typedef tree_node<_T>* 					npointer;
		typedef _T& 							reference;
		typedef _T& 							rreference;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef tree_node<_T>*					Tnode;  
		npointer                       			 ptr;
	
		//FUNCTIONS: CONSTRUCTORS
		map_iterator() : ptr(NULL) {}
		
		//normal construct
		explicit map_iterator(Tnode node) : ptr(node) {}
		
		//copy
		map_iterator(const map_iterator& copy) : ptr(copy.ptr) {}
		
		map_iterator& operator=(const map_iterator& copy)
		{ 
			ptr = copy.ptr; 
			return *this; 
		}
		
		virtual ~map_iterator(void) { return; }
		
		reference operator*() const
		{
			return this->ptr->pair;
		}

		pointer operator->() const
		{
			return &(this->ptr->pair);
		}

		map_iterator& operator++()
		{
			npointer next;

			if (ptr->right == NULL)
			{
				next = ptr;
				while (next->parent && next == next->parent->right)
					next = next->parent;
				next = next->parent;
				ptr = next;
				return (*this);
			}
			next = ptr->right;
			while (next->left)
				next = next->left;
			ptr = next;
			return (*this);
		}
		
		map_iterator operator++(int)
		{
			
			map_iterator tmp;
			
			tmp.ptr = this->ptr;
			this->operator++();
			return (tmp);
		}

		map_iterator& operator--()
		{
			Tnode tmp = ptr;
			Tnode tmp2 = NULL;
			
			if (!tmp)
				return *this;
			if (tmp->is_end == true)
			{
				if (tmp->left == NULL)
				{
					ptr = ptr->parent;
					return (*this);
				}
				tmp = tmp->left;
				while (tmp->right != NULL)
					tmp = tmp->right;
				ptr = tmp;
				return (*this);	
			}
			if (tmp->left && tmp->left != NULL)
			{
				
				tmp = tmp->left;
				while (tmp->right != NULL)
					tmp = tmp->right;
				this->ptr = tmp;
				return (*this);
			}
			else
			{
				if (tmp->parent == NULL)
				{
					ptr = NULL;
					return (*this);
				}
				tmp2 = tmp->parent;
				if (tmp2->right != NULL && tmp2->right == tmp)
				{
					ptr = tmp2;
					return (*this);
				}
				else
				{
					if (tmp->parent && tmp == tmp->parent->left)
					{		
						while (tmp->parent && tmp == tmp->parent->left)
					{
						if (tmp->parent == NULL)
						{
							ptr = NULL;
							return (*this);
						}
						tmp = tmp->parent;
					}
					tmp = tmp->parent;
					ptr = tmp;
					return (*this);
					}
				}
				ptr = NULL;
				return (*this);
			}
		}

		map_iterator operator--(int)
		{
			
			map_iterator tmp(*this);
			
			this->operator--();
			return tmp;
		}
		
		bool operator==(const map_iterator& rhs) const
		{
			return this->ptr == rhs.ptr;
		}
			
			
		bool operator!=(const map_iterator& rhs) const
		{
			return this->ptr != rhs.ptr;
		}
	};

	template <class _T>
	class const_map_iterator
	{

	public:
		typedef std::ptrdiff_t 					difference_type;
		typedef _T						value_type;
		typedef tree_node<_T>* 					npointer;
		typedef const value_type				&reference;
		typedef const value_type				*pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef tree_node<_T>*					Tnode;  
		npointer                       			 ptr;
	
	public:
		//FUNCTIONS: CONSTRUCTORS
		const_map_iterator() : ptr(NULL) {}
		
		//normal construct
		explicit const_map_iterator(Tnode node) : ptr(node) {}
		
		//copy
		template <class T>
		const_map_iterator(const map_iterator<T>& copy) : ptr(copy.ptr) {}
		
		template <class T>
		const_map_iterator& operator=(const map_iterator<T>& copy)
		{ 
			this->ptr = copy.ptr; 
			return *this; 
		}
		
		~const_map_iterator(void) { return; }
		
		reference operator*() const
		{
			return (this->ptr->pair);
		}
		
		pointer operator->(void) const
		{
			return &(this->ptr->pair);
		}
	
		const_map_iterator& operator++()
		{
			npointer next;
			if (ptr->right == NULL)
			{
				next = ptr;
				while (next->parent && next == next->parent->right)
					next = next->parent;
				next = next->parent;
				ptr = next;
				return (*this);
			}
			next = ptr->right;
			while (next->left)
				next = next->left;
			ptr = next;
			return (*this);
		}
		
		const_map_iterator operator++(int)
		{
			const_map_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		const_map_iterator& operator--()
		{
			Tnode tmp = ptr;
			Tnode tmp2 = NULL;

			if (!tmp)
				return *this;
			if (tmp->is_end == true)
			{
				if (tmp->left == NULL)
				{
					ptr = ptr->parent;
					return (*this);
				}
				tmp = tmp->left;
				while (tmp->right != NULL)
					tmp = tmp->right;
				ptr = tmp;
				return (*this);	
			}	
			if (tmp->left && tmp->left != NULL)
			{
				tmp = tmp->left;
				while (tmp->right != NULL)
					tmp = tmp->right;
				this->ptr = tmp;
				return (*this);
			}
			else
			{
				if (tmp->parent == NULL)
				{
					ptr = NULL;
					return (*this);
				}
				tmp2 = tmp->parent;
				if (tmp2->right == tmp)
				{
					ptr = tmp2;
					return (*this);
				}
				else
				{
					if (tmp->parent && tmp == tmp->parent->left)
					{
					while (tmp->parent && tmp == tmp->parent->left)
					{
						if (tmp->parent == NULL)
						{
							ptr = NULL;
							return (*this);
						}
						tmp = tmp->parent;
					}
					tmp = tmp->parent;
					ptr = tmp;
					return (*this);
					}
				}
				ptr = NULL;
				return (*this);
			}
		}
		const_map_iterator operator--(int)
		{
			const_map_iterator tmp = (*this);
			--(*this);
			return tmp;
		}
		
		bool operator==(const const_map_iterator& rhs) const
		{
			return this->ptr == rhs.ptr;
		}			
			
		bool operator!=(const const_map_iterator& rhs) const
		{
			return this->ptr != rhs.ptr;
		}
	};
} // namespace ft

#endif