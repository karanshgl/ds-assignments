#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

class Vertex;

class Decoration{
	// Contains additional Vertex info
	bool visited;	// If the vertex is visited in a tranversal
	bool inStack;	// If the vertex is in recursion stack

	int inDeg;		// The in Degree of a vertex during topo sort
	int lp;			// The length of longest path so far

	vector<Vertex *> lpList;	// The vertices in the long path ending at this vertex

	friend class Vertex;
	friend class Graph;
public:
	Decoration();
};

class Vertex{
	// Represents a vertex in a graph
	string name;	// Name of the course
	int duration;	// Duration of the course
	int inDeg;		// in Degree of the course
	int in;			// Index in the adj list of the vertex
	Decoration decore;	// Decoration object

	friend class Edge;
	friend class Graph;
public:
	Vertex();	// Default Constructor
	Vertex(string str, int dur, int i);	// Initializes a vertex
	string& getName();	// Returns the name of the course
	int getDur();		// Returns the duration of the course
	void resetDecor();	// Resets the decoration
	bool isVisted();	// Returns if the vertex is visited
	bool insideStack();	// Returns if the vertex is inside the recursion stack

};

class Edge{
	// Represents an edge of a graph
	Vertex *start;	// Begining of the edge
	Vertex *end;	// End of the edge
	int weight;		// If weighted

	friend class Graph;
public:
	Edge();	// Constructor
	Edge(Vertex *u, Vertex *v, int wt = 1);	// Initializes the edge
	Vertex* getEnd();	// Returns the end point
	Vertex* getBegin();	// Returns the beginning
};



class Graph{
	// Represents a Graph
	int nV;	// Number of vertices
	int nE;	// Number of edges
	vector<Vertex*> vList;	// List of vertices
	map<string,Vertex*> vertex;	// Map from course name to vertex
	vector<list<Edge*> > adjList;	// Adj List of the Graph

	// Private function
	bool detectCycle(int start);	// Returns true if there is a cycle
	
public:
	Graph();	// Constructor
	void insertVertex(string str, int dur);	// Inserts a vertex
	void insertEdge(string p1, string p2);	// Inserts an edge
	bool isCycle();	// Returns true if there is a cycle
	int longestPath();	// Returns the length of the longest path
	void displayPath();	// Displays the computed longest path
	
};
