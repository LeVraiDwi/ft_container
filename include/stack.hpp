#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"
namespace ft
{
    template <class T, class Container = ft::vector<T> > 
        class stack
        {
            public:
                typedef T   value_type;
                typedef Container container_type;
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef typename container_type::size_type size_type;
            protected:
                container_type  _c;
            public:
                explicit stack (const container_type& ctnr = container_type()): _c(ctnr) {}
                ~stack() {_c.clear;}

                void    pop(){_c.pop_back();};
                void    push(const value_type& val) {_c.pushback(val);};
                bool    empty() const {return _c.empty();};
                size_type   size() const {return _c.size();};
                reference   top() {return _c.back();};
                const_reference   top() const {return _c.back();};

                stack& operator=(const stack& other)
                {
                    this->_c  = other._c;
                    return *this;
                };
                template <class DT, class Cont>
                    friend bool operator== (const stack<DT,Cont>& lhs, const stack<DT,Cont>& rhs);
                template <class DT, class Cont>
                    friend bool operator!= (const stack<DT,Cont>& lhs, const stack<DT,Cont>& rhs);
                template <class DT, class Cont>
                    friend bool operator<  (const stack<DT,Cont>& lhs, const stack<DT,Cont>& rhs);
                template <class DT, class Cont>
                    friend bool operator<= (const stack<DT,Cont>& lhs, const stack<DT,Cont>& rhs);
                template <class DT, class Cont>
                    friend bool operator>  (const stack<DT,Cont>& lhs, const stack<DT,Cont>& rhs);
                template <class DT, class Cont>
                    friend bool operator>= (const stack<DT,Cont>& lhs, const stack<DT,Cont>& rhs);
        };
    template <class T, class Container>
        bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._c == rhs._c;};
    template <class T, class Container>
        bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._c != rhs._c;};
    template <class T, class Container>
        bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._c < rhs._c;};
    template <class T, class Container>
        bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._c <= rhs._c;};
    template <class T, class Container>
        bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._c > rhs._c;};
    template <class T, class Container>
        bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._c >= rhs._c;};
}
#endif