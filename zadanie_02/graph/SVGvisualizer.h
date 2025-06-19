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