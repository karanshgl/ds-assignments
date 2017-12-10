#include <iostream>
#include <fstream>
#include <algorithm>
#include "trie.h"

using namespace std;

int main(){
	Trie t;
	fstream fin;
	fin.open("name_number.txt");
	while(!fin.eof()){
		string name,number;
		fin>>name>>number;
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		t.insert(name,number);
	}
	string a;
	cout<<"Please enter full/partial contact name"<<endl;
	cin>>a;
	transform(a.begin(), a.end(), a.begin(), ::tolower);
	t.find(a);
}