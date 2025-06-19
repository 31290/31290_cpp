#pragma once
#include "graph.h"
#include "SVGvisualizer.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

struct AStarNode
{
    int distance;  // g(n) - actual distance from start
    int heuristic; // h(n) - heuristic to target
    int fScore;    // f(n) = g(n) + h(n)
    Node *previous;
    bool inQueue;

    AStarNode() : distance(INT_MAX), heuristic(0), fScore(INT_MAX), previous(nullptr), inQueue(false) {}
};

struct AStarPriorityEntry
{
    Node *node;
    int fScore;

    bool operator>(const AStarPriorityEntry &other) const
    {
        return fScore > other.fScore;
    }
};

class AStarVisualizer
{
private:
    Graph *graph;
    SVGVisualizer *visualizer;
    std::vector<RenderState> steps;
    std::unordered_map<int, AStarNode> astarData;
    Node *targetNode;
    Node *startNode;
    int heuristicType; // 0: Pythagorean, 1: Dot Product, 2: Progress Factor

    int calculateHeuristic(Node *from, Node *to);
    void captureState(Node *current, const std::priority_queue<AStarPriorityEntry,
                                                               std::vector<AStarPriorityEntry>, std::greater<>> &pq);
    std::vector<int> reconstructPath(Node *target);

public:
    AStarVisualizer(Graph *g, SVGVisualizer *vis, int heuristicType = 0);

    int calculatePathDistance(const std::vector<int> &path);
    void runAStar(int startId, int targetId);
    void generateVisualization(const std::string &htmlFilename);

    std::vector<int> getShortestPath(int startId, int targetId);
    int getShortestDistance(int startId, int targetId);
};

struct DijkstraNode
{
    int distance;
    Node *previous;
    bool inQueue;

    DijkstraNode() : distance(INT_MAX), previous(nullptr), inQueue(false) {}
};

struct PriorityQueueEntry
{
    Node *node;
    int distance;

    bool operator>(const PriorityQueueEntry &other) const
    {
        return distance > other.distance;
    }
};

class DijkstraVisualizer
{
private:
    Graph *graph;
    SVGVisualizer *visualizer;
    std::vector<RenderState> steps;
    std::unordered_map<int, DijkstraNode> dijkstraData;

    void captureState(Node *current, const std::priority_queue<PriorityQueueEntry,
                                                               std::vector<PriorityQueueEntry>, std::greater<>> &pq);
    std::vector<int> reconstructPath(Node *target);

public:
    DijkstraVisualizer(Graph *g, SVGVisualizer *vis);

    int calculatePathDistance(const std::vector<int> &path);
    void runDijkstra(int startId, int targetId = -1);
    void generateVisualization(const std::string &htmlFilename);

    // Get shortest path between two nodes
    std::vector<int> getShortestPath(int startId, int targetId);
    int getShortestDistance(int startId, int targetId);
};