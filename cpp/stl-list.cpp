// STL C++ List Example
// Derived from http://www.cprogramming.com/tutorial/stl/stllist.html

#include <iostream>
#include <list>

int main ()
{
	std::list<int> int_list;
	int_list.push_back(1);
	int_list.push_back(1);
	int_list.push_back(8);
	int_list.push_back(9);
	int_list.push_back(7);
	int_list.push_back(8);
	int_list.push_back(2);
	int_list.push_back(3);
	int_list.push_back(3);
	
	int_list.sort(); // Sort in ascending order
	int_list.reverse(); // Reverse the list
	int_list.unique(); // Remove duplicates
	
	for(std::list<int>::iterator list_iter = int_list.begin(); list_iter != int_list.end(); list_iter++)
	{
	    std::cout<<*list_iter<<std::endl;
	}

	std::cout<<"Size of int_list:"<<int_list.size()<<std::endl;
	int_list.pop_back();
	std::cout<<"Size of int_list after popping:"<<int_list.size()<<std::endl;
	return 0;
}