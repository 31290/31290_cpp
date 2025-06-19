#include "graph.h"
#include <iostream>
#include <cmath>

Coords::Coords(int x, int y) : x(x), y(y) {}

int Edge::calculateWeight(Coords source, Coords target)
{
    int dx = target.x - source.x;
    int dy = target.y - source.y;
    return static_cast<int>(sqrt(dx * dx + dy * dy));
}

Edge::Edge(Node *source, Node *target) : target(target)
{
    weight = calculateWeight(source->coords, target->coords);
}

Node::Node(int id, Coords coords) : id(id), coords(coords) {}
Node::Node(int id, int x, int y) : id(id), coords(x, y) {}

void Node::createEdge(Node *target)
{
    edges.emplace_back(this, target);
    target->edges.emplace_back(target, this);
}

Edge *Node::getEdge(Node *target)
{
    for (Edge &edge : edges)
    {
        if (edge.target == target)
        {
            return &edge;
        }
    }
    throw "Edge not found";
}

Edge *Node::getSmallestEdge(int minWeight, int count)
{
    Edge *smallest = nullptr;
    int small = __INT_MAX__;
    for (Edge &edge : edges)
    {
        if (edge.weight < minWeight)
            continue;
        if (edge.weight <= small)
        {
            if (edge.weight == minWeight && count > 0)
            {
                count--;
                continue;
            }
            smallest = &edge;
            small = smallest->weight;
        }
    }
    return smallest;
}

std::vector<Node*> Node::getUnvisitedNeighbours()
{
    std::vector<Node*> unvisited;
    for (Edge &edge : edges)
    {
        if (!edge.target->visited)
        {
            unvisited.push_back(edge.target);
        }
    }
    return unvisited;
}

Graph::Graph() {}

Graph::Graph(int nest, int count, int y, int x)
{
    count++;
    for (int i = 0; i < nest; ++i)
    {
        for(int j = 0; j < count; ++j)
        {
            std::cout << "Creating node at (" << j * x << ", " << i * y << ")\n";
            int id = i * count + j;
            Coords coords(j * x, i * y);
            Node *node = createNode(id, coords);
            if (i > 0)
            {
                std::cout << "Connecting node " << id << " to node " << (i - 1) * count + j << "\n";
                createEdge(node, findNodeById((i - 1) * count + j));
            }
            if (j > 0)
            {
                std::cout << "Connecting node " << id << " to node " << i * count + (j - 1) << "\n";
                createEdge(node, findNodeById(i * count + (j - 1)));
            }
        }
    }
}

Node* Graph::findNodeById(int id)
{
    for (Node *node : nodes)
    {
        if (node->id == id)
        {
            return node;
        }
    }
    throw "Node not found";
}

Node *Graph::createNode(int id, Coords coords)
{
    Node *node = new Node(id, coords);
    nodes.push_back(node);
    return node;
}

Node *Graph::getNode(int id)
{
    return findNodeById(id);
}

void Graph::createEdge(Node *source, Node *target)
{
    source->createEdge(target);
}

Edge *Graph::getEdge(Node *source, Node *target)
{
    return source->getEdge(target);
}

void Graph::printGraph()
{
    for (Node *node : nodes)
    {
        std::cout << "Node " << node->id << " at (" << node->coords.x << ", " << node->coords.y << ") edges:\n";
        for (Edge &edge : node->edges)
        {
            std::cout << "  to Node " << edge.target->id << " with weight " << edge.weight << "\n";
        }
    }
}