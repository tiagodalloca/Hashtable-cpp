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
}

Hashtable::~Hashtable()
{

}


void Hashtable::insert() {
}


IHashble* Hashtable::get(){
	return NULL;
}


char Hashtable::remove(IHashble* o){
	return 'c';
}

