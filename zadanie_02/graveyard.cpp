/*
#include "graph.h"
#include <iostream>

int main()
{
    srand(time(nullptr));

    try
    {
        Graph graph(5);
        graph.printGraph();
    }
    catch (const char *e)
    {
        std::cerr << "Error: " << e << std::endl;
    }

    return 0;
}
/**/

/*
#include "graph.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class GraphVisualizer {
private:
    sf::RenderWindow window;
    Graph* graph;
    float nodeRadius = 15.0f;
    sf::Font font;
    
public:
    GraphVisualizer(Graph* g, int width = 800, int height = 600) 
        : window(sf::VideoMode(width, height), "Graph Visualization"), graph(g) {
        // Try to load a font - SFML usually has a default font path
        if (!font.loadFromFile("/System/Library/Fonts/Arial.ttf") && // macOS
            !font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") && // Linux
            !font.loadFromFile("C:/Windows/Fonts/arial.ttf")) { // Windows
            std::cout << "Warning: Could not load font, text may not display\n";
        }
    }
    
    void run() {
        while (window.isOpen()) {
            handleEvents();
            render();
        }
    }
    
private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    
    void render() {
        window.clear(sf::Color::Black);
        
        // Draw edges first (so they appear behind nodes)
        drawEdges();
        
        // Draw nodes on top
        drawNodes();
        
        window.display();
    }
    
    void drawNodes() {
        for (Node* node : graph->nodes) {
            // Create circle for node
            sf::CircleShape circle(nodeRadius);
            circle.setPosition(node->coords.x - nodeRadius, node->coords.y - nodeRadius);
            
            // Color based on visited status
            if (node->visited) {
                circle.setFillColor(sf::Color::Blue);
            } else {
                circle.setFillColor(sf::Color::White);
            }
            circle.setOutlineThickness(2);
            circle.setOutlineColor(sf::Color::Black);
            
            window.draw(circle);
            
            // Draw node ID
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(node->id));
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Black);
            
            // Center text on node
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setPosition(
                node->coords.x - textBounds.width / 2,
                node->coords.y - textBounds.height / 2
            );
            
            window.draw(text);
        }
    }
    
    void drawEdges() {
        for (Node* node : graph->nodes) {
            for (Edge& edge : node->edges) {
                // Only draw each edge once (avoid duplicates)
                if (node->id < edge.target->id) {
                    drawEdge(node, edge.target, edge.weight);
                }
            }
        }
    }
    
    void drawEdge(Node* from, Node* to, int weight) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(from->coords.x, from->coords.y), sf::Color::White),
            sf::Vertex(sf::Vector2f(to->coords.x, to->coords.y), sf::Color::White)
        };
        
        window.draw(line, 2, sf::Lines);
        
        // Draw weight label
        float midX = (from->coords.x + to->coords.x) / 2.0f;
        float midY = (from->coords.y + to->coords.y) / 2.0f;
        
        sf::Text weightText;
        weightText.setFont(font);
        weightText.setString(std::to_string(weight));
        weightText.setCharacterSize(10);
        weightText.setFillColor(sf::Color::Yellow);
        weightText.setPosition(midX, midY);
        
        window.draw(weightText);
    }
};

// Modified main.cpp
int main() {
    // Create graph with better spacing for visualization
    Graph graph(5, 5, 100, 100); // 5x5 grid, 100px spacing
    
    // Offset the entire graph to center it better in window
    for (Node* node : graph.nodes) {
        node->coords.x += 50;
        node->coords.y += 50;
    }
    
    GraphVisualizer visualizer(&graph);
    visualizer.run();
    
    return 0;
}

/**/

/*

//h

#include "graph.h"
#include <string>

class SVGVisualizer
{
private:
    Graph *graph;
    int width, height;
    int nodeRadius = 15;
    int padding = 50;

    void calculateDimensions();

public:
    SVGVisualizer(Graph *g);

    void generateSVG(const std::string &filename, const std::vector<int> &visitedNodes = {}, const std::vector<int> &currentPath = {}, int currentNode = -1);
    void generateHTML(const std::string &filename, const std::vector<std::vector<int>> &pathfindingSteps, const std::vector<std::vector<int>> &visitedSteps, const std::vector<int> &currentNodes);

private:
    void drawEdges(std::ofstream &file, const std::vector<int> &currentPath);
    void drawEdgesHTML(std::ofstream &file, const std::vector<int> &currentPath);
    void drawNodes(std::ofstream &file, const std::vector<int> &visitedNodes, const std::vector<int> &currentPath, int currentNode);
    void drawNodesHTML(std::ofstream &file, const std::vector<int> &visitedNodes, const std::vector<int> &currentPath, int currentNode);
    std::string getNodeClass(int nodeId, const std::vector<int> &visitedNodes, const std::vector<int> &currentPath, int currentNode);
    bool isEdgeInPath(int from, int to, const std::vector<int> &path);

};


//cpp

#include "SVGVisualizer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graph.h"

void SVGVisualizer::calculateDimensions()
{
    if (graph->nodes.empty())
    {
        width = 400;
        height = 400;
        return;
    }

    int minX = graph->nodes[0]->coords.x;
    int maxX = graph->nodes[0]->coords.x;
    int minY = graph->nodes[0]->coords.y;
    int maxY = graph->nodes[0]->coords.y;

    for (Node *node : graph->nodes)
    {
        minX = std::min(minX, node->coords.x);
        maxX = std::max(maxX, node->coords.x);
        minY = std::min(minY, node->coords.y);
        maxY = std::max(maxY, node->coords.y);
    }

    width = maxX - minX + 2 * (padding + nodeRadius);
    height = maxY - minY + 2 * (padding + nodeRadius);

    // Center the graph by adjusting all node coordinates
    int offsetX = padding + nodeRadius - minX;
    int offsetY = padding + nodeRadius - minY;

    for (Node *node : graph->nodes)
    {
        node->coords.x += offsetX;
        node->coords.y += offsetY;
    }
}

SVGVisualizer::SVGVisualizer(Graph *g) : graph(g)
{
    calculateDimensions();
}

void SVGVisualizer::generateSVG(const std::string &filename, const std::vector<int> &visitedNodes,
                                const std::vector<int> &currentPath, int currentNode)
{

    std::remove(filename.c_str());
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    else
    {
        std::cout << "Successfully opened file: " << filename << std::endl;
    }

    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    file << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    file << "<style>\n";
    file << ".node-unvisited { fill: white; stroke: black; stroke-width: 2; }\n";
    file << ".node-visited { fill: lightblue; stroke: black; stroke-width: 2; }\n";
    file << ".node-current { fill: yellow; stroke: black; stroke-width: 3; }\n";
    file << ".node-path { fill: lightgreen; stroke: black; stroke-width: 2; }\n";
    file << ".edge { stroke: gray; stroke-width: 1; }\n";
    file << ".edge-path { stroke: red; stroke-width: 3; }\n";
    file << ".text { font-family: Arial; font-size: 12px; text-anchor: middle; }\n";
    file << ".weight-text { font-family: Arial; font-size: 10px; text-anchor: middle; fill: blue; }\n";
    file << "</style>\n";

    std::cout << "Drawing edges...\n";
    // Draw edges first
    drawEdges(file, currentPath);

    std::cout << "Drawing nodes...\n";
    // Draw nodes on top
    drawNodes(file, visitedNodes, currentPath, currentNode);

    file << "</svg>\n";
    file.close();
}

void SVGVisualizer::generateHTML(const std::string &filename, const std::vector<std::vector<int>> &pathfindingSteps,
                                 const std::vector<std::vector<int>> &visitedSteps, const std::vector<int> &currentNodes)
{
    std::ofstream file(filename);

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<title>Graph Pathfinding Visualization</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial; margin: 20px; }\n";
    file << ".controls { margin: 20px 0; }\n";
    file << "button { margin: 5px; padding: 10px; font-size: 14px; }\n";
    file << "#info { margin: 10px 0; font-weight: bold; }\n";
    file << "</style>\n";
    file << "</head>\n<body>\n";
    file << "<h1>Graph Pathfinding Visualization</h1>\n";
    file << "<div class=\"controls\">\n";
    file << "<button onclick=\"prevStep()\">Previous</button>\n";
    file << "<button onclick=\"nextStep()\">Next</button>\n";
    file << "<button onclick=\"reset()\">Reset</button>\n";
    file << "</div>\n";
    file << "<div id=\"info\">Step: <span id=\"stepCounter\">0</span> / " << pathfindingSteps.size() - 1 << "</div>\n";

    // Generate SVG for each step
    for (int i = 0; i < pathfindingSteps.size(); ++i)
    {
        file << "<svg id=\"step" << i << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"display:" << (i == 0 ? "block" : "none") << ";border:1px solid #ccc;\">\n";

        file << "<style>\n";
        file << ".node-unvisited { fill: white; stroke: black; stroke-width: 2; }\n";
        file << ".node-visited { fill: lightblue; stroke: black; stroke-width: 2; }\n";
        file << ".node-current { fill: yellow; stroke: black; stroke-width: 3; }\n";
        file << ".node-path { fill: lightgreen; stroke: black; stroke-width: 2; }\n";
        file << ".edge { stroke: gray; stroke-width: 1; }\n";
        file << ".edge-path { stroke: red; stroke-width: 3; }\n";
        file << ".text { font-family: Arial; font-size: 12px; text-anchor: middle; }\n";
        file << ".weight-text { font-family: Arial; font-size: 10px; text-anchor: middle; fill: blue; }\n";
        file << "</style>\n";

        drawEdges(file, pathfindingSteps[i]);
        drawNodes(file, visitedSteps[i], pathfindingSteps[i], i < currentNodes.size() ? currentNodes[i] : -1);

        file << "</svg>\n";
    }

    file << "\n<script>\n";
    file << "let currentStep = 0;\n";
    file << "const totalSteps = " << pathfindingSteps.size() << ";\n";
    file << "let autoInterval = null;\n\n";

    file << "function showStep(step) {\n";
    file << "  for (let i = 0; i < totalSteps; i++) {\n";
    file << "    document.getElementById('step' + i).style.display = 'none';\n";
    file << "  }\n";
    file << "  document.getElementById('step' + step).style.display = 'block';\n";
    file << "  document.getElementById('stepCounter').textContent = step;\n";
    file << "}\n\n";

    file << "function nextStep() {\n";
    file << "  if (currentStep < totalSteps - 1) {\n";
    file << "    currentStep++;\n";
    file << "    showStep(currentStep);\n";
    file << "  }\n";
    file << "}\n\n";

    file << "function prevStep() {\n";
    file << "  if (currentStep > 0) {\n";
    file << "    currentStep--;\n";
    file << "    showStep(currentStep);\n";
    file << "  }\n";
    file << "}\n\n";

    file << "function autoPlay() {\n";
    file << "  if (autoInterval) {\n";
    file << "    clearInterval(autoInterval);\n";
    file << "    autoInterval = null;\n";
    file << "  } else {\n";
    file << "    autoInterval = setInterval(() => {\n";
    file << "      if (currentStep < totalSteps - 1) {\n";
    file << "        nextStep();\n";
    file << "      } else {\n";
    file << "        clearInterval(autoInterval);\n";
    file << "        autoInterval = null;\n";
    file << "      }\n";
    file << "    }, 1000);\n";
    file << "  }\n";
    file << "}\n\n";

    file << "function reset() {\n";
    file << "  if (autoInterval) {\n";
    file << "    clearInterval(autoInterval);\n";
    file << "    autoInterval = null;\n";
    file << "  }\n";
    file << "  currentStep = 0;\n";
    file << "  showStep(currentStep);\n";
    file << "}\n";

    file << "</script>\n";
    file << "</body>\n</html>\n";
    file.close();
}

void SVGVisualizer::drawEdges(std::ofstream &file, const std::vector<int> &currentPath)
{
    std::cout << "Drawing edges in a function...\n";
    for (Node *node : graph->nodes)
    {
        for (Edge &edge : node->edges)
        {
            if (node->id < edge.target->id)
            {

                std::cout << "Drawing edge from " << node->id << " to " << edge.target->id << "\n";
                bool isInPath = isEdgeInPath(node->id, edge.target->id, currentPath);

                std::cout << "Edge " << node->id << " -> " << edge.target->id << (isInPath ? " is in the current path." : " is not in the current path.") << "\n";

                std::string edgeClass = isInPath ? "edge-path" : "edge";

                file << "<line x1=\"" << node->coords.x << "\" y1=\"" << node->coords.y
                     << "\" x2=\"" << edge.target->coords.x << "\" y2=\"" << edge.target->coords.y
                     << "\" class=\"" << edgeClass << "\"/>\n";

                // Draw weight
                int midX = (node->coords.x + edge.target->coords.x) / 2;
                int midY = (node->coords.y + edge.target->coords.y) / 2;
                file << "<text x=\"" << midX << "\" y=\"" << midY << "\" class=\"weight-text\">"
                     << edge.weight << "</text>\n";
            }
        }
    }
    std::cout << "Finished drawing edges.\n";
}

void SVGVisualizer::drawNodes(std::ofstream &file, const std::vector<int> &visitedNodes,
                              const std::vector<int> &currentPath, int currentNode)
{
    for (Node *node : graph->nodes)
    {
        std::string nodeClass = getNodeClass(node->id, visitedNodes, currentPath, currentNode);

        file << "<circle cx=\"" << node->coords.x << "\" cy=\"" << node->coords.y
             << "\" r=\"" << nodeRadius << "\" class=\"" << nodeClass << "\"/>\n";

        file << "<text x=\"" << node->coords.x << "\" y=\"" << node->coords.y + 4
             << "\" class=\"text\">" << node->id << "</text>\n";
    }
}


std::string SVGVisualizer::getNodeClass(int nodeId, const std::vector<int> &visitedNodes,
                                        const std::vector<int> &currentPath, int currentNode)
{
    if (nodeId == currentNode)
        return "node-current";

    for (int pathNode : currentPath)
    {
        if (pathNode == nodeId)
            return "node-path";
    }

    for (int visitedNode : visitedNodes)
    {
        if (visitedNode == nodeId)
            return "node-visited";
    }

    return "node-unvisited";
}

bool SVGVisualizer::isEdgeInPath(int from, int to, const std::vector<int> &path)
{
    if (path.empty())
        return false;

    for (int i = 0; i < path.size() - 1; ++i)
    {
        if ((path[i] == from && path[i + 1] == to) ||
            (path[i] == to && path[i + 1] == from))
        {
            return true;
        }
    }
    return false;
}

/**/