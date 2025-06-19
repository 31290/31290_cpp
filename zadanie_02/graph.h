#include <vector>

struct Edge;

struct Coords
{
    int x;
    int y;
    Coords(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Node
{
    int id;
    Coords coords;
    std::vector<Edge> edges;

    void createEdge(Node *target);
    void removeEdge(Node *target);
    int getEdgeWeight(Node *target);
    int getEdgeWeight(Edge target);
    Edge *getSmallestEdge(int minWeight = 0);
    void resetEdges();
};

struct Edge
{
    Edge(Node *source, Node *target);
    Node *target;
    int weight;
    static int calculateWeight(Coords source, Coords target);
};

class Graph
{
private:
    Node* findNodeById(int id);
    Coords maxCoords;
    Coords minCoords;

public:
    std::vector<Node *> nodes;

    Graph();
    Graph(int nest);
    ~Graph();

    void createEdge(Node *source, Node *target);
    Node *createNode(int id = -1, Coords coords = Coords());
    Node *getNode(int id);
    void resetEdges();
};