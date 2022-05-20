#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"
# include "algo.hpp"

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
                container_type  c;
            public:
                explicit stack (const container_type& ctnr = container_type()): c(ctnr) {}
                ~stack() {c.clear();}

                void    pop(){c.pop_back();};
                void    push(const value_type& val) {c.push_back(val);};
                bool    empty() const {return c.empty();};
                size_type   size() const {return c.size();};
                reference   top() {return c.back();};
                const_reference   top() const {return c.back();};

                stack& operator=(const stack& other)
                {
                    this->c  = other.c;
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
        bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.c == rhs.c;};
    template <class T, class Container>
        bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.c != rhs.c;};
    template <class T, class Container>
        bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.c < rhs.c;};
    template <class T, class Container>
        bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.c <= rhs.c;};
    template <class T, class Container>
        bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.c > rhs.c;};
    template <class T, class Container>
        bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs.c >= rhs.c;};
}
#endif