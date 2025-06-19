#include "graph.h"
#include "SVGvisualizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

int main()
{
    srand(time(nullptr));
    Graph graph(6, 8, 120, 120);

    for (Node *node : graph.nodes)
    {
        node->coords.x += 100;
        node->coords.y += 100;
    }

    RenderState currentState;

    SVGVisualizer visualizer(&graph);

    std::cout << "Generating SVG visualization...\n";

    visualizer.generateSVG("graph.svg", currentState);
    
    // visualizer.generateHTML("pathfinding.html", path);
    std::cout << "Generated graph.svg and pathfinding.html\n";
    std::cout << "Open pathfinding.html in your browser to see the interactive visualization\n";
/**/
    return 0;
}