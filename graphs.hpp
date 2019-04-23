


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

using namespace std;
struct vertex;


/*this is the struct for each vertex in the graph. */
struct vertex
{
    string id;
    bool visited;
    vector<vertex*> Edges;
    double Distance; //stores edges to adjacent vertices
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addEdge(string v1, string v2);
    void addVertex(string id, double x1, double y1, double x2, double y2);
    void setAllVerticesUnvisited();
    string findSeen(string id);
  private:
    std::vector<vertex> vertices;
    vertex *findVertex(string id);
};

#endif // GRAPH_HPP
