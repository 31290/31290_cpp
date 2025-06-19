#include "graph.h"
#include "SVGvisualizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

// Example usage in main.cpp
int main()
{
    srand(time(nullptr));
    Graph graph(6, 8, 120, 120);

    for (Node *node : graph.nodes)
    {
        node->coords.x += 100;
        node->coords.y += 100;
    }

    SVGVisualizer visualizer(&graph);

    std::cout << "Generating SVG visualization...\n";

    visualizer.generateSVG("graph.svg");

/*
    // Example pathfinding visualization data
    std::vector<std::vector<int>> pathSteps = {
        {},          // Step 0: no path
        {0},         // Step 1: start at node 0
        {0, 1},      // Step 2: path to node 1
        {0, 1, 2},   // Step 3: path to node 2
        {0, 1, 2, 3} // Step 4: path to node 3
    };

    std::vector<std::vector<int>> visitedSteps = {
        {},                // Step 0: no visited
        {0},               // Step 1: visited node 0
        {0, 1},            // Step 2: visited nodes 0, 1
        {0, 1, 2, 3},      // Step 3: visited nodes 0, 1, 2, 3
        {0, 1, 2, 3, 4} // Step 4: more visited nodes
    };

    std::vector<int> currentNodes = {0, 1, 2, 3, 4}; // Current node being processed

    visualizer.generateHTML("pathfinding.html", pathSteps, visitedSteps, currentNodes);
    std::cout << "Generated graph.svg and pathfinding.html\n";
    std::cout << "Open pathfinding.html in your browser to see the interactive visualization\n";
/**/
    return 0;
}