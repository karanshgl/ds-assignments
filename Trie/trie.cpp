#include <iostream>
#include <vector>
#include <fstream>
#include "trie.h"

using namespace std;

Node::Node(){
	children = new Node*[26];
	for(int i=0;i<26;i++) children[i] = NULL;
	isEnd = false;
}
Node::Node(int id, int be, int en, Node* p){
	word_index = id;
	begin = be;
	end = en;
	parent = p;
	isEnd = false;
	children = new Node*[26];
	for(int i=0;i<26;i++) children[i] = NULL;
}

string Node::getString(List list){
	return list.names[word_index].substr(begin, end - begin + 1);
}	

int Node::size(){
	return (end - begin + 1);
}



int Trie::ctoi(char a){
	// Maps a character to the index
	if(a > 64 && a < 91){
		// Upper
		return a - 'A';
	}
	// Lower
	return a - 'a';
}

Trie::Trie(){
	root = new Node;
	wordCount = -1;
}

void Trie::insert(string str, string num){
	// Inserts the name and number in vectors and the main trie

	// Add the name and number in the respective vectors
	words.names.push_back(str);
	words.numbers.push_back(num);
	wordCount++;
	int be = 0;
	int en = str.size()-1;
	int si = 0;

	Node *it = root;

	bool itUpdate = true;
	int i;
	while(it && be < str.size()){

		if(itUpdate) i = ctoi(str[be]);
		if(it->children[i] == NULL){
			// prefix doesn't exist
			it->children[i] = new Node(wordCount,be,en,it);
			it->children[i]->isEnd = true;
			return;
		}

		if(si >= it->children[i]->size()){
			// Existing string was prefix of the string to Add
			int c = ctoi(str[be]);
			if(it->children[i]->children[c]){
				// Further nodes exist
				it = it->children[i];
				itUpdate = true;
				si = 0;
				continue;
			}

			// Further children doesn't exist, add the child

			it->children[i]->children[c] = new Node(wordCount,be,en,it->children[i]);
			it->children[i]->children[c]->isEnd = true;
			return;

		}

		if(it->children[i]->getString(words)[si] == str[be]){
			si++;
			be++;
			itUpdate = false;
			continue;
		}

		// Break the node
		int p = si;
		si += it->children[i]->begin;

		Node *goDown = new Node(it->children[i]->word_index, si, it->children[i]->end,it->children[i]);
		goDown->isEnd = it->children[i]->isEnd;
		goDown->children = it->children[i]->children;
		char d = it->children[i]->getString(words)[p];
		int c = ctoi(d); 
		it->children[i]->end = si-1;
		it->children[i]->children = new Node*[26];
		it->children[i]->isEnd = false;
		for(int j=0;j<26;j++) it->children[i]->children[j] = NULL;
		it->children[i]->children[c] = goDown;
		Node *branch = new Node(wordCount,be,en,it->children[i]);
		c = ctoi(str[be]);
		branch->isEnd = true;
		it->children[i]->children[c] = branch;
		return;
	}

	// Node to add is actually a prefix
	if(si == it->children[i]->size()){
		cout<<"Entry Already Exists"<<endl;
		return;
	}
		int p = si;
		si += it->children[i]->begin;

		Node *goDown = new Node(it->children[i]->word_index, si, it->children[i]->end,it->children[i]);
		goDown->isEnd = it->children[i]->isEnd;
		goDown->children = it->children[i]->children;
		char d = it->children[i]->getString(words)[p];
		int c = ctoi(d); 
		it->children[i]->end = si-1;
		it->children[i]->children = new Node*[26];
		it->children[i]->isEnd = true;
		it->children[i]->word_index = wordCount;
		for(int j=0;j<26;j++) it->children[i]->children[j] = NULL;
		it->children[i]->children[c] = goDown;
		

}

void Trie::find(string prefix){
	// Displays the similar strings
	matchCount = 0;
	Node *it = root;
	int be = 0;
	int si = 0;
	bool itUpdate = true;
	int i;
	while(it && be < prefix.size()){
		if(itUpdate) i = ctoi(prefix[be]);

		if(it->children[i] == NULL){
			// Not Found
			cout<<"Contact Not Found"<<endl;
			return;
		}

		if(si >= it->children[i]->size()){
			// If we have to go down the tree
			int c = ctoi(prefix[be]);
			if(it->children[i]->children[c]){
				// Further nodes exist
				it = it->children[i];
				itUpdate = true;
				si = 0;
			}
			else{
				cout<<"Contact Not Found"<<endl;
				return;
			}
		}
		else if(it->children[i]->getString(words)[si] == prefix[be]){
			// If we have to search the node
			si++;
			be++;
			itUpdate = false;
		}
		else{
			cout<<"Contact Not Found"<<endl;
			return;
		}
	}

	// We have reached our destination, with it->children[i] has the root of the tree transversal
	transversal(it->children[i]);
	cout<<"We found "<<matchCount<<" contacts matching "<<prefix<<endl;
	int topSize = ((matchCount<5)? matchCount: 5);
	cout<<"Top "<<topSize<<" are:"<<endl;
	for(int i=0;i<topSize;i++) cout<<i+1<<". "<<words.names[topFive[i]]<<"\t"<<words.numbers[topFive[i]]<<endl;
}

void Trie::transversal(Node *trie){
	if(trie == NULL) return;

	if(trie->isEnd){
		//cout<<words.names[trie->word_index]<<"\t"<<words.numbers[trie->word_index]<<endl;
		if(matchCount<5) topFive[matchCount] = trie->word_index;
		matchCount++;
	}

	for(int i=0;i<26;i++){
		transversal(trie->children[i]);
	}
}


