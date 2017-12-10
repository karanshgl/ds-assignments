#ifndef NODE_H
#define NODE_H

#include <iostream>

template <typename K, typename V> class Number_Map;
template <typename K, typename V> class Name_Map;


template <typename K, typename V>
class Node{
public:
	V value;
	K key;
	Node<K,V>* next;

	friend class Number_Map<K,V>;
	friend class Name_Map<K,V>;

	Node(){
		next = NULL;
	}
	Node(K k,V d){
		value = d;
		key = k;
		next = NULL;
	}
};

#endif
