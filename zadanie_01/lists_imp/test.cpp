#include <functional>
#include <list>
#include <iostream>
#include "lists.h"
#define ENABLE_DUMP

#define small 1, 2, 3, 4, 5

int main()
{
    std::cout << "chuj" << "\n";
    Scarlet::List<int> list1 = Scarlet::List<int>(small);
    Scarlet::List<int> list2 = Scarlet::List<int>(small);
    Scarlet::List<int> list3 = Scarlet::List<int>(small);
    Scarlet::List<int> list4 = Scarlet::List<int>(small);
    Scarlet::List<int> list5 = Scarlet::List<int>(small);
    std::cout << "pierdole" << "\n";

    Scarlet::List<Scarlet::List<int>> list = Scarlet::List<Scarlet::List<int>>();
    std::cout << "ejbie" << "\n";
    list.push_back(list1);

    std::cout << "dupa" << "\n";
    for (Scarlet::List<int> val : list)
    {
        std::cout << "kurwa" << "\n";
        for (const auto &el : val)
        {
            std::cout << "el" << el << "\n";
        }
        std::cout << "mać" << "\n";
    }
}
