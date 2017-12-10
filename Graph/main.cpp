#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "graph.h"

using namespace std;

int main(){
	Graph G;
	fstream fin;
	fin.open("courses.txt", ios::in);
	string course;
	int duration;
	while(!fin.eof()){
		fin>>course>>duration;
		G.insertVertex(course,duration);
	}
	fin.close();
	fin.open("dependencies.txt", ios::in);
	string c1,c2;
	while(!fin.eof()){
		fin>>c1>>c2;
		G.insertEdge(c1,c2);
	}

	if(!G.isCycle()){
		int duration = G.longestPath();
		cout<<"Longest Path is ";
		G.displayPath();
		cout<<"Duration is "<<duration<<endl;
	}
	else{
		cout<<"Not a DAG"<<endl;
	}
}