#include "graph.h"
#include "SVGvisualizer.h"
#include "pathfinding.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>

struct TestResult {
    std::string scenario;
    std::string algorithm;
    int distance;
    int steps;
    std::vector<int> path;
    bool optimal;
};

class HeuristicTestGraphs {
public:
    // Scenario 1: Straight line - Pythagorean should dominate
    static Graph* createStraightLineGraph() {
        Graph* g = new Graph();
        
        for (int i = 0; i < 10; ++i) {
            g->createNode(i, Coords(i * 60, 200));
        }
        
        for (int i = 0; i < 9; ++i) {
            g->createEdge(i, i + 1);
        }
        
        return g;
    }
    
    // Scenario 2: L-shaped corridor - Manhattan should excel
    static Graph* createLShapedGraph() {
        Graph* g = new Graph();
        
        // Horizontal part (8 nodes)
        for (int i = 0; i < 8; ++i) {
            g->createNode(i, Coords(i * 60, 200));
        }
        
        // Vertical part (8 nodes) 
        for (int i = 0; i < 8; ++i) {
            g->createNode(8 + i, Coords(420, 200 + i * 60));
        }
        
        // Connect horizontal
        for (int i = 0; i < 7; ++i) {
            g->createEdge(i, i + 1);
        }
        
        // Connect vertical
        for (int i = 0; i < 7; ++i) {
            g->createEdge(8 + i, 9 + i);
        }
        
        // Connect corner
        g->createEdge(7, 8);
        
        return g;
    }
    
    // Scenario 3: Grid with diagonals - Chebyshev should win
    static Graph* createGridWithDiagonals() {
        Graph* g = new Graph();
        int id = 0;
        
        // Create 6x6 grid with 60 unit spacing
        for (int y = 0; y < 6; ++y) {
            for (int x = 0; x < 6; ++x) {
                g->createNode(id++, Coords(x * 60, y * 60));
            }
        }
        
        // Connect with all 8 directions
        for (int y = 0; y < 6; ++y) {
            for (int x = 0; x < 6; ++x) {
                int currentId = y * 6 + x;
                
                // Right
                if (x < 5) {
                    g->createEdge(currentId, currentId + 1);
                }
                
                // Down
                if (y < 5) {
                    g->createEdge(currentId, currentId + 6);
                }
                
                // Diagonals
                if (x < 5 && y < 5) {
                    g->createEdge(currentId, currentId + 7); // down-right
                }
                if (x > 0 && y < 5) {
                    g->createEdge(currentId, currentId + 5); // down-left
                }
            }
        }
        
        return g;
    }
    
    // Scenario 4: Spiral trap - Dot Product should fail
    static Graph* createSpiralTrap() {
        Graph* g = new Graph();
        
        std::vector<Coords> coords = {
            {100, 100},   // 0 - start
            {160, 100},   // 1
            {220, 100},   // 2 
            {280, 100},   // 3
            {340, 100},   // 4
            {340, 160},   // 5
            {340, 220},   // 6
            {340, 280},   // 7
            {280, 280},   // 8
            {220, 280},   // 9
            {160, 280},   // 10
            {160, 220},   // 11
            {160, 160},   // 12
            {220, 160},   // 13
            {280, 160},   // 14
            {280, 220},   // 15
            {220, 220},   // 16 - target (center of spiral)
        };
        
        for (int i = 0; i < coords.size(); ++i) {
            g->createNode(i, coords[i]);
        }
        
        // Create spiral path
        std::vector<std::pair<int, int>> connections = {
            {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7},
            {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13},
            {13, 14}, {14, 15}, {15, 16}
        };
        
        for (auto& conn : connections) {
            g->createEdge(conn.first, conn.second);
        }
        
        return g;
    }
    
    // Scenario 5: Maze with dead ends - should test exploration efficiency
    static Graph* createMazeGraph() {
        Graph* g = new Graph();
        
        std::vector<Coords> coords = {
            {100, 100},   // 0 - start
            {160, 100},   // 1
            {220, 100},   // 2
            {160, 160},   // 3 - dead end branch
            {220, 160},   // 4
            {280, 160},   // 5
            {340, 160},   // 6
            {220, 220},   // 7 - another dead end
            {280, 220},   // 8
            {340, 220},   // 9
            {400, 220},   // 10
            {460, 220},   // 11 - target
        };
        
        for (int i = 0; i < coords.size(); ++i) {
            g->createNode(i, coords[i]);
        }
        
        // Main path and dead ends
        std::vector<std::pair<int, int>> connections = {
            {0, 1}, {1, 2}, {1, 3}, // dead end at 3
            {2, 4}, {4, 5}, {5, 6},
            {4, 7}, // dead end at 7
            {5, 8}, {8, 9}, {9, 10}, {10, 11}
        };
        
        for (auto& conn : connections) {
            g->createEdge(conn.first, conn.second);
        }
        
        return g;
    }
};

std::string getHeuristicName(int type) {
    switch (type) {
        case 0: return "Pythagorean";
        case 1: return "DotProduct";
        case 3: return "Manhattan";
        case 4: return "Chebyshev";
        default: return "Unknown";
    }
}

void runTestScenario(const std::string& scenarioName, Graph* graph, int startId, int targetId, 
                    std::vector<TestResult>& results, std::ofstream& logFile) {
    
    logFile << "\n=== " << scenarioName << " ===" << std::endl;
    logFile << "Start: " << startId << ", Target: " << targetId << std::endl;
    
    SVGVisualizer visualizer(graph);
    
    // Run Dijkstra (ground truth)
    DijkstraVisualizer dijkstra(graph, &visualizer);
    dijkstra.runDijkstra(startId, targetId);
    
    TestResult dijkstraResult;
    dijkstraResult.scenario = scenarioName;
    dijkstraResult.algorithm = "Dijkstra";
    dijkstraResult.distance = dijkstra.getShortestDistance(startId, targetId);
    dijkstraResult.steps = dijkstra.getStepCount();
    dijkstraResult.path = dijkstra.getShortestPath(startId, targetId);
    dijkstraResult.optimal = true;
    results.push_back(dijkstraResult);
    
    dijkstra.generateVisualization(scenarioName + "_dijkstra.html");
    
    logFile << "Dijkstra: distance=" << dijkstraResult.distance 
            << ", steps=" << dijkstraResult.steps << std::endl;
    
    // Test heuristics (skip progress factor = 2)
    std::vector<int> heuristics = {0, 1, 3, 4};
    std::vector<TestResult> heuristicResults;
    
    for (int h : heuristics) {
        AStarVisualizer astar(graph, &visualizer, h);
        astar.runAStar(startId, targetId);
        
        TestResult result;
        result.scenario = scenarioName;
        result.algorithm = "AStar_" + getHeuristicName(h);
        result.distance = astar.getShortestDistance(startId, targetId);
        result.steps = astar.getStepCount();
        result.path = astar.getShortestPath(startId, targetId);
        result.optimal = (result.distance == dijkstraResult.distance);
        
        heuristicResults.push_back(result);
        results.push_back(result);
        
        logFile << getHeuristicName(h) << ": distance=" << result.distance 
                << ", steps=" << result.steps 
                << ", optimal=" << (result.optimal ? "YES" : "NO") << std::endl;
    }
    
    // Find best and worst heuristics
    auto bestIt = std::min_element(heuristicResults.begin(), heuristicResults.end(),
        [](const TestResult& a, const TestResult& b) {
            if (a.optimal != b.optimal) return a.optimal > b.optimal;
            return a.steps < b.steps;
        });
    
    auto worstIt = std::max_element(heuristicResults.begin(), heuristicResults.end(),
        [](const TestResult& a, const TestResult& b) {
            if (a.optimal != b.optimal) return a.optimal > b.optimal;
            return a.steps < b.steps;
        });
    
    if (bestIt != heuristicResults.end()) {
        std::string bestAlg = bestIt->algorithm.substr(6); // Remove "AStar_"
        AStarVisualizer bestAstar(graph, &visualizer, 
            bestAlg == "Pythagorean" ? 0 : 
            bestAlg == "DotProduct" ? 1 : 
            bestAlg == "Manhattan" ? 3 : 4);
        bestAstar.runAStar(startId, targetId);
        bestAstar.generateVisualization(scenarioName + "_best_" + bestAlg + ".html");
        
        logFile << "BEST: " << bestAlg << " (steps: " << bestIt->steps << ")" << std::endl;
    }
    
    if (worstIt != heuristicResults.end()) {
        std::string worstAlg = worstIt->algorithm.substr(6); // Remove "AStar_"
        AStarVisualizer worstAstar(graph, &visualizer,
            worstAlg == "Pythagorean" ? 0 : 
            worstAlg == "DotProduct" ? 1 : 
            worstAlg == "Manhattan" ? 3 : 4);
        worstAstar.runAStar(startId, targetId);
        worstAstar.generateVisualization(scenarioName + "_worst_" + worstAlg + ".html");
        
        logFile << "WORST: " << worstAlg << " (steps: " << worstIt->steps << ")" << std::endl;
    }
}

int main() {
    std::vector<TestResult> allResults;
    std::ofstream logFile("results.txt");
    
    logFile << "HEURISTIC PERFORMANCE ANALYSIS" << std::endl;
    logFile << "=============================" << std::endl;
    
    // Test scenarios
    struct Scenario {
        std::string name;
        Graph* (*createFunc)();
        int startId;
        int targetId;
    };
    
    std::vector<Scenario> scenarios = {
        {"StraightLine", HeuristicTestGraphs::createStraightLineGraph, 0, 9},
        {"LShape", HeuristicTestGraphs::createLShapedGraph, 0, 15},
        {"GridDiagonal", HeuristicTestGraphs::createGridWithDiagonals, 0, 35},
        {"SpiralTrap", HeuristicTestGraphs::createSpiralTrap, 0, 16},
        {"MazeDeadEnds", HeuristicTestGraphs::createMazeGraph, 0, 11}
    };
    
    for (auto& scenario : scenarios) {
        Graph* graph = scenario.createFunc();
        runTestScenario(scenario.name, graph, scenario.startId, scenario.targetId, allResults, logFile);
        delete graph;
    }
    
    // Summary analysis
    logFile << "\n\nSUMMARY ANALYSIS" << std::endl;
    logFile << "================" << std::endl;
    
    std::map<std::string, int> algorithmWins;
    std::map<std::string, int> totalOptimal;
    std::map<std::string, int> totalRuns;
    
    for (const auto& result : allResults) {
        if (result.algorithm != "Dijkstra") {
            totalRuns[result.algorithm]++;
            if (result.optimal) {
                totalOptimal[result.algorithm]++;
            }
        }
    }
    
    // Find best performer per scenario
    std::set<std::string> uniqueScenarios;
    for (const auto& result : allResults) {
        uniqueScenarios.insert(result.scenario);
    }
    
    for (const std::string& scenario : uniqueScenarios) {
        std::vector<TestResult> scenarioResults;
        for (const auto& result : allResults) {
            if (result.scenario == scenario && result.algorithm != "Dijkstra") {
                scenarioResults.push_back(result);
            }
        }
        
        if (!scenarioResults.empty()) {
            auto best = std::min_element(scenarioResults.begin(), scenarioResults.end(),
                [](const TestResult& a, const TestResult& b) {
                    if (a.optimal != b.optimal) return a.optimal > b.optimal;
                    return a.steps < b.steps;
                });
            
            algorithmWins[best->algorithm]++;
        }
    }
    
    logFile << "\nAlgorithm Performance:" << std::endl;
    for (const auto& pair : totalRuns) {
        double optimalRate = (double)totalOptimal[pair.first] / pair.second * 100.0;
        logFile << std::setw(15) << pair.first 
                << ": " << totalOptimal[pair.first] << "/" << pair.second 
                << " optimal (" << std::fixed << std::setprecision(1) << optimalRate << "%)"
                << ", wins: " << algorithmWins[pair.first] << std::endl;
    }
    
    // Find overall champion
    auto champion = std::max_element(algorithmWins.begin(), algorithmWins.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second;
        });
    
    if (champion != algorithmWins.end()) {
        logFile << "\nOVERALL CHAMPION: " << champion->first 
                << " (won " << champion->second << " scenarios)" << std::endl;
    }
    
    logFile.close();
    std::cout << "Analysis complete! Check results.txt and generated HTML files." << std::endl;
    
    return 0;
}