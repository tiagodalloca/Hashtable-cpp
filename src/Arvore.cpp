#include <stdlib.h>
#include <string>
#include <iostream>
#include "Arvore.h"
#include "IHashble.h"

#define max(n1,n2) (n1 > n2 ? n1 : n2)
#define height(n) (n == NULL ? 0 : n->h)
#define bf(n) (height(n->l) - height(n->r))


Arvore::Arvore(){
  root = NULL; 
	count= 0;
	indice = 0;
}

Arvore::Arvore(const Arvore *a){
	
}

unsigned int Arvore::getHeight() const{
	return height(root);
}

unsigned int Arvore::getCount() const{
	return count;
}

unsigned int Arvore::getIndice() const{
	return indice;
}


IHashble* Arvore::getElements() {
	IHashble* aux;
	getElementsAux(root,aux);
	return aux;
}

std::string Arvore::toString() const{
	return toStringAux(root);
}

void Arvore::getElementsAux(const Node *no,IHashble* aux) {
	
	if (no != NULL) {

		getElementsAux(no->l,aux);

		aux[indice++] = *no->info; //talvez de ruim

		getElementsAux(no->r,aux);

	}
}
std::string Arvore::toStringAux(const Node *no) const {

	std::string str = "";
	
	if (no != NULL){
		str += "(";
		
		str += toStringAux(no->l);

		str += no->info->hashcode();

		str += toStringAux(no->r);

		str += ")";
	}

	return str;
}



Arvore::~Arvore(){

	arvore_Destrutor(root);

}

void Arvore::arvore_Destrutor(struct Node *raiz)
{
	if (raiz != NULL)
	{
		arvore_Destrutor(raiz->l);
		arvore_Destrutor(raiz->r);
		free(raiz) ;
		raiz = NULL;
	}
}

IHashble* Arvore::get(IHashble* o) const{
	Node *no = root;
	
	while(no != NULL){
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

void Arvore::remove(IHashble* o){
	remove_Node(root, o);
}

void Arvore::copyNode(Node *n1, Node* n2){
	n2->l = n1->l;
	n2->r = n1->r;
	n2->p = n1->p;
	n2->info = n1->info;
	n2->h = n1->h;
}

void Arvore::freeNode(Node *n1, Node* noR) {
	if (n1->p != NULL) {
		if (n1->p->l != NULL)
			if (n1->p->l->info == n1->info)
				n1->p->l = noR;

		if(n1->p->r != NULL)
			if (n1->p->r->info == n1->info)
				n1->p->r = noR;
	}
	
	free(n1);
	count--;
}

void Arvore::rotateRight(Node *y){
	Node* temp = (Node*) malloc(sizeof(Node));
	copyNode(y, temp);
	
	Node* x = y->l;
	Node* xr = x->r;
	Node* yp = y->p;
	copyNode(x, y);
	y->p = yp;
	
	if(y->l != NULL)
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
	
	x->h = max(height(x->l),height(x->r)) + 1;
	y->h = max(height(x->l),height(x->r)) + 1;

	delete temp;
}

void Arvore::rotateLeft(Node *x){
	Node* temp = (Node*) malloc(sizeof(Node));
	copyNode(x, temp);
	
	Node* y = x->r;
	Node* yl = y->l;
	Node* xp = x->p;
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
	
	y->h = max(height(y->l),height(y->r)) + 1;
	x->h = max(height(x->l),height(x->r)) + 1;

	delete temp;
}

void Arvore::insert(IHashble* o){
	Node *no = root;
	
	if (root == NULL){
		root = (Node*) malloc(sizeof(Node));
		root->p = NULL;
		root->l = NULL;
		root->r = NULL;
		root->info = o;
		root->h = 1;
		no = root;
		count++;
	}

	else
		while(1){
			if (o->hashcode() < no->info->hashcode()){
				if (no->l == NULL){
					no->l =	(Node*) malloc(sizeof(Node));
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

			if (o->hashcode() > no->info->hashcode()){
				if (no->r == NULL){
					no->r =	(Node*) malloc(sizeof(Node));
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

	Node* nop = no;
	
	while(no != NULL){
		no->h = max(height(no->l),height(no->r)) + 1;

		int balanceF = bf(no);
		
		if (balanceF > 1){
		 	if(o->hashcode() < no->l->info->hashcode()){
		 		rotateRight(no);
		 	}

		 	else{
		 		rotateLeft(no->l);
				rotateRight(no);
			}
			
			continue;
		}

		else if (balanceF < -1){
		 	if(o->hashcode() > no->r->info->hashcode()){
		 		rotateLeft(no);
		 	}

		 	else{
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