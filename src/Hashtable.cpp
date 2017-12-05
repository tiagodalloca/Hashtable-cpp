#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Arvore.h"
#include "Hashtable.h"
#include "Node.h"

Hashtable::Hashtable() {
}

Hashtable::Hashtable(unsigned int initial_length,
	unsigned int initial_growth_rate,
	float initial_max_occupation_rate,
	unsigned int initial_max_tree_size,
	unsigned int initial_max_exceeded_trees) {
	length = initial_length;
	growth_rate = initial_growth_rate;
	max_occupation_rate = initial_max_occupation_rate;
	max_tree_size = initial_max_tree_size;
	max_exceeded_trees = initial_max_exceeded_trees;
	the_array = (Arvore**)malloc(length * sizeof(Arvore));
	count = 0;

	for (int i = 0; i < length; i++)
	{
		the_array[i] = NULL;
	}
}

Hashtable::~Hashtable() {

}

bool Hashtable::needToGrow()
{
	if (count != 0)
	{
		if ((float)count / length >= max_occupation_rate)
			return true;

		int exceededTrees = 0;
		for (int i = 0; i < length; i++)
			if (the_array[i] != NULL)
				if (the_array[i]->getCount() > max_tree_size)
					exceededTrees++;

		if (exceededTrees >= max_exceeded_trees)
			return true;
	}


	return false;
}

void Hashtable::grow()
{
	Arvore** oldArray = the_array;
	int oldLength = length;
	length *= growth_rate;
	the_array = (Arvore**)malloc(length * sizeof(Arvore));
	count = 0;
	for (int i = 0; i < length; i++)
	{
		the_array[i] = NULL;
	}

	for (int i = 0; i < oldLength; i++)
		if (oldArray[i] != NULL)
			for (int i2 = 0; i2 < oldArray[i]->getCount(); i2++)
			{
				IHashble** atuais = oldArray[i]->getElements(oldLength);
				for (int i3 = 0; i3 < oldArray[i]->getInd(); i3++)
				{
					this->insert(atuais[i3]);
				}
			}


	for (int n = 0; n < oldLength; n++)
		delete oldArray[n];
}


void Hashtable::insert(IHashble* o) {
	if (needToGrow())
	{
		grow();
	}
	unsigned int hash = o->hashcode();
	unsigned int place_to_go = hash % length;

	if (the_array[place_to_go] == NULL)
		the_array[place_to_go] = new Arvore();
	else
	{
		IHashble** ih = the_array[place_to_go]->getElements(length);
		for (int i3 = 0; i3 < the_array[place_to_go]->getInd(); i3++)
		{			
			Node<std::string>* n1 = ((Node<std::string>*)
				ih[i3]);
			Node<std::string>* n2 = ((Node<std::string>*)
				o);

			if (n1->key == n2->key)
			{
				cout << "\nRepeated key. Throwing exception.\n";
				throw new exception("repeated key");
			}
		}
	}

	the_array[place_to_go]->insert(o);
	count++;
}

std::string Hashtable::toString() const {
	std::string aux = "[\n\n";
	for (int i = 0; i < length; i++)
	{
		if (the_array[i] != NULL)
		{
			aux += "pos" + std::to_string(i) + ":";
			aux += the_array[i]->toString() + "\n";
		}
	}
	aux += "\n]";
	return aux;
}

IHashble* Hashtable::get(IHashble* o) {
	unsigned int hash = o->hashcode();
	unsigned int place_to_get = hash % length;

	if (the_array[place_to_get] == NULL)
		return NULL;

	return the_array[place_to_get]->get(o);
}


void Hashtable::remove(IHashble* o) {
	unsigned int hash = o->hashcode();
	unsigned int place_to_remove = hash % length;
	Arvore* tree = the_array[place_to_remove];
	if (tree != NULL) {
		tree->remove(o);
		count--;
		if (tree->getCount() == 0) {
			//delete[]tree;
			the_array[place_to_remove] = NULL;
		}
	}
}



