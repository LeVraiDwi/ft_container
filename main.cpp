#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>
#include <ctime>
#include <map>
#include <stack>
#include <vector>

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

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

using namespace ft;

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
                r += std::to_string((*it).first);
                r += ":";
                r += std::to_string((*it).second);
                r += " ";
        }
        std::cout << r << std::endl;
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

int main(/*int argc, char** argv*/) {

	vector_basiques();
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
