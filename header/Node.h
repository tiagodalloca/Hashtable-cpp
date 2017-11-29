#ifndef NODE
#define NODE

#include <stdlib.h>
#include <string>

#include "IHashble.h"

#define max(n1,n2) (n1 > n2 ? n1 : n2)
#define height(n) (n == NULL ? 0 : n->h)
#define bf(n) (height(n->l) - height(n->r))

using namespace std;

template<typename T>
class Node : public IHashble{

public:
	T* info;
	IHashble* key;
	
	Node(T* to, IHashble* ho);
	Node(IHashble* ho);
	Node();
	
	unsigned int hashcode();
	
	bool operator== (const Node<T> &n);
	bool operator> (const Node<T> &n);
	bool operator< (const Node<T> &n);
	bool operator<= (const Node<T> &n);
	bool operator>= (const Node<T> &n);
	bool operator!= (const Node<T> &n);

};

template<typename T>
Node<T>::Node(T* to, IHashble* ho){
	info = to;
	key = ho;
}

template<typename T>
Node<T>::Node(IHashble* ho){
	Node(NULL, ho);
}

template<typename T>
Node<T>::Node(){
	Node(NULL, NULL);
}

template<typename T>
unsigned int Node<T>::hashcode(){
	return key->hashcode();
}

template<typename T>
bool Node<T>::operator== (const Node<T> &n){
	return n.hashcode() == hashcode();
}

template<typename T>
bool Node<T>::operator> (const Node<T> &n){
	return n.hashcode() > hashcode();
}

template<typename T>
bool Node<T>::operator< (const Node<T> &n){
	return n.hashcode()  < hashcode();
}

template<typename T>
bool Node<T>::operator<= (const Node<T> &n){
	return n.hashcode() == hashcode() || n.hashcode() < hashcode();
}

template<typename T>
bool Node<T>::operator>= (const Node<T> &n){
	return n.hashcode() == hashcode() || n.hashcode() > hashcode();
}

template<typename T>
bool Node<T>::operator!= (const Node<T> &n){
	return !(n.hashcode() == hashcode());
}

#endif //NODE	
