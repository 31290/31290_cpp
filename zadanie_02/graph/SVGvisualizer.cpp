#include "SVGVisualizer.h"
#include <iostream>
#include <sstream>

const char *SVGVisualizer::CSS_STYLES = R"(
.node-unvisited { fill: white; stroke: black; stroke-width: 2; }
.node-visited { fill: lightblue; stroke: black; stroke-width: 2; }
.node-current { fill: yellow; stroke: black; stroke-width: 3; }
.node-path { fill: lightgreen; stroke: black; stroke-width: 2; }
.edge { stroke: gray; stroke-width: 1; }
.edge-path { stroke: red; stroke-width: 3; }
.text { font-family: Arial; font-size: 12px; text-anchor: middle; }
.weight-text { font-family: Arial; font-size: 10px; text-anchor: middle; fill: blue; }
)";

SVGVisualizer::SVGVisualizer(Graph *g) : graph(g)
{
    calculateViewBox();
    calculateDisplayCoords();
}

void SVGVisualizer::calculateViewBox()
{
    if (graph->nodes.empty())
    {
        viewBox = {0, 0, 400, 400};
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

    viewBox.x = minX - padding - nodeRadius;
    viewBox.y = minY - padding - nodeRadius;
    viewBox.width = (maxX - minX) + 2 * (padding + nodeRadius);
    viewBox.height = (maxY - minY) + 2 * (padding + nodeRadius);
    std::cout << maxY << " " << minY << " " << maxX << " " << minX << std::endl;
    std::cout << "ViewBox: " << viewBox.x << ", " << viewBox.y << ", " << viewBox.width << ", " << viewBox.height << std::endl;
}

void SVGVisualizer::calculateDisplayCoords()
{
    displayCoords.reserve(graph->nodes.size());
    int offsetX = padding + nodeRadius - viewBox.x;
    int offsetY = padding + nodeRadius - viewBox.y;

    for (Node *node : graph->nodes)
    {
        displayCoords.emplace_back(node->coords.x + offsetX, node->coords.y + offsetY);
    }
}

std::string SVGVisualizer::generateSVGContent(const RenderState &state)
{
    std::ostringstream svg;
    svg << "<style>" << CSS_STYLES << "</style>\n";
    svg << generateEdgesSVG(state.currentPath);
    svg << generateNodesSVG(state);
    return svg.str();
}

std::string SVGVisualizer::generateEdgesSVG(const std::vector<int> &currentPath)
{
    std::ostringstream edges;

    for (size_t i = 0; i < graph->nodes.size(); ++i)
    {
        Node *node = graph->nodes[i];
        for (Edge &edge : node->edges)
        {
            size_t targetIdx = 0;
            for (size_t j = 0; j < graph->nodes.size(); ++j)
            {
                if (graph->nodes[j] == edge.target)
                {
                    targetIdx = j;
                    break;
                }
            }

            if (i < targetIdx)
            {
                bool inPath = isEdgeInPath(node->id, edge.target->id, currentPath);
                std::string edgeClass = inPath ? "edge-path" : "edge";

                const Coords &start = displayCoords[i];
                const Coords &end = displayCoords[targetIdx];

                edges << "<line x1=\"" << start.x << "\" y1=\"" << start.y
                      << "\" x2=\"" << end.x << "\" y2=\"" << end.y
                      << "\" class=\"" << edgeClass << "\"/>\n";

                int midX = (start.x + end.x) / 2;
                int midY = (start.y + end.y) / 2;
                edges << "<text x=\"" << midX << "\" y=\"" << midY
                      << "\" class=\"weight-text\">" << edge.weight << "</text>\n";
            }
        }
    }
    return edges.str();
}

std::string SVGVisualizer::generateNodesSVG(const RenderState &state)
{
    std::ostringstream nodes;

    for (size_t i = 0; i < graph->nodes.size(); ++i)
    {
        Node *node = graph->nodes[i];
        const Coords &pos = displayCoords[i];
        std::string nodeClass = getNodeClass(node->id, state);

        nodes << "<circle cx=\"" << pos.x << "\" cy=\"" << pos.y
              << "\" r=\"" << nodeRadius << "\" class=\"" << nodeClass << "\"/>\n";

        nodes << "<text x=\"" << pos.x << "\" y=\"" << pos.y + 4
              << "\" class=\"text\">" << node->id << "</text>\n";
    }
    return nodes.str();
}

std::string SVGVisualizer::getNodeClass(int nodeId, const RenderState &state)
{
    if (nodeId == state.currentNode)
        return "node-current";

    for (int pathNode : state.currentPath)
    {
        if (pathNode == nodeId)
            return "node-path";
    }

    for (int visitedNode : state.visitedNodes)
    {
        if (visitedNode == nodeId)
            return "node-visited";
    }

    return "node-unvisited";
}

bool SVGVisualizer::isEdgeInPath(int from, int to, const std::vector<int> &path)
{
    if (path.size() < 2)
        return false;

    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        if ((path[i] == from && path[i + 1] == to) ||
            (path[i] == to && path[i + 1] == from))
        {
            return true;
        }
    }
    return false;
}

void SVGVisualizer::generateSVG(const std::string &filename, const RenderState &state)
{
    std::ofstream file(filename);
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    file << "<svg width=\"" << viewBox.width + nodeRadius + 5 << "\" height=\"" << viewBox.height + nodeRadius + 5
         << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    file << generateSVGContent(state);
    file << "</svg>\n";
}

void SVGVisualizer::generateHTML(const std::string &filename, const std::vector<RenderState> &states)
{
    std::ostringstream html;
    html << "<!DOCTYPE html>\n<html><head>\n"
         << "<title>Graph Pathfinding Visualization</title>\n"
         << "<style>\n"
         << "body { font-family: Arial; margin: 20px; }\n"
         << ".controls { margin: 20px 0; }\n"
         << "button { margin: 5px; padding: 10px; font-size: 14px; }\n"
         << "#info { margin: 10px 0; font-weight: bold; }\n"
         << "</style>\n</head><body>\n"
         << "<h1>Graph Pathfinding Visualization</h1>\n"
         << "<div class=\"controls\">\n"
         << "<button onclick=\"prevStep()\">Previous</button>\n"
         << "<button onclick=\"nextStep()\">Next</button>\n"
         << "<button onclick=\"reset()\">Reset</button>\n"
         << "</div>\n"
         << "<div id=\"info\">Step: <span id=\"stepCounter\">0</span> / "
         << states.size() - 1 << "</div>\n";

    for (size_t i = 0; i < states.size(); ++i)
    {
        html << "<svg id=\"step" << i << "\" width=\"" << viewBox.width
             << "\" height=\"" << viewBox.height
             << "\" style=\"display:" << (i == 0 ? "block" : "none")
             << ";border:1px solid #ccc;\">\n";
        html << generateSVGContent(states[i]);
        html << "</svg>\n";
    }

    html << "<script>\n"
         << "let currentStep = 0;\n"
         << "const totalSteps = " << states.size() << ";\n"
         << "function showStep(step) {\n"
         << "  for (let i = 0; i < totalSteps; i++) {\n"
         << "    document.getElementById('step' + i).style.display = 'none';\n"
         << "  }\n"
         << "  document.getElementById('step' + step).style.display = 'block';\n"
         << "  document.getElementById('stepCounter').textContent = step;\n"
         << "}\n"
         << "function nextStep() { if (currentStep < totalSteps - 1) { currentStep++; showStep(currentStep); } }\n"
         << "function prevStep() { if (currentStep > 0) { currentStep--; showStep(currentStep); } }\n"
         << "function reset() { currentStep = 0; showStep(currentStep); }\n"
         << "</script>\n</body></html>\n";

    std::ofstream file(filename);
    file << html.str();
}