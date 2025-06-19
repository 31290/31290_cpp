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