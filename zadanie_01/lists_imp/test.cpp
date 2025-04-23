#include <functional>
#include <list>
#include <chrono>
#include <iostream>
#include "lists.h"
#define ENABLE_DUMP

#define lll 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20

template <typename ListType>
double testList(const char *label, std::function<ListType()> constructor)
{
    auto start = std::chrono::steady_clock::now();

    ListType lst = constructor();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    return elapsed.count();
}

int main()
{
    std::cout << "Scarlet " << testList<Scarlet ::List<int>>("Scarlet ", []
                                                           { return Scarlet ::List<int>(lll); })
              << " ms\n";
    std::cout << testList<std::list<int>>("Standard", []
                                          { return std::list<int>{lll}; })
              << " ms\n";
    std::cout << "Scarlet " << testList<Scarlet ::List<int>>("Scarlet ", []
                                                           { return Scarlet ::List<int>(lll); })
              << " ms\n";
    std::cout << testList<std::list<int>>("Standard", []
                                          { return std::list<int>{lll}; })
              << " ms\n";
    std::cout << "Scarlet " << testList<Scarlet ::List<int>>("Scarlet ", []
                                                           { return Scarlet ::List<int>(lll); })
              << " ms\n";
    std::cout << testList<std::list<int>>("Standard", []
                                          { return std::list<int>{lll}; })
              << " ms\n";
    std::cout << "Scarlet " << testList<Scarlet ::List<int>>("Scarlet ", []
                                                           { return Scarlet ::List<int>(lll); })
              << " ms\n";
    std::cout << testList<std::list<int>>("Standard", []
                                          { return std::list<int>{lll}; })
              << " ms\n";
}
