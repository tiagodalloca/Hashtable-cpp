#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Arvore.h"
#include "Hashtable.h"

Hashtable::Hashtable(){
}

Hashtable::Hashtable(	unsigned int initial_length, 
							unsigned int initial_growth_rate, 
							unsigned int initial_max_occupation_rate, 
							unsigned int initial_max_tree_size, 
							unsigned int initial_max_exceeded_trees){
	length = initial_length;
	growth_rate = initial_growth_rate;
	max_occupation_rate = initial_max_occupation_rate;
	max_tree_size = initial_max_tree_size;
	max_exceeded_trees = initial_max_exceeded_trees;
	the_array = (Arvore<IHashble*>*)malloc(length * sizeof(Arvore<IHashble*>));
	count = 0;
}

Hashtable::~Hashtable(){

}


void Hashtable::insert(IHashble* o) {
	unsigned int hash = o->hashcode();
	unsigned int place_to_go = hash % length;
	the_array[place_to_go].insert(o);
	count++;
}


IHashble* Hashtable::get(IHashble* o){
	unsigned int hash = o->hashcode();
	unsigned int place_to_get = hash % length;
	return the_array[place_to_get].get(o);
}


void Hashtable::remove(IHashble* o){
	unsigned int hash = o->hashcode();
	unsigned int place_to_remove = hash % length;
  Arvore<IHashble*> tree = the_array[place_to_remove];
	if (tree.getCount() > 0)
		tree.remove(o);
}

