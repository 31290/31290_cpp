#include "graph.h"
#include "SVGvisualizer.h"
#include "pathfinding.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>

DijkstraVisualizer::DijkstraVisualizer(Graph *g, SVGVisualizer *vis)
    : graph(g), visualizer(vis) {}

void DijkstraVisualizer::runDijkstra(int startId, int targetId)
{
    // Clear everything in case of multiple runs
    steps.clear();
    dijkstraData.clear();

    // Initialize all nodes
    for (Node *node : graph->nodes)
    {
        node->visited = false;
        dijkstraData[node->id] = DijkstraNode();
    }

    // Set start node and distance to 0
    Node *startNode = graph->getNode(startId);
    dijkstraData[startId].distance = 0;

    // Initialize priority queue with the start node
    std::priority_queue<PriorityQueueEntry, std::vector<PriorityQueueEntry>, std::greater<>> pq;
    pq.push({startNode, 0});
    dijkstraData[startId].inQueue = true;

    // Save initial state
    RenderState initialState;
    initialState.currentNode = startId;
    steps.push_back(initialState);

    // Run until priority queue is empty
    while (!pq.empty())
    {
        // Get the node with the smallest distance from the priority queue
        PriorityQueueEntry current = pq.top();
        pq.pop();

        Node *currentNode = current.node;
        dijkstraData[currentNode->id].inQueue = false;

        // Skip already visited
        if (currentNode->visited)
        {
            continue;
        }

        // Capture current state for visualization
        captureState(currentNode, pq);
        currentNode->visited = true;

        // Stop at target
        if (targetId != -1 && currentNode->id == targetId)
        {
            break;
        }

        // Process all neighbours
        for (Edge &edge : currentNode->edges)
        {
            Node *neighbour = edge.target;

            // Skip neighbour if it was already visited
            if (neighbour->visited)
                continue;

            // Calculate new possible distance to neighbour
            int newDistance = dijkstraData[currentNode->id].distance + edge.weight;

            // If shorter path available
            if (newDistance < dijkstraData[neighbour->id].distance)
            {
                dijkstraData[neighbour->id].distance = newDistance;
                dijkstraData[neighbour->id].previous = currentNode;

                // If neighbour is not already in the queue, add it
                if (!dijkstraData[neighbour->id].inQueue)
                {
                    pq.push({neighbour, newDistance});
                    dijkstraData[neighbour->id].inQueue = true;

                    // Capture state after updating neighbour
                    captureState(currentNode, pq);
                }
            }
        }
    }

    // Final state
    if (targetId != -1)
    {
        RenderState finalState;
        finalState.currentPath = reconstructPath(graph->getNode(targetId));

        // Mark all visited nodes
        for (Node *node : graph->nodes)
        {
            if (node->visited)
            {
                finalState.visitedNodes.push_back(node->id);
            }
        }
        steps.push_back(finalState);
    }
}

AStarVisualizer::AStarVisualizer(Graph *g, SVGVisualizer *vis, int heuristicType)
    : graph(g), visualizer(vis), targetNode(nullptr), heuristicType(heuristicType) {}

int AStarVisualizer::calculateHeuristic(Node *from, Node *to)
{
    int dx = to->coords.x - from->coords.x;
    int dy = to->coords.y - from->coords.y;

    switch (heuristicType)
    {
    case 0: // Pythagorean
        return static_cast<int>(sqrt(dx * dx + dy * dy));
    case 1: // Dot Product Heuristic (directional alignment)
    {
        // Vector from start to goal
        int gx = targetNode->coords.x - startNode->coords.x;
        int gy = targetNode->coords.y - startNode->coords.y;

        // Vector from current to goal
        int cx = to->coords.x - from->coords.x;
        int cy = to->coords.y - from->coords.y;

        int dot = gx * cx + gy * cy;

        // Normalize
        float magG = sqrt(gx * gx + gy * gy);
        float normalizedDot = (magG != 0) ? dot / magG : 0;

        return static_cast<int>(normalizedDot); // negative because higher dot is better (closer)
    }
    case 2: // Progress Factor (projected progress along goal direction)
    {
        int vx = targetNode->coords.x - startNode->coords.x;
        int vy = targetNode->coords.y - startNode->coords.y;
        int ux = to->coords.x - startNode->coords.x;
        int uy = to->coords.y - startNode->coords.y;

        float vMag = vx * vx + vy * vy;
        float projection = (vMag != 0) ? ((ux * vx + uy * vy) / static_cast<float>(vMag)) : 0.0f;

        return static_cast<int>(100 * projection); // scale for weight
    }
    case 3: // Manhattan distance (for grid-like graphs)
        return abs(dx) + abs(dy);
    case 4: // Chebyshev distance (for grid-like graphs)
        return std::max(abs(dx), abs(dy));
    default:
        return static_cast<int>(sqrt(dx * dx + dy * dy));
    }
}

void AStarVisualizer::runAStar(int startId, int targetId)
{
    // Clear everything in case of multiple runs
    steps.clear();
    astarData.clear();

    // Initiate the two earlier to calculate heuristic
    targetNode = graph->getNode(targetId);
    startNode = graph->getNode(startId);

    // Initialize all nodes
    for (Node *node : graph->nodes)
    {
        node->visited = false;
        astarData[node->id] = AStarNode();
        astarData[node->id].heuristic = calculateHeuristic(node, targetNode);
    }

    // Set distance and fScore for the start node
    astarData[startId].distance = 0;
    astarData[startId].fScore = astarData[startId].heuristic;

    // Initialize priority queue with the start node
    std::priority_queue<AStarPriorityEntry, std::vector<AStarPriorityEntry>, std::greater<>> pq;
    pq.push({startNode, astarData[startId].fScore});
    astarData[startId].inQueue = true;

    
    // Capture current state for visualization
    RenderState initialState;
    initialState.currentNode = startId;
    for (auto &pair : astarData)
    {
        if (pair.second.fScore != INT_MAX)
        {
            initialState.distances[pair.first] = pair.second.fScore;
        }
    }
    steps.push_back(initialState);

    while (!pq.empty())
    {
        AStarPriorityEntry current = pq.top();
        pq.pop();

        Node *currentNode = current.node;
        astarData[currentNode->id].inQueue = false;

        if (currentNode->visited)
        {
            continue;
        }

        captureState(currentNode, pq);
        currentNode->visited = true;

        // Stop at target
        if (currentNode->id == targetId)
        {
            break;
        }

        // Process all neighbours
        for (Edge &edge : currentNode->edges)
        {
            Node *neighbour = edge.target;


            if (neighbour->visited)
                continue;

            // Calculate tentative g(n) distance
            int tentativeG = astarData[currentNode->id].distance + edge.weight;


            // If shorter path available
            if (tentativeG < astarData[neighbour->id].distance)
            {
                astarData[neighbour->id].distance = tentativeG;
                astarData[neighbour->id].fScore = tentativeG + astarData[neighbour->id].heuristic;
                astarData[neighbour->id].previous = currentNode;

                // If neighbour is not already in the queue, add it
                if (!astarData[neighbour->id].inQueue)
                {
                    pq.push({neighbour, astarData[neighbour->id].fScore});
                    astarData[neighbour->id].inQueue = true;

                    // Capture state after updating neighbour for visualization
                    captureState(currentNode, pq);
                }
            }
        }
    }

    // Final state
    RenderState finalState;
    finalState.currentPath = reconstructPath(targetNode);

    for (Node *node : graph->nodes)
    {
        if (node->visited)
        {
            finalState.visitedNodes.push_back(node->id);
        }
    }
    steps.push_back(finalState);
}

int DijkstraVisualizer::getStepCount()
{
    return steps.size();
}

void DijkstraVisualizer::captureState(Node *current, const std::priority_queue<PriorityQueueEntry,
                                                                               std::vector<PriorityQueueEntry>, std::greater<>> &pq)
{
    RenderState state;
    state.currentNode = current->id;

    // Add all visited nodes (but NOT the current one yet)
    for (Node *node : graph->nodes)
    {
        if (node->visited && node->id != current->id)
        {
            state.visitedNodes.push_back(node->id);
        }
    }

    // Add nodes in priority queue
    auto pqCopy = pq;
    while (!pqCopy.empty())
    {
        Node *queueNode = pqCopy.top().node;
        pqCopy.pop();

        if (!queueNode->visited && queueNode->id != current->id)
        {
            state.queuedNodes.push_back(queueNode->id);
        }
    }

    // Add current distances
    for (auto &pair : dijkstraData)
    {
        if (pair.second.distance != INT_MAX)
        {
            state.distances[pair.first] = pair.second.distance;
        }
    }

    steps.push_back(state);
}

std::vector<int> DijkstraVisualizer::reconstructPath(Node *target)
{
    std::vector<int> path;
    Node *current = target;

    while (current != nullptr)
    {
        path.push_back(current->id);
        current = dijkstraData[current->id].previous;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> DijkstraVisualizer::getShortestPath(int startId, int targetId)
{
    return reconstructPath(graph->getNode(targetId)); // Returns the path from start to target
}

int DijkstraVisualizer::getShortestDistance(int startId, int targetId)
{
    return dijkstraData[targetId].distance; // Returns the distance from start to target
}

void DijkstraVisualizer::generateVisualization(const std::string &htmlFilename)
{
    visualizer->generateHTML(htmlFilename, steps);
}

// A* Implementation

void AStarVisualizer::captureState(Node *current, const std::priority_queue<AStarPriorityEntry,
                                                                            std::vector<AStarPriorityEntry>, std::greater<>> &pq)
{
    RenderState state;
    state.currentNode = current->id;

    for (Node *node : graph->nodes)
    {
        if (node->visited && node->id != current->id)
        {
            state.visitedNodes.push_back(node->id);
        }
    }

    auto pqCopy = pq;
    while (!pqCopy.empty())
    {
        Node *queueNode = pqCopy.top().node;
        pqCopy.pop();

        if (!queueNode->visited && queueNode->id != current->id)
        {
            state.queuedNodes.push_back(queueNode->id);
        }
    }

    for (auto &pair : astarData)
    {
        if (pair.second.fScore != INT_MAX)
        {
            state.distances[pair.first] = pair.second.fScore; // Show f-score
        }
    }

    steps.push_back(state);
}

std::vector<int> AStarVisualizer::reconstructPath(Node *target)
{
    std::vector<int> path;
    Node *current = target;

    while (current != nullptr)
    {
        path.push_back(current->id);
        current = astarData[current->id].previous;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> AStarVisualizer::getShortestPath(int startId, int targetId)
{
    return reconstructPath(graph->getNode(targetId)); // Returns the path from start to target
}

int AStarVisualizer::getShortestDistance(int startId, int targetId)
{
    return astarData[targetId].distance; // Retiurns the distance from start to target
}

void AStarVisualizer::generateVisualization(const std::string &htmlFilename)
{
    visualizer->generateHTML(htmlFilename, steps);
}

int AStarVisualizer::getStepCount()
{
    return steps.size();
}