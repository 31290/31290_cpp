#include "graph.h"
#include "SVGvisualizer.h"
#include "pathfinding.h"
#include <iostream>

#define NEST 4
#define COUNT 5

int main()
{
    srand(time(nullptr));
    Graph graph(NEST, COUNT, 120, 120);

/*
    Node* bypass = graph.createNode(graph.nodes.size(), Coords(-5, -5));
    bypass->createEdge(graph.findNodeById(0));
    bypass->createEdge(graph.findNodeById(NEST*(COUNT+1)-1));
/**/    


    for (Node *node : graph.nodes)
    {
        node->coords.x += 100;
        node->coords.y += 100;
    }

    SVGVisualizer visualizer(&graph);
    DijkstraVisualizer dijkstra(&graph, &visualizer);

    std::cout << "Graph created with " << graph.nodes.size() << " nodes\n";
    std::cout << "\n\n";

    RenderState staticState = { 0 };
    visualizer.generateSVG("graph.svg", staticState);
    std::cout << "Generated static graph.svg\n";

    int startNode = 0;
    int targetNode = NEST*(COUNT+1)-1;
    
    std::cout << "Running Dijkstra from node " << startNode << " to node " << targetNode << "\n";
    
    dijkstra.runDijkstra(startNode, targetNode);
    dijkstra.generateVisualization("pathfinding_dijkstra.html");

    std::cout << "Generated pathfinding_dijkstra.html\n";

    // Show shortest path and distance
    std::vector<int> shortestPath = dijkstra.getShortestPath(startNode, targetNode);
    int shortestDistance = dijkstra.getShortestDistance(startNode, targetNode);
    
    std::cout << "Shortest path from " << startNode << " to " << targetNode << ":\n";
    for (size_t i = 0; i < shortestPath.size(); ++i) {
        std::cout << shortestPath[i];
        if (i < shortestPath.size() - 1) std::cout << " -> ";
    }
    std::cout << "\nTotal distance: " << shortestDistance << "\n";
    
    std::cout << "\nOpen dijkstra_visualization.html in your browser to see the step-by-step visualization\n";
    
/*
    // visualizer.generateHTML("pathfinding.html", path);
    std::cout << "Generated graph.svg and pathfinding.html\n";
    std::cout << "Open pathfinding.html in your browser to see the interactive visualization\n";
/**/
    return 0;
}