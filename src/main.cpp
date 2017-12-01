#include "Hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Hashtable.h"
#include "Node.h"

class stringao : public IHashble, public std::string {
public:
	stringao(char* cs) : string(cs) {
	}

	unsigned int hashcode() {
		unsigned int hash = 13;
		for (int i = 0; i < length(); i++) {
			hash *= 13 + 13 * (this->operator [](i));
		}

		return hash;
	}

};

int main() {
	Hashtable* h = new Hashtable(
		10, //unsigned int initial_length,
		10, //unsigned int initial_growth_rate,
		0.5, //float initial_max_occupation_rate,
		3,  //unsigned int initial_max_tree_size,
		10  //unsigned int initial_max_exceeded_trees
	);
	h->
		insert(
			new Node<std::string>(
				new std::string("a"),
				new stringao("0")));
	h->insert
	(new Node<std::string>(new std::string("b"), new stringao("1")));

	h->insert
	(new Node<std::string>(new std::string("c"), new stringao("2")));

	h->insert
	(new Node<std::string>(new std::string("d"), new stringao("3")));

	h->insert
	(new Node<std::string>(new std::string("e"), new stringao("4")));

	h->insert
	(new Node<std::string>(new std::string("f"), new stringao("5")));

	std::string str = *(((Node<std::string>*)
		h->get(
			new stringao("0")))
		->info);

	cout << str << '\n';

	std::string str2 = *(((Node<std::string>*)
		h->get(
			new stringao("1")))
		->info);

	cout << str2 << '\n';

	h->remove(new stringao("0"));

	Node<std::string>* n = ((Node<std::string>*)
		h->get(
			new stringao("0")));

	if (n != NULL)
		cout << (n->info);

	else
		cout << "\n\nNao dah pra excluir algo que nao existe";

	h->insert
	(new Node<std::string>(new std::string("300"), new stringao("300000")));
	std::string str3 = *(((Node<std::string>*)
		h->get(
			new stringao("300000")))
		->info);

	cout << '\n' << str3 << '\n';

	cout << '\n' << h->count;

	cout << "\n\n\n\n\n\n\n" + h->toString();

	cin >> str;


	return 0;
}