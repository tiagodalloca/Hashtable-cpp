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
	 Arvore<IHashble*>* the_array;
};

#endif //HASHTABLE
