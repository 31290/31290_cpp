#include <iostream>
#include <list>
#include "lists.h"

int main()
{
    Scarlet::List<int> List(1, 2, 3);

    std::cout << "1. Wlasna biblioteka.\n2. Standardowa bilbioteka\n3. Porownaj biblioteki.\n";
    Scarlet::List<int> List(1, 2, 3);
    switch(std::cin.get())
    {
        case '1':
            break;
        case '2':
            // remove List;
            std::list<int> List{1, 2, 3};
            break;
        case '3':
            std::cout << "Porownaj biblioteki\n";
            break;
        default:
            std::cout << "Nieznany wybor\n";
    }
}