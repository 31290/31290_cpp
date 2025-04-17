#include <iostream>
#include <list>
#include <chrono>
#include <string>
#include "lists.h"

#define lll 1, 2, 3, 4 //, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20

#define REP 1000000

#define FLAG_INPUT (1 << 0)
#define OP_PUSH_FRONT (1 << 1)
#define OP_PUSH_BACK (1 << 2)
#define OP_POP_FRONT (1 << 3)
#define OP_POP_BACK (1 << 4)
#define OP_FRONT (1 << 5)
#define OP_BACK (1 << 6)

int c = 1;
char x;

void interpretBitMask(unsigned char f)
{
    std::cout << "\nBitmask: " << (int)f << "\n";
    if (f & FLAG_INPUT)
    {
        std::cout << "Number of repetitions: " << c << "\n";
    }
    else
    {
        std::cout << "Only the constructor will be created.\n";
        return;
    }
    if (f & OP_PUSH_FRONT)
        std::cout << "OP_PUSH_FRONT ";
    if (f & OP_PUSH_BACK)
        std::cout << "OP_PUSH_BACK ";
    if (f & OP_POP_FRONT)
        std::cout << "OP_POP_FRONT ";
    if (f & OP_POP_BACK)
        std::cout << "OP_POP_BACK ";
    if (f & OP_FRONT)
        std::cout << "OP_FRONT ";
    if (f & OP_BACK)
        std::cout << "OP_BACK ";
}

void getActions(char f)
{
    if (f & OP_PUSH_FRONT)
        std::cout << "OP_PUSH_FRONT ";
    if (f & OP_PUSH_BACK)
        std::cout << "OP_PUSH_BACK ";
    if (f & OP_POP_FRONT)
        std::cout << "OP_POP_FRONT ";
    if (f & OP_POP_BACK)
        std::cout << "OP_POP_BACK ";
    std::cout << c << " times.";
}

void listOptions()
{
    std::cout << "\nChoose actions:\n0. Only constructor.\n1. Push front\n2. Push back\n3. Pop front\n4. Pop back\n5. Front\n6. Back\n7. Repetition.\n8. End\n9. List options.\n";
}

void testScarletList(unsigned char f)
{
    interpretBitMask(f);

    if (!f & FLAG_INPUT)
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto List = Scarlet::List<int>(1, 2, 3);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Time taken by the Scarlet list to create a list of {1, 2, 3}: " << duration.count() << " ms\n\n";
    }
    else
    {
        auto s = std::chrono::high_resolution_clock::now();
        auto List = Scarlet::List<int>(lll);
        auto e = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::high_resolution_clock::now();
        if (f & OP_PUSH_FRONT)
            for (int i = 0; i < c; ++i)
                List.push_front(0);
        if (f & OP_PUSH_BACK)
            for (int i = 0; i < c; ++i)
                List.push_back(4);
        if (f & OP_POP_FRONT)
            for (int i = 0; i < c; ++i)
                List.pop_front();
        if (f & OP_POP_BACK)
            for (int i = 0; i < c; ++i)
                List.pop_back();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::chrono::duration<double, std::milli> d = e - s;

        if (f & OP_FRONT)
            std::cout << "Front: " << List.front() << std::endl;
        if (f & OP_BACK)
            std::cout << "Back: " << List.back() << std::endl;

        std::cout << "\nTime taken by the Scarlet list to create a list of {1, 2, 3}: " << d.count() << " ms\n";

        std::cout << "\nTime taken by the Scarlet list to perform actions like\n";
        getActions(f);
        std::cout << "\nWas " << duration.count() << " ms\n";
    }
}

void testStandardList(unsigned char f)
{
    interpretBitMask(f);

    if (!f & FLAG_INPUT)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::list<int> List{1, 2, 3};
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Time taken by the Standard list to create a list of {1, 2, 3}: " << duration.count() << " ms\n";
    }
    else
    {
        auto s = std::chrono::high_resolution_clock::now();
        std::list<int> List{1, 2, 3};
        auto e = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::high_resolution_clock::now();
        if (f & OP_PUSH_FRONT)
            for (int i = 0; i < c; ++i)
                List.push_front(0);
        if (f & OP_PUSH_BACK)
            for (int i = 0; i < c; ++i)
                List.push_back(4);
        if (f & OP_POP_FRONT)
            for (int i = 0; i < c; ++i)
                List.pop_front();
        if (f & OP_POP_BACK)
            for (int i = 0; i < c; ++i)
                List.pop_back();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::chrono::duration<double, std::milli> d = e - s;

        if (f & OP_FRONT)
            std::cout << "Front: " << List.front() << std::endl;
        if (f & OP_BACK)
            std::cout << "Back: " << List.back() << std::endl;

        std::cout << "\nTime taken by the Standard list to create a list of {1, 2, 3}: " << d.count() << " ms\n";

        std::cout << "\nTime taken by the Standard list to perform actions like\n";
        getActions(f);
        std::cout << "\nWas " << duration.count() << " ms\n";
    }
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

void allStandardTest()
{
    unsigned char f = 0;
    testStandardList(f);
    f ^= OP_PUSH_FRONT;
    testStandardList(f);
    f = 0;
    f ^= OP_PUSH_BACK;
    testStandardList(f);
    f = 0;
    f ^= OP_POP_FRONT;
    testStandardList(f);
    f = 0;
    f ^= OP_POP_BACK;
    testStandardList(f);
    f = 0;
}

void allScarletTest()
{
    std::cout << "KURWAAAA";
    unsigned char f = 0;
    testScarletList(f);
    f ^= OP_PUSH_FRONT;
    testScarletList(f);
    f = 0;
    f ^= OP_PUSH_BACK;
    testScarletList(f);
    f = 0;
    f ^= OP_POP_FRONT;
    testScarletList(f);
    f = 0;
    f ^= OP_POP_BACK;
    testScarletList(f);
    f = 0;
}

int main()
{
    /*char ff;
    std::cout << "\nChoose library:\n";
    std::cout << "0. Scarlet library.\n1. Standard library.\n2. Compare libraries.\n3. Exit.\n";
    switch (std::cin.get())
    {
    case '0':
        testScarletList(createBitMask());
        return 1;
        break;
    case '1':
        testStandardList(createBitMask());
        return 1;
        break;
    case '2':
        std::cout << "Compare libraries.\n";
        ff = createBitMask();
        std::cout << "\nStandard library:";
        testStandardList(ff);
        std::cout << "\nScarlet library:";
        testScarletList(ff);
        return 1;
        break;
    case '3':
        return 0;
    case '4':
        allScarletTest();
        allStandardTest();
        return 2;
    default:
        std::cout << "Invalid parameter.\n";
        return -1;
        break;
    }/**/

    /*
    for (int i = 0; i < 10; ++i)
    {
        _sleep(300);
        std::cout << "\r" << std::string(i, '.');
    }
    std::cout << "\n";/**/

    // pierdole to kurwa

/*    double sum = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    for (int i = 0; i < REP; i++)
    {
        start = std::chrono::high_resolution_clock::now();
        std::list<int> list{lll};
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        sum += duration.count();
    }
    // std::cout << list.size();
    std::cout << "Average time taken by the Standard list to create a list of {1, 2, 3}: " << sum / REP << " ms\n\n";

    sum = 0;
    start = std::chrono::high_resolution_clock::now();
    auto List = Scarlet::List<int>(lll);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    sum += duration.count();
    // std::cout << List.size();
    std::cout << "Average time taken by the Scarlet list to create a list of {1, 2, 3}: " << sum / REP << " ms\n\n";/**/
}