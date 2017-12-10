#include "node.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename K, typename V>
  class Name_Map {					// map interface
  	int len;
  	int nK;
  	V defRet;
  	double cRate[12];
  	Node<K,V> **table[12];
  	enum combination {
  		ID, IMAD, IM,
  		CoD, CoMAD, CoM,
  		PD, PMAD, PM,
  		CyD, CyMAD, CyM
  	};

  	// HASH CODES
  	int integer_cast(K str);
  	int component_sum(K str);
  	int polynomial_sum(K str);
  	int cycle_shift(K str);

  	// HASH FUNCTIONS
  	int divide(int code);
  	int mad(int code);
  	int multiply(int code);

  	// List Operations
  	void insert(Node<K,V>*&,K,V,int);
  	void remove(Node<K,V>*&,K);
  	V& search(Node<K,V>*, K);


  public:
    Name_Map(int capacity=2531);			// constructor
    int size() const;				// number of entries in the map
    bool empty() const;				// is the map empty?
    V& find(const K& k);		// find entry with key k
    void put(const K& k, const V& v);	// insert/replace pair (k,v)
    void erase(const K& k);			// remove entry with key k
    void input(string s);			// Reads from a file
    void output(string s);			// Prints in the file
 };

template <typename K, typename V>
Name_Map<K,V>::Name_Map(int capacity){
	nK = 0;
	len = capacity;
	for(int i=0;i<12;i++){
		cRate[i] = 0;
		table[i] =  new Node<K,V>*[capacity];
		for(int j = 0; j<capacity;j++) table[i][j] = NULL;
	}
	defRet = "Not Found";
}

template <typename K, typename V>
int Name_Map<K,V>::integer_cast(K str){
	// Sums up each block characters of the string
	int toRet = 0;
	int shift[4] = {0,8,16,24};
	int n = str.length();
	for(int i=0;i<4;i++){
		toRet+= str[n-i-1]<<shift[i];
	}
	return toRet;
}

template <typename K, typename V>
int Name_Map<K,V>::component_sum(K str){
	// Sums up each character of the string
	int toRet = 0;
	for(int i=0;i<str.size();i++){
		toRet+=str[i];
	}
	return toRet;
}

template <typename K, typename V>
int Name_Map<K,V>::polynomial_sum(K str){
	// Takes characters as coefficients of a polynomial
	int a = 33;
	int toRet = 0;
	for(int i=0; i<str.size();i++){
		toRet = str[i] + a*toRet;
	}

	return toRet;
}

template <typename K, typename V>
int Name_Map<K,V>::cycle_shift(K str){
	// Shifts the code cyclically by some amount
	unsigned int h = 0;
	int shift = 5;
	for(int i=0;i<str.size();i++){
		h = (h << shift) | (h >> (32 - shift));
		h += (unsigned int)str[i];
	}
	return h;
}

template <typename K, typename V>
int Name_Map<K,V>::divide(int code){
	// h = |k| mod m
	int greaterPrime = 2531;

	return ( code > 0 ? code%greaterPrime : (-code)%greaterPrime );
}

template <typename K, typename V>
int Name_Map<K,V>::mad(int code){
	// h = |ak + b| mod m
	int a = 500;
	int b = 211;
	int greaterPrime = 2531;

	code = a*code + b;

	return ( code > 0 ? code%greaterPrime : (-code)%greaterPrime );
}

template <typename K, typename V>
int Name_Map<K,V>::multiply(int code){
	// h = m(kA mod 1)
	if(code<0) code = -code;
	int greaterPrime = 2531;
	double A = 0.61803398875;
	double h = A*code;
	int floorh = (int)(A*code);
	h-=floorh;
	int m = 16384; // 2^p
	code = m*h;

	return ( code > 0 ? code%greaterPrime : (-code)%greaterPrime );
}


template <typename K, typename V>
int Name_Map<K,V>::size() const{
	return nK;
}

template <typename K, typename V>
bool Name_Map<K,V>::empty() const{
	return nK==0;
}

template <typename K, typename V>
void Name_Map<K,V>::put(const K& k, const V& v){

	for(int i=0; i<12; i++){
		if(i==CoD){
			// Component - Divide
			int code = component_sum(k);
			int index = divide(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i == CoMAD){
			// Component - MAD
			int code = component_sum(k);
			int index = mad(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i==CoM){
			// Component - Multiply
			int code = component_sum(k);
			int index = multiply(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i==PD){
			// Polynomial - Divide
			int code = polynomial_sum(k);
			int index = divide(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i==PMAD){
			// Polynomial - MAD
			int code = polynomial_sum(k);
			int index = mad(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i==PM){
			// Polynomial Multiply
			int code = polynomial_sum(k);
			int index = multiply(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i == CyD){
			// Cycle - Divide
			int code = cycle_shift(k);
			int index = divide(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i == CyMAD){
			// Cycle - MAD
			int code = cycle_shift(k);
			int index = mad(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i == CyM){
			// Cycle - Multiply
			int code = cycle_shift(k);
			int index = multiply(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i == ID){
			// Integer - Divide
			int code = integer_cast(k);
			int index = divide(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i == IMAD){
			// integer - mad
			int code = integer_cast(k);
			int index = mad(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
		else if(i == IM){
			// Cycle - Multiply
			int code = integer_cast(k);
			int index = multiply(code);
			remove(table[i][index],k);
			insert(table[i][index],k,v,i);
		}
	}
	nK++;
}

template <typename K, typename V>
void Name_Map<K,V>::insert(Node<K,V> *&head, K k, V v, int i){

	if(head == NULL){
		head = new Node<K,V>(k,v);
		return;
	}
	cRate[i]+=1;
	Node<K,V> *temp = new Node<K,V>(k,v);
	temp->next = head;
	head = temp;
}


template <typename K, typename V>
void Name_Map<K,V>::remove(Node<K,V> *&head, K key){
	if(head == NULL) return;

	Node<K,V> *cur = head;
	Node<K,V> *pre = NULL;
	while(cur){
		if(cur->key == key){
			if(pre == NULL){
				// Root
				head = head->next;
				delete(cur);
			}
			else{
				pre->next = cur->next;
				delete(cur);
			}
			break;
		}
		pre = cur;
		cur = cur->next;
	}
}


template <typename K, typename V>
void Name_Map<K,V>::erase(const K& k){
	for(int i=0; i<12; i++){
		if(i==CoD){
			// Component - Divide
			int code = component_sum(k);
			int index = divide(code);
			remove(table[i][index],k);
		}
		else if(i == CoMAD){
			// Component - MAD
			int code = component_sum(k);
			int index = mad(code);
			remove(table[i][index],k);
		}
		else if(i==CoM){
			// Component - Multiply
			int code = component_sum(k);
			int index = multiply(code);
			remove(table[i][index],k);
		}
		else if(i==PD){
			// Polynomial - Divide
			int code = polynomial_sum(k);
			int index = divide(code);
			remove(table[i][index],k);
		}
		else if(i==PMAD){
			// Polynomial - MAD
			int code = polynomial_sum(k);
			int index = mad(code);
			remove(table[i][index],k);
		}
		else if(i==PM){
			// Polynomial Multiply
			int code = polynomial_sum(k);
			int index = multiply(code);
			remove(table[i][index],k);
		}
		else if(i == CyD){
			// Cycle - Divide
			int code = cycle_shift(k);
			int index = divide(code);
			remove(table[i][index],k);
		}
		else if(i == CyMAD){
			// Cycle - MAD
			int code = cycle_shift(k);
			int index = mad(code);
			remove(table[i][index],k);
		}
		else if(i == CyM){
			// Cycle - Multiply
			int code = cycle_shift(k);
			int index = mad(code);
			remove(table[i][index],k);
		}
		else if(i == ID){
			// Integer - Divide
			int code = integer_cast(k);
			int index = divide(code);
			remove(table[i][index],k);
		}
		else if(i == IMAD){
			// integer - mad
			int code = integer_cast(k);
			int index = mad(code);
			remove(table[i][index],k);
		}
		else if(i == IM){
			// Cycle - Multiply
			int code = integer_cast(k);
			int index = multiply(code);
			remove(table[i][index],k);
		}
	}
}

template <typename K, typename V>
V& Name_Map<K,V>::find(const K& k){
	int m = cRate[0];
	//K k = key;
	int i = 0;
	for(int index=1;index<12;index++){
		if(cRate[index]<m){
			m = cRate[index];
			i = index;
		}
	}

	if(i==CoD){
			// Component - Divide
			int code = component_sum(k);
			int index = divide(code);
			return search(table[i][index],k);
		}
		else if(i == CoMAD){
			// Component - MAD
			int code = component_sum(k);
			int index = mad(code);
			return search(table[i][index],k);
		}
		else if(i==CoM){
			// Component - Multiply
			int code = component_sum(k);
			int index = multiply(code);
			return search(table[i][index],k);
		}
		else if(i==PD){
			// Polynomial - Divide
			int code = polynomial_sum(k);
			int index = divide(code);
			return search(table[i][index],k);
		}
		else if(i==PMAD){
			// Polynomial - MAD
			int code = polynomial_sum(k);
			int index = mad(code);
			return search(table[i][index],k);
		}
		else if(i==PM){
			// Polynomial Multiply
			int code = polynomial_sum(k);
			int index = multiply(code);
			return search(table[i][index],k);
		}
		else if(i == CyD){
			// Cycle - Divide
			int code = cycle_shift(k);
			int index = divide(code);
			return search(table[i][index],k);
		}
		else if(i == CyMAD){
			// Cycle - MAD
			int code = cycle_shift(k);
			int index = mad(code);
			return search(table[i][index],k);
		}
		else if(i == CyM){
			// Cycle - Multiply
			int code = cycle_shift(k);
			int index = mad(code);
			return search(table[i][index],k);
		}
		else if(i == ID){
			// Integer - Divide
			int code = integer_cast(k);
			int index = divide(code);
			return search(table[i][index],k);
		}
		else if(i == IMAD){
			// integer - mad
			int code = integer_cast(k);
			int index = mad(code);
			return search(table[i][index],k);
		}
		else if(i == IM){
			// Cycle - Multiply
			int code = integer_cast(k);
			int index = multiply(code);
			return search(table[i][index],k);
		}
}


template <typename K, typename V>
V& Name_Map<K,V>::search(Node<K,V> *head, K key){

	Node<K,V> *cur = head;
	while(cur){
		if(cur->key == key){
			return cur->value;
		}
		cur = cur->next;
	}
	return defRet;
}

template <typename K, typename V>
void Name_Map<K,V>::input(string s){

	ifstream fin;
	fin.open(s.c_str(), ios::in);
	K key;
	V value;
	char ch;
	while(!fin.eof()){
		fin>>key;
		fin.get(ch);
		getline(fin,value);
		put(key,value);
	}

}

template <typename K, typename V>
void Name_Map<K,V>::output(string s){

	ofstream fout;
	fout.open(s.c_str(), ios::out);
	string code[4]={"Int Cast", "Comp Sum", "Poly Sum", "Cycle Shift"};
	fout<<"NAME MAP"<<endl;
	fout<<"\t\t\tDIVIDE\t\t MAD\t\tMULTIPLY"<<endl;
	int k = 0;
	for(int i=0;i<12;i++){
		if(i%3==0){
			fout<<code[k++].c_str()<<"\t";
		}
		fout<<cRate[i]/nK<<"\t";
		if(i%3==2) fout<<endl;
	}
	fout<<endl;
}