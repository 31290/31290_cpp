#pragma once
#include "graph.h"
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

struct ViewBox {
    int x, y, width, height;
};

struct RenderState {
    int currentNode = -1;
    std::vector<int> visitedNodes;
    std::vector<int> queuedNodes;
    std::vector<int> currentPath;
    std::unordered_map<int, int> distances;
};

class SVGVisualizer
{
private:
    Graph *graph;
    ViewBox viewBox;
    int nodeRadius = 15;
    int padding = 10;

    std::vector<Coords> displayCoords;
    
    void calculateViewBox();
    void calculateDisplayCoords();
    
    std::string generateSVGContent(const RenderState& state);
    std::string generateEdgesSVG(const std::vector<int>& currentPath);
    std::string generateNodesSVG(const RenderState& state);
    
    std::string getNodeClass(int nodeId, const RenderState& state);
    bool isEdgeInPath(int from, int to, const std::vector<int>& path);
    
    static const char* CSS_STYLES;

public:
    SVGVisualizer(Graph *g);
    
    void generateSVG(const std::string& filename, const RenderState& state = {});
    void generateHTML(const std::string& filename, const std::vector<RenderState>& states);
};