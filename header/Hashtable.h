#ifndef HASHTABLE
#define HASHTABLE

#include "Arvore.h"
#include "IHashble.h"

using namespace std;

class Hashtable{

 public:
	 Hashtable();
	 ~Hashtable();
	 
	 IHashble* insert();
	 IHashble* get();
	 bool remove(IHashble*);

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
