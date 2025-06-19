#include "graph.h"
#include <iostream>

int main()
{

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