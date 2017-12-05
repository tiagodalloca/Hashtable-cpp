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
	std::string str;
	int incAt = 65;
	int cont = 0;
	Hashtable* h = new Hashtable(
		10, //unsigned int initial_length,
		10, //unsigned int initial_growth_rate,
		0.8, //float initial_max_occupation_rate,
		3,  //unsigned int initial_max_tree_size,
		10  //unsigned int initial_max_exceeded_trees
	);


	if(((Node<std::string>*)
		h->get(
			new stringao("0"))) != NULL)
	{
		str = *(((Node<std::string>*)
			h->get(
				new stringao("0")))
			->info);

		cout << str << '\n';
	}

	h->remove(new stringao("0"));

	Node<std::string>* n = ((Node<std::string>*)
		h->get(
			new stringao("0")));

	if (n != NULL)
		cout << (n->info);

	else
		cout << "\n\nNao dah pra excluir algo que nao existe";


	for (int i = 0; i < 500; i++)
	{
		char c = cont++ + incAt;
		
		if (c == 90)
		{
			incAt = 97;
			cont = 0;
		}			

		if (c == 122)
		{
			incAt = 65;
			cont = 0;
		}
		std::string str(1, c);
		std::string* strp = new std::string(str);

		char c2 = i + 48;
		char* cp = (char*)malloc(sizeof(char));
		cp[0] = c2;
		cp[1] = '\0';

		stringao* s = new stringao(cp);
		Node<std::string>* nP = (new Node<std::string>(strp, s));

		h->insert
		(nP);
	}

	cout << '\n' << h->count;

	cout << "\n\n\n\n\n\n\n" + h->toString();

	cin >> str;

	return 0;
}