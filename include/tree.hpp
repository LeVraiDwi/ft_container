#ifndef TREE_HPP
# define TREE_HPP

namespace ft
{
    template <class T>
        class Node
        {
            public:
                typedef T   value_type;
                typedef Node*   node_ptr;

                value_type  pair;
                Node        *right;
                Node        *left;
                Node        *parent;
                bool        is_init;
                bool        is_end;

                Node(): pair(NULL), right(NULL), left(NULL), parent(NULL), is_init(false), is_end(false) {}
                Node(const value_type &value): pair(value), right(NULL), left(NULL), parent(NULL), is_init(false), is_end(true) {}
                Node(Node& other): pair(other.value), right(other.right), left(other.left), parent(other.parent), is_init(other.is_init), is_end(other.is_end) {}

                Node& operator=(const Node& other)
                {
                    pair = other.pair;
                    parent = other.parent;
                    right = other.right;
                    left = other.left;
                    is_init = other.is_init;
                    is_end = other.is_end;
                    return *this;
                }
        };
}
#endif