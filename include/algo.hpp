#ifndef ALGO_HPP
# define ALGO_HPP

namespace ft
{
    //is_integral//
    template <class T, T v>
        struct integral_constant
        {
            static const T value = v;
            typedef T value_type;
        };
        typedef struct integral_constant<bool, true> true_type;
        typedef struct integral_constant<bool, false> false_type;
        
    template <class T>
        struct is_integral: public false_type {};
    template <>
        struct is_integral<char>: public true_type {};
    template <>
        struct is_integral<wchar_t>: public true_type {};
    template <>
        struct is_integral<signed char>: public true_type {};
    template <>
        struct is_integral<short int>: public true_type {};
    template <>
        struct is_integral<int>: public true_type {};
    template <>
        struct is_integral<long int>: public true_type {};
    template <>
        struct is_integral<long long int>: public true_type {};
    template <>
        struct is_integral<unsigned char>: public true_type {};
    template <>
        struct is_integral<unsigned short int>: public true_type {};
    template <>
        struct is_integral<unsigned int>: public true_type {};
    template <>
        struct is_integral<unsigned long int>: public true_type {};
    template <>
        struct is_integral<unsigned long long int>: public true_type {};
    //enable_if//
    template<bool Cond, class T = void> struct enable_if {};

    template<class T> struct enable_if<true, T> { typedef T type; };
    //equal//
    template <class InputIterator1, class InputIterator2>
        bool equal (InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2)
        {
            for (InputIterator1 it = first1; it != last1; it++)
            {
                if (*it != first2)
                    return false;
                first2++;
            }
            return true;
        };
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
        bool equal (InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, BinaryPredicate p)
        {
            while (first1 != last1)
            {
                if (!p(first1, first2))
                    return false;
                first1++;
                first2++;
            }
            return true;
        };
    //lexicographical_compare//
    template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1)
                    return false;
                else if (*first1 < *first2)
                    return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        };
    template <class InputIterator1, class InputIterator2, class Compare>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, InputIterator2 last2, Compare comp)
        {
            while (first1!=last1)
            {
                if (first2 == last2 || comp(*first2, *first1))
                    return false;
                else if (comp(first1, first2))
                    return true;
                ++first1; ++first2;
            }
            return (first2!=last2);
        };
}
#endif