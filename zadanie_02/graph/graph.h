#pragma once
#include <vector>

struct Node;

struct Coords
{
    int x;
    int y;
    Coords(int x = 0, int y = 0);
};

struct Edge
{
    Node *target;
    int weight;

    Edge(Node *source, Node *target);

    static int calculateWeight(Coords source, Coords target);
};

struct Node
{
    int id;
    Coords coords;
    bool visited = false;
    std::vector<Edge> edges;
    Node(int id = -1, Coords coords = Coords());
    Node(int id, int x, int y);

    void createEdge(Node *target);

    Edge *getEdge(Node *target);
    Edge *getSmallestEdge(int minWeight = 0, int count = 0);
    std::vector<Node*> getUnvisitedNeighbours();
};

class Graph
{
private:
    Coords maxCoords;
    Coords minCoords;

public:
    Node* findNodeById(int id);
    std::vector<Node *> nodes;

    Graph();
    Graph(int nest, int count, int y = 5, int x = 5);

    Node *createNode(int id = -1, Coords coords = Coords());
    Node *getNode(int id);
    
    void createEdge(Node *source, Node *target);
    void createEdge(int sourceID, int targetID);
    Edge *getEdge(Node *source, Node *target);

    void printGraph();
};