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

                value_type  value;
                Node        *right;
                Node        *left;
                Node        *parent;
                bool        is_left;
                bool        color;

                Node(): value(NULL), right(NULL), left(NULL), parent(NULL), is_left(false), color(false);
                Node(const value_type &value): value(value), right(NULL), left(NULL), parent(NULL), is_left(false), color(true);
                Node(Node& other): value(other.value), right(other.right), left(other.left), parent(other.parent), is_left(other.is_left), color(other.color);

                Node& operator=(const Node& other)
                {
                    value = other.value;
                    parent = other.parent;
                    right = other.right;
                    left = other.left;
                    is_left = other.is_left;
                    color = other.color;
                    return *this;
                }

                node_ptr    get_aunt()
                {
                    if (parent == NULL)
                        return NULL;
                    else if (parent->is_left)
                    {
                        return parent->parent->right);
                    }
                    else
                        return parent->parent->left;
                }
        };
}
#endif