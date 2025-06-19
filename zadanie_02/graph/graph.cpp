#include "graph.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

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

std::vector<Node *> Node::getUnvisitedNeighbours()
{
    std::vector<Node *> unvisited;
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
        for (int j = 0; j < count; ++j)
        {
            int id = i * count + j;
            Coords coords(j * (x - 1) + rand() % x + 1, i * (y - 1) + rand() % y + 1);
            Node *node = createNode(id, coords);
            if (i > 0)
            {
                createEdge(node, findNodeById((i - 1) * count + j));
            }
            if (j > 0)
            {
                createEdge(node, findNodeById(i * count + (j - 1)));
            }
        }
    }

    int totalNodes = nest * count;
    // std::cout << "Total node count: " << totalNodes << "\n";
    int extraConnections = std::max(1, totalNodes / 8); // ~12.5% of nodes get extra connections

    for (int i = 0; i < extraConnections; ++i)
    {
        Node *source = nodes[rand() % totalNodes];
        Node *target = nodes[rand() % totalNodes];

        // Don't connect to self or already connected nodes
        if (source == target)
            target++;

        bool alreadyConnected = false;
        for (Edge &edge : source->edges)
        {
            if (edge.target == target)
            {
                alreadyConnected = true;
                break;
            }
        }

        if (!alreadyConnected)
        {
            createEdge(source, target);
        }
    }
}

Node *Graph::findNodeById(int id)
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

void Graph::createEdge(int sourceID, int targetID)
{
    Node *source = getNode(sourceID);
    Node *target = getNode(targetID);
    if (source && target)
    {
        source->createEdge(target);
    }
    else
    {
        throw "Source or target node not found";
    }
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
            std::cout << "  to Node " << edge.target->id << " at (" << edge.target->coords.x << ", " << edge.target->coords.y << ") with weight " << edge.weight << "\n";
        }
    }
}