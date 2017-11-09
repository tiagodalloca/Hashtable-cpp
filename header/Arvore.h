#ifndef ARVORE
#define ARVORE

#include <stdlib.h>
#include <string>
#include <stack>

#define max(n1,n2) (n1 > n2 ? n1 : n2)
#define height(n) (n == NULL ? 0 : n->h)
#define bf(n) (height(n->l) - height(n->r))

using namespace std;

template<typename T>
class Arvore{
		
	typedef struct StackFrameToString{
		const struct Arvore<T>::Node *no;
		std::string *str;
		char position;
	} StackFrameToString;

	typedef struct StackFrameRemove {
		struct Arvore<T>::Node *root;
		T o;
		char retorno;
		char position;
	} StackFrameRemove;

	typedef struct StackFrameDestructor {
		struct Arvore<T>::Node *root;
		char position;
	}StackFrameDestructor;

	struct Node{
		T info;
		Node *l;
		Node *r;
		Node *p;

		unsigned int h;
	};
 public:
  Arvore();
  ~Arvore();
  void arvore_Destrutor(struct Node* raiz);
  Arvore(const Arvore<T> *a);
  unsigned int getCount() const;
  unsigned int getHeight() const;
	T* get(T o);

	template <typename U>
  friend ostream& operator<< (ostream&, const Arvore<U>&);
	template <typename U>
  friend istream& operator >> (istream&, Arvore<U>&);


	void insert(T o);
	void remove(T o);	
	int remove_Node(Node *raiz, T o);
	std::string toString() const;
	Node *root;
	
 protected:

	unsigned int count;
	std::string toStringAux(const Node *no) const;
	
	void rotateLeft(Node *x);
	void rotateRight(Node *y);
	void copyNode(Node *n1, Node *n2);
	void freeNode(Node *n1, Node* noR);
};

template<typename T>
Arvore<T>::Arvore(){
  root = NULL; 
	count= 0;
}

template<typename T>
Arvore<T>::Arvore(const Arvore<T> *a){
	
}

template<typename T>
unsigned int Arvore<T>::getHeight() const{
	return height(root);
}

template<typename T>
int Arvore<T>::remove_Node(Node *raiz, T o) {
	int ret = 1;
	std::stack<StackFrameRemove> stack = std::stack<StackFrameRemove>();
	StackFrameRemove sfr;

	inicio:
	if (raiz == NULL)
	{
		ret = 0;
		goto doReturn;
	}

	if (o < raiz->info)
	{
		sfr.root = raiz;
		sfr.o = o;
		sfr.retorno = ret;
		sfr.position = 1;
		stack.push(sfr);

		raiz = raiz->l;
		goto inicio;

		retorno1:
		if (ret == 1) {
			raiz->h = max(height(raiz->l), height(raiz->r)) + 1;
			int befao = bf(raiz);
			if (befao < -1)
			{
				if (height(raiz->r->l) <= height(raiz->r->r))
					rotateLeft(raiz);
				else
				{
					rotateRight(raiz->r);
					rotateLeft(raiz);
				}
			}
		}
	}

	if (o > raiz->info)
	{
		sfr.root = raiz;
		sfr.retorno = ret;
		sfr.o = o;
		sfr.position = 2;
		stack.push(sfr);

		raiz = raiz->r;
		goto inicio;

		retorno2:
		if (ret == 1) {
			raiz->h = max(height(raiz->l), height(raiz->r)) + 1;
			int befao = bf(raiz);
			if (befao > 1)
			{
				if (height(raiz->l->r) <= height(raiz->l->l))
					rotateLeft(raiz);
				else
				{
					rotateRight(raiz->r);
					rotateLeft(raiz);
				}
			}
		}
	}

	if (raiz->info == o)
	{
		if (raiz->l == NULL || raiz->r == NULL)
		{
			struct Node *old = raiz;
			if (raiz->l != NULL)
				raiz = raiz->l;
			else
			{
				Node* pai = raiz->p;
				raiz = raiz->r;
				if (raiz != NULL)
				{
					raiz->h = max(height(raiz->l), height(raiz->r)) + 1;
					raiz->p = pai;
				}
			}

			freeNode(old, raiz);

		}
		else
		{
			struct Node *no1 = raiz->r;
			struct Node *no2 = raiz->r->l;
			while (no2 != NULL) {
				no1 = no2;
				no2 = no2->l;
			}
			struct Node* temp = no1;
			raiz->info = temp->info;

			sfr.root = raiz;
			sfr.retorno = ret;
			sfr.o = o;
			sfr.position = 3;
			stack.push(sfr);

			raiz = raiz->r;
			o = temp->info;
			goto inicio;

			retorno3:
			int befao = bf(raiz);
			if (befao > 1)
			{
				if (height(raiz->l->r) <= height(raiz->l->l))
					rotateRight(raiz);
				else
				{
					rotateLeft(raiz->l);
					rotateRight(raiz);
				}
			}
			raiz->h = max(height(raiz->l), height(raiz->r)) + 1;
		}
		ret = 1;
		goto doReturn;
	}

	doReturn:
	if (stack.empty())
		return ret;

	sfr = stack.top();
	stack.pop();
	raiz = sfr.root;
	ret = sfr.retorno;
	o = sfr.o;

	if (sfr.position == 1)
		goto retorno1;
	else if (sfr.position == 2)
		goto retorno2;
	else if (sfr.position == 3)
		goto retorno3;
	else 
		goto inicio;
}

template<typename T>
unsigned int Arvore<T>::getCount() const{
	return count;
}

template<typename T>
ostream& operator <<(ostream& OS, const Arvore<T>& S)
{
	return (OS << S.toString());
}

template<typename T>
istream& operator >>(istream& IS, Arvore<T>& S)
{
	IS >> S.toString();

	return IS;
}

template<typename T>
std::string Arvore<T>::toString() const{
	return toStringAux(root);
}

template<typename T>
std::string Arvore<T>::toStringAux(const Node *no) const{

	std::stack<StackFrameToString> stack = std::stack<StackFrameToString> ();
	
	StackFrameToString sf;
	sf.str = new std::string();
	sf.no = &*(no);
	sf.position = 0;
	
	stack.push(sf);
	
	for(; !stack.empty(); sf = stack.top(), stack.pop()){
		
		std::string s;
		
		StackFrameToString temp;
		
		if (sf.no != NULL){
			
			switch(sf.position){
				case 0:
					goto pos0;
					break;
					
				case 1:
					goto pos1;
					break;
					
				case 2:
					goto pos2;
					break;
					
				default:
					goto pos0;
					break;
			}
			
			pos0:
			sf.str->append("(");
			temp.no = sf.no->l;
			temp.str = sf.str;
			temp.position = 0;
			sf.position++;
			stack.push(sf);
			stack.push(temp);
			continue;

			pos1:
			sf.str->operator +=(sf.no->info);
			temp.no = sf.no->r;
			temp.str = sf.str;
			temp.position = 0;
			sf.position++;
			stack.push(sf);
			stack.push(temp);
			continue;
			
			pos2:
			sf.str->append(")");
		}
	}
	
	return *sf.str;
}

template<typename T>
Arvore<T>::~Arvore(){

	arvore_Destrutor(root);

}

template<typename T>
void Arvore<T>::arvore_Destrutor(struct Node *raiz)
{
	std::stack<StackFrameDestructor> stack = std::stack<StackFrameDestructor>();
	StackFrameDestructor sfd;
	inicio:
	if (raiz != NULL)
	{
		sfd.root = raiz;
		sfd.position = 1;
		stack.push(sfd);

		raiz = raiz->l;
		goto inicio;

		pos1:
		sfd.root = raiz;
		sfd.position = 2;
		stack.push(sfd);

		raiz = raiz->r;
		goto inicio;

		pos2:
		free(raiz) ;
		raiz = NULL;
	}
	if (!stack.empty())
	{
		sfd = stack.top();
		stack.pop();
		raiz = sfd.root;	
		if (sfd.position == 1)
			goto pos1;
		else if (sfd.position == 2)
			goto pos2;
	}

}

//template<typename T>
//struct Node* Arvore<T>::procuraMenor(struct Node *atual){
//	struct Node *no1 = atual;
//	struct Node *no2 = atual->l;
//	while(no2 != NULL){
//		no1 = no2;
//		no2 = no2->l;
//	}
//	return no1;
//}


template<typename T>
T* Arvore<T>::get(T o){
	Node *no = root;
	
	while(no != NULL){
		if (no->info > o)
			no = no->r;
		
		else if (no->info <  o)
			no = no->l;

		else
			break;
	}
	
	if (no != NULL)
		return &(no->info);
	
	return NULL;
}

template<typename T>
void Arvore<T>::remove(T o){
	remove_Node(root, o);
}

template<typename T>
void Arvore<T>::copyNode(Node *n1, Node* n2){
	n2->l = n1->l;
	n2->r = n1->r;
	n2->p = n1->p;
	n2->info = n1->info;
	n2->h = n1->h;
}

template<typename T>
void Arvore<T>::freeNode(Node *n1, Node* noR) {
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

template<typename T>
void Arvore<T>::rotateRight(Node *y){
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

template<typename T>
void Arvore<T>::rotateLeft(Node *x){
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

template<typename T>
void Arvore<T>::insert(T o){
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
			if (o < no->info){
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

			if (o > no->info){
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
		 	if(o < no->l->info){
		 		rotateRight(no);
		 	}

		 	else{
		 		rotateLeft(no->l);
				rotateRight(no);
			}
			
			continue;
		}

		else if (balanceF < -1){
		 	if(o > no->r->info){
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
#endif
