#include <stdlib.h>
#include <string>
#include <iostream>
#include "Arvore.h"
#include "IHashble.h"
#include "Node.h"

#define max(n1,n2) (n1 > n2 ? n1 : n2)
#define height(n) (n == NULL ? 0 : n->h)
#define bf(n) (height(n->l) - height(n->r))

Arvore::Arvore() {
	root = NULL;
	count = 0;
	ind = 0;
}

Arvore::Arvore(const Arvore *a) {

}

unsigned int Arvore::getHeight() const {
	return height(root);
}

unsigned int Arvore::getCount() const {
	return count;
}

unsigned int Arvore::getInd() const {
	return ind;
}

std::string Arvore::toString() const {
	return toStringAux(root);
}

std::string Arvore::toStringAux(const NodeA *no) const {

	std::string str = "";

	if (no != NULL) {
		str += "(";

		str += toStringAux(no->l);

		str += *(((Node<std::string>*)
			no->info)
			->info);

		str += ")";
	}

	return str;
}

IHashble** Arvore::getElements() {
	IHashble** aux = (IHashble**)malloc(sizeof(Arvore*));
	ind = 0;
	getElementsAux(root, aux);
	return aux;
}

Arvore::~Arvore() {

	arvore_Destrutor(root);

}

void Arvore::getElementsAux(const NodeA *no, IHashble** aux) {

	if (no != NULL) {

		getElementsAux(no->l, aux);

		IHashble* ih = no->info;
		aux[ind++] = ih; //DEU RUIM 

		getElementsAux(no->r, aux);

	}
}

void Arvore::arvore_Destrutor(struct NodeA *raiz)
{
	if (raiz != NULL)
	{
		arvore_Destrutor(raiz->l);
		arvore_Destrutor(raiz->r);
		free(raiz);
		raiz = NULL;
	}
}

IHashble* Arvore::get(IHashble* o) const {
	NodeA *no = root;

	while (no != NULL) {
		if (o->hashcode() > no->info->hashcode())
			no = no->r;

		else if (o->hashcode() < no->info->hashcode())
			no = no->l;

		else
			break;
	}

	if (no != NULL)
		return no->info;

	return NULL;
}

void Arvore::remove(IHashble* o) {
	remove_Node(root, o);
}

void Arvore::copyNode(NodeA *n1, NodeA* n2) {
	n2->l = n1->l;
	n2->r = n1->r;
	n2->p = n1->p;
	n2->info = n1->info;
	n2->h = n1->h;
}

void Arvore::freeNode(NodeA *n1, NodeA* noR) {
	if (n1->p != NULL) {
		if (n1->p->l != NULL)
			if (n1->p->l->info == n1->info)
				n1->p->l = noR;

		if (n1->p->r != NULL)
			if (n1->p->r->info == n1->info)
				n1->p->r = noR;
	}

	free(n1);
	count--;
}

void Arvore::rotateRight(NodeA *y) {
	NodeA* temp = (NodeA*)malloc(sizeof(NodeA));
	copyNode(y, temp);

	NodeA* x = y->l;
	NodeA* xr = x->r;
	NodeA* yp = y->p;
	copyNode(x, y);
	y->p = yp;

	if (y->l != NULL)
		y->l->p = y;

	copyNode(temp, x);
	y->r = x;
	x->p = y;

	x->l = xr;

	if (xr != NULL)
		xr->p = x;

	if (x->l != NULL)
		x->l->p = x;

	if (x->r != NULL)
		x->r->p = x;

	x->h = max(height(x->l), height(x->r)) + 1;
	y->h = max(height(x->l), height(x->r)) + 1;

	delete temp;
}

void Arvore::rotateLeft(NodeA *x) {
	NodeA* temp = (NodeA*)malloc(sizeof(NodeA));
	copyNode(x, temp);

	NodeA* y = x->r;
	NodeA* yl = y->l;
	NodeA* xp = x->p;
	copyNode(y, x);
	x->p = xp;

	if (x->r != NULL)
		x->r->p = x;

	copyNode(temp, y);
	x->l = y;
	y->p = x;

	y->r = yl;

	if (yl != NULL)
		yl->p = y;

	if (y->l != NULL)
		y->l->p = y;

	if (y->r != NULL)
		y->r->p = y;

	y->h = max(height(y->l), height(y->r)) + 1;
	x->h = max(height(x->l), height(x->r)) + 1;

	delete temp;
}

void Arvore::insert(IHashble* o) {
	NodeA *no = root;

	if (root == NULL) {
		root = (NodeA*)malloc(sizeof(NodeA));
		root->p = NULL;
		root->l = NULL;
		root->r = NULL;
		root->info = o;
		root->h = 1;
		no = root;
		count++;
	}

	else
		while (1) {
			if (o->hashcode() < no->info->hashcode()) {
				if (no->l == NULL) {
					no->l = (NodeA*)malloc(sizeof(NodeA));
					no->l->info = o;
					no->l->l = NULL;
					no->l->r = NULL;
					no->l->p = no;

					no = no->l;
					count++;
					break;
				}
				no = no->l;
				continue;
			}

			if (o->hashcode() > no->info->hashcode()) {
				if (no->r == NULL) {
					no->r = (NodeA*)malloc(sizeof(NodeA));
					no->r->info = o;
					no->r->l = NULL;
					no->r->r = NULL;
					no->r->p = no;

					no = no->r;
					count++;
					break;
				}

				no = no->r;
				continue;
			}

			return;
		}

	NodeA* nop = no;

	while (no != NULL) {
		no->h = max(height(no->l), height(no->r)) + 1;

		int balanceF = bf(no);

		if (balanceF > 1) {
			if (o->hashcode() < no->l->info->hashcode()) {
				rotateRight(no);
			}

			else {
				rotateLeft(no->l);
				rotateRight(no);
			}

			continue;
		}

		else if (balanceF < -1) {
			if (o->hashcode() > no->r->info->hashcode()) {
				rotateLeft(no);
			}

			else {
				rotateRight(no->r);
				rotateLeft(no);
			}

			continue;
		}


		nop = no;
		no = no->p;
	}

	root = nop;

}