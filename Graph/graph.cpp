#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "graph.h"

using namespace std;

// Decoration

Decoration::Decoration(){
	visited = false;
	inStack = false;
}

// Vertex
Vertex::Vertex(){}

Vertex::Vertex(string str, int dur, int i){
	name = str;
	duration = dur;
	in = i;
}

string& Vertex::getName(){
	return name;
}

int Vertex::getDur(){
	return duration;
}

void Vertex::resetDecor(){
	decore.visited = false;
	decore.inStack = false;
	decore.inDeg = inDeg;
	decore.lp = duration;
	decore.lpList.clear();
	decore.lpList.push_back(this);
}

bool Vertex::isVisted(){
	return decore.visited;
}

bool Vertex::insideStack(){
	return decore.inStack;
}

// Edge

Edge::Edge(){}

Edge::Edge(Vertex *u, Vertex *v, int wt){
	start = u;
	end = v;
	weight = wt;
}

Vertex* Edge::getEnd(){
	return end;
}

Vertex* Edge::getBegin(){
	return start;
}


bool Graph::detectCycle(int start){

	if(vList[start]->isVisted() == false){
		vList[start]->decore.visited = true;
		vList[start]->decore.inStack = true;

		list<Edge*>::iterator it;
		for(it = adjList[start].begin();it!=adjList[start].end();++it){
			Vertex *next = (*it)->getEnd();

			if(next->isVisted() == false && detectCycle(next->in)) return true;
			else if(next->decore.inStack == true) return true;

		}
	}

	vList[start]->decore.inStack = false;
	return false;

}

Graph::Graph(){
	nV = 0;
	nE = 0;
}

void Graph::insertVertex(string str, int dur){
	// Adds a vertex into the vertex list and map
	Vertex *toAdd = new Vertex(str,dur,nV);
	vList.push_back(toAdd);
	vertex[str] = toAdd;
	nV++;
}

void Graph::insertEdge(string p1, string p2){
	// Adds an Edge from p1 to p2
	if(adjList.size()!=nV) adjList.resize(nV);

	Vertex *a = vertex[p1];
	Vertex *b = vertex[p2];

	Edge *newE = new Edge(a,b);
	adjList[a->in].push_back(newE);
	b->inDeg +=1;
	nE++;

}

bool Graph::isCycle(){
	// Returns true if cycle exists

	for(int i=0;i<vList.size();i++){
		// Visited is false;
		vList[i]->resetDecor();
	}

	// Since only one DFS Tree is present
	return detectCycle(0);
}

int Graph::longestPath(){

	for(int i=0;i<vList.size();i++){
		// Visited is false;
		vList[i]->resetDecor();
	}

	queue<Vertex*> q;
	q.push(vList[0]);	// First item

	while(!q.empty()){
		// Topological Sort
		Vertex *front = q.front();
		q.pop();

		int i = front->in;

		list<Edge*>::iterator it;
		for(it = adjList[i].begin();it!=adjList[i].end();++it){
			Vertex *next = (*it)->getEnd();
			next->decore.inDeg -=1;

			if(next->decore.lp < (next->duration + front->decore.lp)){
				next->decore.lp = next->duration + front->decore.lp;
				next->decore.lpList = front->decore.lpList;
				next->decore.lpList.push_back(next);
			}
			if(next->decore.inDeg == 0) q.push(next);
		}
	}

	return vList[nV-1]->decore.lp;
}

void Graph::displayPath(){

	vector<Vertex *> v = vList[nV-1]->decore.lpList;
	for(int i=0;i<v.size();i++){
		cout<<v[i]->getName()<<" ";
	}
	cout<<endl;
}
