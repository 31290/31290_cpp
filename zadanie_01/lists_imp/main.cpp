#include <iostream>
#include <list>
#include "lists.h"

#define FLAG_INPUT      (1 << 0)
#define OP_PUSH_FRONT   (1 << 1)
#define OP_PUSH_BACK    (1 << 2)
#define OP_POP_FRONT    (1 << 3)
#define OP_POP_BACK     (1 << 4)
#define OP_FRONT        (1 << 5)
#define OP_BACK         (1 << 6)

int c;

void testScarletList(char f)
{
    Scarlet::List<int> List(1, 2, 3);
    if (f & OP_PUSH_FRONT) List.push_front(0);
    if (f & OP_PUSH_BACK) List.push_back(4);
    if (f & OP_POP_FRONT) List.pop_front();
    if (f & OP_POP_BACK) List.pop_back();
    if (f & OP_FRONT) std::cout << "Front: " << List.front() << std::endl;
    if (f & OP_BACK) std::cout << "Back: " << List.back() << std::endl;
}

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