#include <iostream>
#include <list>
#include "lists.h"

#define FLAG_INPUT (1 << 0)
#define OP_PUSH_FRONT (1 << 1)
#define OP_PUSH_BACK (1 << 2)
#define OP_POP_FRONT (1 << 3)
#define OP_POP_BACK (1 << 4)
#define OP_FRONT (1 << 5)
#define OP_BACK (1 << 6)

int c = 0;

void interpretBitMask(unsigned char f){
    std::cout << "Bitmask: " << (int)f << "\n";
    if (f & FLAG_INPUT){
        std::cout << "Number of repetitions: " << c << "\n";
    }
    else{
        std::cout << "Only the constructor will be created.\n";
        return;
    }
    if (f & OP_PUSH_FRONT)
        std::cout << "OP_PUSH_FRONT\n";
    if (f & OP_PUSH_BACK)
        std::cout << "OP_PUSH_BACK\n";
    if (f & OP_POP_FRONT)
        std::cout << "OP_POP_FRONT\n";
    if (f & OP_POP_BACK)
        std::cout << "OP_POP_BACK\n";
    if (f & OP_FRONT)
        std::cout << "OP_FRONT\n";
    if (f & OP_BACK)
        std::cout << "OP_BACK\n";    
}

void listOptions(){
    std::cout << "Choose actions:\n0. Only constructor.\n1. Push front\n2. Push back\n3. Pop front\n4. Pop back\n5. Front\n6. Back\n7. Repetition.\n8. Koniec\n9. List options.\n";
}

void testScarletList(unsigned char f)
{
    interpretBitMask(f);
    // Scarlet::List<int> List(1, 2, 3);
    // if (f & OP_PUSH_FRONT) List.push_front(0);
    // if (f & OP_PUSH_BACK) List.push_back(4);
    // if (f & OP_POP_FRONT) List.pop_front();
    // if (f & OP_POP_BACK) List.pop_back();
    // if (f & OP_FRONT) std::cout << "Front: " << List.front() << std::endl;
    // if (f & OP_BACK) std::cout << "Back: " << List.back() << std::endl;
}

char createBitMask()
{
    unsigned char f = 1;
    listOptions();
    while (true)
    {
        switch (std::cin.get())
        {
        case '0':
            f ^= FLAG_INPUT;
            break;
        case '1':
            f ^= OP_PUSH_FRONT;
            break;
        case '2':
            f ^= OP_PUSH_BACK;
            break;
        case '3':
            f ^= OP_POP_FRONT;
            break;
        case '4':
            f ^= OP_POP_BACK;
            break;
        case '5':
            f ^= OP_FRONT;
            break;
        case '6':
            f ^= OP_BACK;
            break;
        case '7':
            std::cout << "How many times to repeat an action: ";
            std::cin >> c;
            break;
        case '8':
            return f;
            break;
        case '9':
            interpretBitMask(f);
            listOptions();
            break;
        default:
            std::cout << "\r";
            break;
        }
    }
}

int main()
{

    std::cout << FLAG_INPUT << "\n";
    std::cout << OP_PUSH_FRONT << "\n";
    std::cout << OP_PUSH_BACK << "\n";
    std::cout << OP_POP_FRONT << "\n";
    std::cout << OP_POP_BACK << "\n";
    std::cout << OP_FRONT << "\n";
    std::cout << OP_BACK << "\n";

    std::cout << "Choose library:\n";
    std::cout << "0. Scarlet library.\n1. Standard library.\n2. Compare libraries.\n";
    switch (std::cin.get())
    {
    case '0':
        testScarletList(createBitMask());
        break;
    case '1':
        // remove List;
        break;
    case '2':
        std::cout << "Compare libraries.\n";
        break;
    default:
        std::cout << "Unknown parameter\n";
    }
}