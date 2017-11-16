#include "Hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Hashtable.h"
#include "Node.h"

class stringao : public IHashble, public std::string{
	public:
		stringao(char* cs) : string(cs){

		}
		
		unsigned int hashcode(){
			unsigned int hash = 13;
			for(int i = 0; i < length(); i++){
				hash *= 13 + 13*(this->operator [](i));
			}
			
			return hash;
		}
};

int main(){
	Hashtable* h = new Hashtable(
					10, //unsigned int initial_length,
					10, //unsigned int initial_growth_rate,
					30, //unsigned int initial_max_occupation_rate,
					3,  //unsigned int initial_max_tree_size,
					10  //unsigned int initial_max_exceeded_trees
					);
	h->
	insert(
	new Node<std::string>(
		new std::string("1234"), 
		new stringao("asdf")));
	h->insert
	(new Node<std::string>(new std::string("10"), new stringao("10000")));
	
	std::string str = *(((Node<std::string>*)
											h->get(
												new stringao("asdf")))
										->info);
	
	cout << str;
	
  return 0;
}

