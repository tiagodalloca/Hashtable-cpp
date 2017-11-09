#ifndef NODE
#define NODE

#include <stdlib.h>
#include <string>

#define max(n1,n2) (n1 > n2 ? n1 : n2)
#define height(n) (n == NULL ? 0 : n->h)
#define bf(n) (height(n->l) - height(n->r))

using namespace std;

template<typename T>
class Node{

public:
	T info;
	unsigned int i;
	
	Node(T o, int i);
	Node(int i);
	Node();
	
	bool operator== (const Node<T> &n);
	bool operator> (const Node<T> &n);
	bool operator< (const Node<T> &n);
	bool operator<= (const Node<T> &n);
	bool operator>= (const Node<T> &n);
	bool operator!= (const Node<T> &n);

};

template<typename T>
Node<T>::Node(T o, int i){
	info = o;
	this->i = i;
}

template<typename T>
Node<T>::Node(int i){
	this->i = i;
}

template<typename T>
Node<T>::Node(){
	this->i = -1;
}

template<typename T>
bool Node<T>::operator== (const Node<T> &n){
	return n.i == i;
}

template<typename T>
bool Node<T>::operator> (const Node<T> &n){
	return n.i > i;
}

template<typename T>
bool Node<T>::operator< (const Node<T> &n){
	return n.i < i;
}

template<typename T>
bool Node<T>::operator<= (const Node<T> &n){
	return n == this || n < this;
}

template<typename T>
bool Node<T>::operator>= (const Node<T> &n){
	return n == this || n > this;
}

template<typename T>
bool Node<T>::operator!= (const Node<T> &n){
	return !(n.i == i );
}

#endif //NODE	
