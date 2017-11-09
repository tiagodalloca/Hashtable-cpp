#ifndef HASHTABLE
#define HASHTABLE

#include "Arvore.h"
#include "IHashble.h"

using namespace std;

class Hashtable{

 public:
	 Hashtable();
	 Hashtable(	unsigned int initial_length, 
							unsigned int growth_rate, 
							unsigned int occupation_rate, 
							unsigned int conflict_tree_max_size, 
							unsigned int max_maximized_tree_count);
	 ~Hashtable();
	 
	 void insert();
	 IHashble* get();
	 char remove(IHashble* o);

 private:
	 unsigned int length;
	 unsigned int count;
	 
	 unsigned int growth_rate;
	 unsigned int occupation_rate;
	 unsigned int conflict_tree_max_size;
	 unsigned int max_maximized_tree_count;
	 
	 Arvore<IHashble*>* the_array;
};

#endif //HASHTABLE
