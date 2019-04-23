//Testing In Sky function

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "graphs.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


struct planetLocation{

	double longitude;
	double inclination;
};

enum {Mercury, Venus, Mars, Jupiter, Saturn, Uranus, Neptune};

planetLocation planetArr[7];


void calcMercury(int d){

    planetArr[Mercury].longitude =  48.3313 + 3.24587E-5 * d;
    planetArr[Mercury].inclination = 7.0047 + 5.00E-8 * d;
}

void calcVenus(int d){

    planetArr[Venus].longitude =  76.6799 + 2.46590E-5 * d;
    planetArr[Venus].inclination = 3.3946 + 2.75E-8 * d;
}

void calcMars(int d){

    planetArr[Mars].longitude =  49.5574 + 2.11081E-5 * d;
    planetArr[Mars].inclination = 1.8497 - 1.78E-8 * d;
}

void calcJupiter(int d){

    planetArr[Jupiter].longitude =  100.4542 + 2.76854E-5 * d;
    planetArr[Jupiter].inclination = 1.3030 - 1.557E-7 * d;
}

void calcSaturn(int d){

    planetArr[Saturn].longitude =  113.6634 + 2.38980E-5 * d;
    planetArr[Saturn].inclination = 2.4886 - 1.081E-7 * d;
}

void calcUranus(int d){

    planetArr[Uranus].longitude =  74.0005 + 1.3978E-5 * d;
    planetArr[Uranus].inclination = 0.7733 + 1.9E-8 * d;
}

void calcNeptune(int d){

    planetArr[Neptune].longitude =  131.7806 + 3.0173E-5 * d;
    planetArr[Neptune].inclination = 1.7700 - 2.55E-7 * d;
}

 planetLocation* nightSkyCoordinates(string date){ // using data from http://www.stjarnhimlen.se/comp/ppcomp.html
	string token;
	int day;
	int month;
	int year;
	int d;

  	istringstream iss(date);

 	getline(iss, token, '/');
  	month = stoi(token);
  	getline(iss, token, '/');
  	day = stoi(token);
  	getline(iss, token, '/');
  	year = stoi(token);

	d = (367*year - 7) * (year + (month+9)/12 ) / 4 + (275*month/9) + day - 730530;
	calcMercury(d);
	calcVenus(d);
	calcMars(d);
	calcJupiter(d);
	calcSaturn(d);
	calcUranus(d);
	calcNeptune(d);
	return planetArr;
}
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
		else{ cout << output + You -> Edges.at(i) -> id << ":" << You -> Edges.at(i) -> Distance << endl;
		}
	}
	if(numSeen == 0){
		output = "Unfortunately you cannot see any planets.\n";
	}
	return output;
}
int main(){
	planetLocation *pl;
	string date;
	string lats;
	string longs;
	double lat;
	double longi;
	cout << "Please enter the date for which you would like to see the night sky (mm/dd/yyyy): " << endl;
	getline(cin, date);
	pl = nightSkyCoordinates(date);
	cout << "Please enter Latitude" << endl;
	getline(cin, lats);
	cout << "Please enter Longitude" << endl;
	getline(cin, longs);
	lat = stod(lats);
	longi = stod(longs);
	Graph g = Graph();
	g.addVertex("me", 0, 0, 0, 0);
	cout << "Mercury " << "Lat : "  << pl[0].inclination*.5 << "Long" << pl[0].longitude;
	g.addVertex("Mercury", lat, longi, pl[0].inclination*.5, fmod(pl[0].longitude, 90));
	g.addVertex("Venus", lat, longi, pl[1].inclination*.5, fmod(pl[0].longitude, 90));
	g.addVertex("Mars", lat, longi, pl[2].inclination*.5, fmod(pl[0].longitude, 90));
	g.addVertex("Jupiter", lat, longi, pl[3].inclination*.5, fmod(pl[0].longitude, 90));
	g.addVertex("Saturn", lat, longi, pl[4].inclination*.5,fmod(pl[0].longitude, 90));
	g.addVertex("Uranus", lat, longi, pl[5].inclination*.5, fmod(pl[0].longitude, 90));
	g.addVertex("Neptune", lat, longi, pl[6].inclination*.5, fmod(pl[0].longitude, 90));
	g.addEdge("me", "Mercury");
	g.addEdge("me", "Venus");
	g.addEdge("me", "Mars");
	g.addEdge("me", "Jupiter");
	g.addEdge("me", "Saturn");
	g.addEdge("me", "Uranus");
	g.addEdge("me", "Neptune");
	cout << g.findSeen("me");

}
