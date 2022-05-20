#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP
# include "iterator.hpp"
namespace ft
{
    template <typename _Iter>
	class reverseIterator
	{
	private:
		_Iter														_t;

	protected:
		_Iter 														_current;
	public:
		typedef _Iter                                            	iterator_type;
		typedef typename iterator_traits<_Iter>::difference_type	difference_type;
		typedef typename iterator_traits<_Iter>::reference       	reference;
		typedef typename iterator_traits<_Iter>::pointer        	pointer;
		typedef typename iterator_traits<_Iter>::iterator_category  category;
	
		//void
		reverseIterator() : _t(), _current() {}
		
		//normal construct
		explicit reverseIterator(_Iter __x) : _t(__x), _current(__x) {}
		template <class T>

		//copy	
		reverseIterator(const reverseIterator<T>& __u) : _t(__u.base()), _current(__u.base()) {}
		template <class T>
			
			reverseIterator& operator=(const reverseIterator<T>& __u)
				{ _t = _current = __u.base(); return *this; }
		
		_Iter base() const {return _current;}
		
		reference operator*() const {_Iter _tmp = _current; return *--_tmp;}
		reverseIterator  operator+( difference_type x) const
		{
			return reverseIterator(_current - x);
		}
		
		reverseIterator  operator-( difference_type x) const
		{
			return reverseIterator(_current + x);
		}
		
		reference operator[](difference_type index)
		{
			return *(*this + index);
		}

		pointer operator->() const
		{
			_Iter _tmp = _current; 
			return std::__addressof(*--_tmp);
		}

		reverseIterator operator++(int)
		{
			reverseIterator tmp(*this);
			this->operator++();
			return (tmp);
		}

		reverseIterator& operator++()
		{
			_current--;
			return *this;
		}
		reverseIterator& operator--()
		{
			_current++;
			return *this;
		}

		reverseIterator operator--(int)
		{
			reverseIterator tmp(*this);
			this->operator--();
			return tmp;
		}

		reverseIterator&  operator+=( difference_type x)
		{
			_current -= x;
			return *this;
		}

		reverseIterator&  operator-=( difference_type x)
		{
			_current += x;
			return *this;
		}
	};

	
	/**** NON MEMBER FUNCTION ****/
	template <class Iterator1, class Iterator2>
    typename reverseIterator<Iterator1>::difference_type operator-(const reverseIterator<Iterator1> & lhs, const reverseIterator<Iterator2>& rhs)
    {
        return rhs.base() - lhs.base();
    }

	template <class Iterator>
	reverseIterator<Iterator> operator+ (typename reverseIterator<Iterator>::difference_type n, const reverseIterator<Iterator>& rev_it)
    {
        return (rev_it + n);
    }
	
	template <class Iterator1, class Iterator2>
	bool operator!=(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator<(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator==(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    }
}
#endif