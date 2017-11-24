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
	the_array = (Arvore**)malloc(length * sizeof(Arvore));
	count = 0;
}

Hashtable::~Hashtable(){

}


void Hashtable::insert(IHashble* o) {
	unsigned int hash = o->hashcode();
	unsigned int place_to_go = hash % length;
	
	if (the_array[place_to_go] == NULL)
		the_array[place_to_go] = new Arvore();
	
	the_array[place_to_go]->insert(o);
	count++;
}


IHashble* Hashtable::get(IHashble* o){
	unsigned int hash = o->hashcode();
	unsigned int place_to_get = hash % length;
	
	if (the_array[place_to_get] == NULL)
		return NULL;
	
	return the_array[place_to_get]->get(o);
}


void Hashtable::remove(IHashble* o){
	unsigned int hash = o->hashcode();
	unsigned int place_to_remove = hash % length;
  Arvore* tree = the_array[place_to_remove];
	if (tree != NULL){
		tree->remove(o);
		if (tree->getCount() == 0){
			//delete[]tree;
			the_array[place_to_remove] = NULL;
		}
	}
}

