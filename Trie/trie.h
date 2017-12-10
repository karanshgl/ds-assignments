#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>

using namespace std;


class List{
	// Contains the list of names and corresponding numbers
	friend class Node;
	friend class Trie;

	vector<string> names;	// List of Names
	vector<string> numbers;	// List of Numbers
};


class Node{
	// Represents a node of a trie
	int word_index;	// Index of the word
	int begin;	// Begin offset
	int end;	// End offset
	Node **children;	// Children of the node
	Node *parent;		// Parent of the node
	bool isEnd;			// If the node is the end of a name

	friend class Trie;
public:
	Node();	// Default constructor
	Node(int id, int be, int en, Node* p);	// Takes the word_index, begin offset, end offset and parent as the input
	string getString(List list);	// Returns the string contained in the node
	int size();	// Returns the size of the string
};

class Trie{
	// Class to represent a compressed trie

	// Private Members
	Node *root;	// Represents the root of the trie
	int wordCount;	// Contains the number of nodes
	List words;		// Contains the list of names and numbers
	int matchCount;	//	Contains the number of matches if a qeury is asked
	int topFive[5];	//	Stores the top 5 matches, if a query is asked

	// Private Functions
	int ctoi(char a);	
	

public:
	Trie();	// Constructor for a trie
	void insert(string str, string num);	// Inserting a name and a number
	void find(string prefix);	// Finding the start of the traversal and prints all the matches
	void transversal(Node *trie);	// Scans all the possible paths from a node
	
};

#endif