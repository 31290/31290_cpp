#include "graph.h"
#include "SVGvisualizer.h"
#include "pathfinding.h"
#include <iostream>

#define NEST 4
#define COUNT 5
#define HEURISTIC 5

std::string getHeuristic(int i)
{
    switch (i)
    {
    case 0:
        return "Pythagorean";
    case 1:
        return "Dot_Product";
    case 2:
        return "Progress_Factor";
    case 3:
        return "Manhattan";
    case 4:
        return "Chebyshev";
    default:
        return "Pythagorean";
    }
}

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    Graph graph(NEST, COUNT, 120, 120);

    if (argc > 1)
    {
        Coords coords = {-strtol(argv[1], nullptr, 10), -strtol(argv[1], nullptr, 10)};
        Node *bypass = graph.createNode(graph.nodes.size(), coords);
        bypass->createEdge(graph.findNodeById(0));
        bypass->createEdge(graph.findNodeById(NEST * (COUNT + 1) - 1));
    }
    /**/

    for (Node *node : graph.nodes)
    {
        node->coords.x += 100;
        node->coords.y += 100;
    }

    SVGVisualizer visualizer(&graph);

    std::cout << "Graph created with " << graph.nodes.size() << " nodes\n";
    std::cout << "\n\n";

    RenderState staticState = {0};
    visualizer.generateSVG("graph.svg", staticState);
    std::cout << "Generated static graph.svg\n";

    int startNode = 0;
    int targetNode = NEST * (COUNT + 1) - 1;

    DijkstraVisualizer dijkstra(&graph, &visualizer);

    std::cout << "Running Dijkstra from node " << startNode << " to node " << targetNode << "\n";
    dijkstra.runDijkstra(startNode, targetNode);
    dijkstra.generateVisualization("pathfinding_dijkstra.html");
    std::cout << "Generated pathfinding_dijkstra.html\n";

    std::vector<int> dijkstraPath = dijkstra.getShortestPath(startNode, targetNode);
    int dijkstraDistance = dijkstra.getShortestDistance(startNode, targetNode);

    std::cout << "Dijkstra shortest path from " << startNode << " to " << targetNode << ":\n";
    for (size_t i = 0; i < dijkstraPath.size(); ++i)
    {
        std::cout << dijkstraPath[i];
        if (i < dijkstraPath.size() - 1)
            std::cout << " -> ";
    }
    std::cout << "\nTotal distance: " << dijkstraDistance << "\n\n";

    int astarDistance[HEURISTIC];
    std::vector<int> astarPath[HEURISTIC];
    int astarStep[HEURISTIC];

    for (int heuristicType = 0; heuristicType < HEURISTIC; ++heuristicType)
    {
        std::cout << "Running A* (heuristic " << getHeuristic(heuristicType) << ") from node " << startNode << " to node " << targetNode << "\n";

        AStarVisualizer astar(&graph, &visualizer, heuristicType);
        astar.runAStar(startNode, targetNode);

        std::string filename = "pathfinding_astar_" + getHeuristic(heuristicType) + ".html";
        astar.generateVisualization(filename.c_str());
        std::cout << "Generated " << filename << "\n";

        astarPath[heuristicType] = astar.getShortestPath(startNode, targetNode);
        astarDistance[heuristicType] = astar.getShortestDistance(startNode, targetNode);
        astarStep[heuristicType] = astar.getStepCount();

        std::cout << "A* shortest path (heuristic " << heuristicType << "): ";
        for (size_t i = 0; i < astarPath[heuristicType].size(); ++i)
        {
            std::cout << astarPath[heuristicType][i];
            if (i < astarPath[heuristicType].size() - 1)
                std::cout << " -> ";
        }
        std::cout << "\nTotal distance: " << astarDistance[heuristicType] << "\n\n";
    }

    std::cout << "Algorithm comparison:\n";
    std::cout << "Dijkstra - Distance: " << dijkstraDistance << ", Path length: " << dijkstraPath.size() << ", steps: " << dijkstra.getStepCount() << "\n";
    for (int i = 0; i < HEURISTIC; i++)
    {
        std::cout << "A* " << getHeuristic(i) << " - Distance: " << astarDistance[i] << ", Path length: " << astarPath[i].size() << ", steps: " << astarStep[i] << "\n";
    }

    for (int i = 0; i < HEURISTIC; i++)
    {
        if (dijkstraDistance == astarDistance[i])
        {
            std::cout << getHeuristic(i) << " found the same optimal distance!\n";
        }
        else
        {
            std::cout << "The " << getHeuristic(i) << " Heuristic failed!\n";
        }
    }
    return 0;
}