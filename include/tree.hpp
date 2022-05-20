#ifndef TREE_HPP
# define TREE_HPP
# define BLACK 0
# define RED 1

namespace ft
{
    template <class value_type>
    struct tree_node
    {
        public:

        value_type  pair;
        tree_node   *right;
        tree_node   *left;
        tree_node   *parent;
        bool        is_init;
        bool        is_end;

        tree_node() : pair(), right(NULL), left(NULL), parent(NULL), is_init(false), is_end(false) {}
    };
}
#endif