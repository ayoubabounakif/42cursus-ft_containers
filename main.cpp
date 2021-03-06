/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:23:28 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/15 20:25:53 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "containers/vector.hpp"
// # include "containers/stack.hpp"
// # include "RBT/rbt_v3.hpp"
// # include "RBT/rbt_v3.hpp"
# include "containers/map.hpp"
# include "AVL/avl.hpp"

#include <iostream>
#include <map>

int main ()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('x');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}


// int main ()
// {
//   ft::map<char,int> mymap;
//   ft::map<char,int>::iterator it;

//   // insert some values:
//   mymap['a']=10;
//   mymap['b']=20;
//   mymap['c']=30;
//   mymap['d']=40;
//   mymap['e']=50;
//   mymap['f']=60;

// //   it=mymap.find('b');
// //   mymap.erase (it);                   // erasing by iterator

// //   mymap.erase ('c');                  // erasing by key


//   it=mymap.find ('e');
//   mymap.erase ( it, mymap.end() );    // erasing by range

//   // show content:
//   for (it = mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';

//   return 0;
// }

// int main( void ) 
// {
//     ft::AVL<ft::pair<const int, int> >	avl;
	
// 	std::vector<int> vec;
// 	std::vector<int>::iterator	it;
	
// 	srand(time(nullptr));
// 	for (int i = 0; i < 20; i++) {
// 		vec.push_back(rand() % 100);
// 		// std::cout << vec[i] << std::endl;
// 		avl.insert(ft::make_pair(i, vec[i]));
// 	}
	
// 	ft::AVL<ft::pair<const int, int> >::iterator	avlit = avl.begin();
// 	for (; avlit != avl.end(); ++avlit)
// 		std::cout << avlit->first << std::endl;
	
// 	// avl.print();
// 	// ft::map<int, std::string> mymap;
// 	// mymap[1] = "Hi";
//     // mymap[2] = "This";
//     // mymap[3] = "is";
//     // mymap[4] = "GeeksForGeeks";
     
//     // using operator[] to print string
//     // mapped to integer 4
//     // std::cout << mymap[4];

	
// }

/* #if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

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

int main( int argc, char** argv ) {
	if (argc != 2)
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
	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
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
	return (EXIT_SUCCESS);
} */