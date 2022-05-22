#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>
#include <ctime>
#include <map>
#include <stack>
#include <vector>
#include <list>

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <stdlib.h>

using namespace std;

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

template <class T>
void    printVec(vector<T> v){
        std::string r = "";
        for (typename vector<T>::size_type i = 0; i < v.size(); i++){
                r += (i == 0 ? "" : " ");
                r += v[i];
        }
        std::cout << r << "; s" << v.size() << "; c" << v.capacity() << std::endl;
}

template <class K, class V>
void    printMap(map<K, V> m){
        std::string r = "";
        for (typename map<K,V>::iterator it = m.begin(); it != m.end(); it++){
                std::cout << (*it).first;
                std::cout << ":";
                std::cout << (*it).second;
                std::cout << " ";
        }
        std::cout << std::endl;
}


void    vector_basiques(){
        #define VECTYPE char
        //CONSTRUCTORS
		std::cout << "construc" << std::endl;
        vector<VECTYPE> v1;
        vector<VECTYPE> v2(4, 97);
        v1 = v2;
        vector<VECTYPE> v3(v1.begin(),v1.end());
        vector<VECTYPE> v4(v3);
        printVec(v4);
        //ELEMENT ACCESS
		std::cout << "elem" << std::endl;
        v4[1] = 65 + 1;
		printVec(v4);
        v4.at(2) = 65 + 2;
		printVec(v4);
        v4.front() = 65 + 0;
		printVec(v4);
        v4.back() = 65 + 3;
        //ITERATORS
        printVec(v4);
        for (vector<VECTYPE>::reverse_iterator it = v4.rbegin(); it != v4.rend(); it++)
                *it += 2;
        //CAPACITY
        std::cout << "capacity" << std::endl;
        printVec(v4);
        std::cout << v4.max_size() << std::endl;
        v4.resize(6, 70);
        std::cout << v4.capacity() << std::endl;
        std::cout << v4.empty() << std::endl;
        v4.reserve(9);
        std::cout << v4.capacity() << std::endl;
        v4.push_back(72);
        v4.push_back(72);
        v4.push_back(72);
        v4.push_back(72);
        std::cout << v4.capacity() << std::endl;
        //MODIFIERS
        std::cout << "modifier" << std::endl;
        v4.clear();
        v3.clear();
        std::cout << v3.empty() << std::endl;
        for (vector<VECTYPE>::size_type i = 0; i < 7; i++){
                v4.insert(v4.begin() + i, 'a' + i);
                v3.insert(v3.begin() + i, 'A' + i);
        }
		std::cout << "lalal" << std::endl;
		printVec(v3);
		std::cout << "modifier" << std::endl;
        v3.insert(v3.begin()+3, 2, 'X');
		std::cout << "modifier" << std::endl;
		printVec(v3);
		printVec(v4);
        v3.insert(v3.begin()+4, v4.begin(), v4.end());
		printVec(v3);
		std::cout << "modifier" << std::endl;
        printVec(v3);
        v3.swap(v4);
		std::cout << "modifier" << std::endl;
        printVec(v4);
        std::cout << *(v4.erase(v4.begin() + 4)) << std::endl;
        std::cout << *(v4.erase(v4.end() - 4, v4.end() - 2)) << std::endl;
        printVec(v4);
        //SURCHARGE
        std::cout << "surcharge" << std::endl;
        std::cout << (v3 == v4) << (v3 != v4) << (v3 <= v4) << (v3 < v4) << (v3 >= v4) << (v3 > v4) << std::endl;
}

void    map_basiques(){
        #define K int
        #define M int
//CONSTRUCTORS
	std::cout << "const" << std::endl;
        map<K,M> m;
        m[-34] = 1;
        m[0345] = 12;
        m[654] = -24;
        m[234] = 53;
        map<K,M> n(m);
        map<K,M> o = n;
//ITERATORS
	std::cout << "itera" << std::endl;
        for (map<K,M>::iterator it = m.begin(); it != m.end(); it++)
                it->second = 0;
	std::cout << "itera" << std::endl;
        for (map<K,M>::const_iterator it = m.begin(); it != m.end(); it++)
                std::cout << it->first << ":" << it->second << " ";
        std::cout << std::endl;
		std::cout << "itera" << std::endl;
        int i = 9;
        for (map<K,M>::reverse_iterator it = m.rbegin(); it != m.rend(); it++)
                it->second = i++;
	std::cout << "itera" << std::endl;
        for (map<K,M>::const_reverse_iterator it = m.rbegin(); it != m.rend(); it++)
                std::cout << it->first << ":" << it->second << " ";
    std::cout << std::endl;
//CAPACITY
std::cout << "capa" << std::endl;
        std::cout << m.empty() << m.size() << m.max_size() << std::endl;
//ELEMENT_ACCESS
std::cout << "elemen" << std::endl;
        printMap(m);
        std::cout << m[14];
        printMap(m);
        std::cout << m[229] << std::endl;
//MODIFIERS
std::cout << "modif" << std::endl;
        m.insert(make_pair(35,54));
        printMap(m);
        map<K,M>::iterator hh = m.begin();
        hh++;
        m.insert(hh, make_pair(-200,-200));
        m.insert(n.begin(), n.end());
        for (int i = 0; i < 4; i++)
                n.insert(make_pair(i, i));
        m.insert(n.begin(), n.end());
        printMap(m);
        m.erase(m.begin());
        m.erase(1);
        printMap(m);
        m.clear();
        for (int i = 0; i < 12; i++){
                m.insert(make_pair(i*5,i*5));
                n.insert(make_pair(i,i));
        }
        m.swap(n);
        printMap(m);
        printMap(n);
//OPERATIONS
std::cout << "opera" << std::endl;
        std::cout << m.find(5)->second << m.count(5) << m.count(43) << std::endl;
        std::cout << m.lower_bound(30)->second << m.upper_bound(30)->second << std::endl;
}

void    map_en_details(){
        #define AK int
        #define AM char
        map<AK,AM>m;
        for (int i = 0; i < 7; i++){
                m[i*5] = 'a' + i;
        }
        m.insert(make_pair(15, 'z'));
        m.insert(make_pair(25, 'y'));
        m[10] = 'G';
        m.insert(make_pair(-10, 'z'));
        printMap(m);
        map<AK,AM>::reverse_iterator it = m.rbegin();
        it++;
        it++;
        std::cout << m.size() << std::endl;
        std::cout << it->first << std::endl;
        m.insert(make_pair(3, '$'));
        printMap(m);
        std::cout << it->first << std::endl;
        // std::cout << "HERE";
        m.erase('3');
        printMap(m);
        std::cout << it->first << std::endl;
        map<AK,AM> n;
        for (int i = 0; i < 4; i++){
                n[i*3] = 'A' + i;
        }
        map<AK,AM>::iterator it2 = n.begin();
        n.swap(m);
        std::cout << it2->first << std::endl;
        printMap(m);
        printMap(n);
}

void	stack_basiques(){
	//member_functions
	stack<char> s1;
	std::cout << s1.size() << std::endl;
	stack<char> d;
	d.push('d');
	d.push('q');
	stack<char> s2 = d;
	s2.push('!');
	for (;!s2.empty(); s2.pop())
		std::cout << s2.top() << std::endl;
	//non_member functions oerloads
	s1.push(';');
	std::cout << (s1 == s2) << std::endl;
	std::cout << (s1 != s2) << std::endl;
	std::cout << (s1 < s2) << std::endl;
	std::cout << (s1 <= s2) << std::endl;
	std::cout << (s1 > s2) << std::endl;
	std::cout << (s1 >= s2) << std::endl;
}

void	stack_en_details(){
	#define S int
	stack<S, std::deque<S> > a;
	stack<S, std::list<S> > b;
	for (int i = 0; i < 5; i++){
		a.push(i*1);
		b.push(i*2);
	}
	for (int i = 0; i < 5; i++){
		std::cout << a.top();
		std::cout << b.top();
		std::cout << std::endl;
		a.pop();
		b.pop();
	}
}

void	vector_en_details(){
	#define ATYPE char
	vector<ATYPE> a;
	for (int i = 0 ; i < 6; i ++)
		a.push_back(i + 'a');
	vector<ATYPE>::iterator it = a.begin() + 1;
	vector<ATYPE>::const_iterator cit = a.begin() + 2;
	std::cout << (it != cit) << std::endl;
	std::cout << (it > cit) << std::endl;
	vector<ATYPE> b;
	for (int i = 0 ; i < 9; i ++)
		b.push_back(i + 'A');
	
	vector<ATYPE>::reference r = a.at(2);
	a.swap(b);
	it++;
	*it = 'Z';
	r = 'X';
	printVec(a);
	printVec(b);
}

int main(/*int argc, char** argv*/) {

	map_en_details();
	map_basiques();
	vector_basiques();
        stack_en_details();
        stack_basiques();
        vector_en_details();
	/*if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);*/
}
