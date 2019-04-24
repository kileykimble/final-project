//Testing In Sky function

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "graphs.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;


using namespace std;

Graph::Graph() {
	// should be empty
}

Graph::~Graph() {
	//
}

void Graph::addEdge(string v1, string v2) {
	findVertex(v1) -> Edges.push_back(findVertex(v2));
}
float findDistance(double x1, double y1, double x2, double y2){

	return sqrt((pow((x1-x2),2) + pow(((y1)-y2),2)));
}
void Graph::addVertex(string id, double x1, double y1, double x2, double y2){
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].id == id) {
			return;
		}
	}
	if(vertices.size() == 0){
		vertex insert;
		insert.id = id;
		insert.Distance = 0;
		vertices.push_back(insert);
	}
	else {
		vertex insert;
		insert.id = id;
		insert.Distance = findDistance(x1, y1, x2, y2);
		vertices.push_back(insert);
	}
}

void Graph::setAllVerticesUnvisited() {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].visited = false;
		for (int j = 0; j < vertices[i].Edges.size(); j++) {
			vertices[i].Edges[j]->visited = false;
		}
	}
}

vertex* Graph::findVertex(string id) {
	for (int i = 0; i < vertices.size(); i++) {
		if (id == vertices[i].id) {
			return &vertices[i];
		}
	}
	return nullptr; // if never found.
}
string Graph::findSeen(string id){
	string output = "You can see: \n";
	vertex* You = findVertex(id);
	int numSeen = 0;
	for(int i = 0; i < You -> Edges.size(); i++){
		if(You -> Edges.at(i) -> Distance < 90){
			output = output + You -> Edges.at(i) -> id + "\n";
			numSeen++;
		}
		else{ cout <<  You -> Edges.at(i) -> id << ":" << You -> Edges.at(i) -> Distance << endl;
		}
	}
	if(numSeen == 0){
		output = "Unfortunately you cannot see any planets.\n";
	}
	return output;
}
