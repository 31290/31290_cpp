#include <iostream>
#include <list>
#include <chrono>
#include <string>
#include "lists.h"

#define lll 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20

#define REP 100000000

#define FLAG_INPUT (1 << 0)
#define OP_PUSH_FRONT (1 << 1)
#define OP_PUSH_BACK (1 << 2)
#define OP_POP_FRONT (1 << 3)
#define OP_POP_BACK (1 << 4)
#define OP_FRONT (1 << 5)
#define OP_BACK (1 << 6)

int c = 1;

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
    std::cout << "\033[1;35m";
    if (f & OP_PUSH_FRONT)
        std::cout << "OP_PUSH_FRONT ";
    if (f & OP_PUSH_BACK)
        std::cout << "OP_PUSH_BACK ";
    if (f & OP_POP_FRONT)
        std::cout << "OP_POP_FRONT ";
    if (f & OP_POP_BACK)
        std::cout << "OP_POP_BACK ";
    std::cout << "\033[1;32m" << c << "\033[0m times";
}

void listOptions()
{
    std::cout << "\nChoose actions:\n0. Only constructor.\n1. Push front\n2. Push back\n3. Pop front\n4. Pop back\n5. Front\n6. Back\n7. Repetition.\n8. End\n9. List options.\n";
}

template <typename T>
void dumpList(std::list<T> &List)
{
    std::cout << "\033[1;34m{  ";
    for (const auto &element : List)
    {
        std::cout << element << ", ";
    }
    std::cout << "\b\b  }\033[0m";
}

void testScarletList(unsigned char f, bool mask = false)
{
    if (mask)
        interpretBitMask(f);

    // auto List = Scarlet::List<int>(lll);
    if (!f & FLAG_INPUT)
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - end;
        std::chrono::duration<double, std::milli> d = end - end;
        for (int i = 0; i < c; ++i)
        {
            {
                start = std::chrono::high_resolution_clock::now();
                auto List = Scarlet::List<int>(lll);
                end = std::chrono::high_resolution_clock::now();
                duration += end - start;
                if (c == 1)
                {
                    std::cout << "\nTime taken by the\033[1;31m Scarlet \033[0mlist to create a list ";
                    if (List.size() < 100)
                        List.dump();
                    std::cout << ": \033[1;33m" << duration.count() << "\033[0m ms.\n";
                }
                start = std::chrono::high_resolution_clock::now();
            }
            end = std::chrono::high_resolution_clock::now();
            d += end - start;
        }
        if (c == 1)
        {
            std::cout << "Time taken to destroy the list: \033[1;33m" << d.count() << "\033[0m ms.";
        }
        else
        {
            std::cout << "\nTime taken by the\033[1;31m Scarlet \033[0mlist to create a list over \033[1;32m" << c << "\033[0m repetitions: \033[1;33m" << duration.count() / c << "\033[0m ms.\n";
            std::cout << "Time taken to destroy the list averaged over \033[1;32m" << c << "\033[0m repetitions: \033[1;33m" << d.count() / c << "\033[0m ms.\n";
        }
    }
    else
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto List = Scarlet::List<int>(lll);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\n\nTime taken by the\033[1;31m Scarlet \033[0mlist to create a list ";
        if (List.size() < 100)
            List.dump();
        std::cout << " \033[1;33m" << duration.count() << "\033[0m ms\n";

        int i = 0;
        try
        {
            start = std::chrono::high_resolution_clock::now();
            if (f & OP_PUSH_FRONT)
                for (i = 0; i < c; ++i)
                    List.push_front(i);
            if (f & OP_PUSH_BACK)
                for (i = 0; i < c; ++i)
                    List.push_back(c - i);
            if (f & OP_POP_FRONT)
                for (i = 0; i < c; ++i)
                    List.pop_front();
            if (f & OP_POP_BACK)
                for (i = 0; i < c; ++i)
                    List.pop_back();
        }
        catch (const char *x)
        {
            std::cout << "\033[1;31mError: " << x << "\033[0m Ending early.\n";
        }
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        if (f & OP_FRONT)
            std::cout << "Front: " << List.front() << std::endl;
        if (f & OP_BACK)
            std::cout << "Back: " << List.back() << std::endl;

        std::cout << "Time taken by the\033[1;31m Scarlet \033[0mlist to perform\n";
        getActions(f);
        std::cout << " was \033[1;33m" << duration.count() << "\033[0m ms ";
        if (c != 1)
            std::cout << " which averages to \033[1;35m" << duration.count() / i << "\033[0m ms for all actions" << "\n";
        std::cout << "and resulted in a list ";
        if (List.size() < 100)
            List.dump();
    }
}

void testStandardList(unsigned char f, bool mask = false)
{
    if (mask)
        interpretBitMask(f);

    // std::list<int> List{1, 2, 3};
    if (!f & FLAG_INPUT)
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - end;
        std::chrono::duration<double, std::milli> d = end - end;
        for (int i = 0; i < c; ++i)
        {
            {
                start = std::chrono::high_resolution_clock::now();
                std::list<int> List{lll};
                end = std::chrono::high_resolution_clock::now();
                duration += end - start;
                if (c == 1)
                {
                    std::cout << "\nTime taken by the\033[1;36m Standard \033[0mlist to create a list of ";

                    if (List.size() < 100)
                        dumpList(List);
                    std::cout << ": \033[1;33m" << duration.count() << "\033[0m ms.\n";
                }
                start = std::chrono::high_resolution_clock::now();
            }
            end = std::chrono::high_resolution_clock::now();
            d += end - start;
        }
        if (c == 1)
        {
            std::cout << "Time taken to destroy the list: \033[1;33m" << d.count() << "\033[0m ms.";
        }
        else
        {
            std::cout << "\nTime taken by the\033[1;36m Standard \033[0mlist to create a list over \033[1;32m" << c << "\033[0m repetitions: \033[1;33m" << duration.count() / c << "\033[0m ms.\n";
            std::cout << "Time taken to destroy the list averaged over \033[1;32m" << c << "\033[0m repetitions: \033[1;33m" << d.count() / c << "\033[0m ms.\n";
        }
    }
    else
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::list<int> List{lll};
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "\n\nTime taken by the\033[1;36m Standard \033[0mlist to create a list of ";

        if (List.size() < 100)
            dumpList(List);
        std::cout << " \033[1;33m" << duration.count() << "\033[0m ms\n";

        int i = 0;
        try
        {
            start = std::chrono::high_resolution_clock::now();
            if (f & OP_PUSH_FRONT)
                for (i = 0; i < c; ++i)
                    List.push_front(i);
            if (f & OP_PUSH_BACK)
                for (i = 0; i < c; ++i)
                    List.push_back(c - i);
            if (f & OP_POP_FRONT)
                for (i = 0; i < c; ++i)
                    List.pop_front();
            if (f & OP_POP_BACK)
                for (i = 0; i < c; ++i)
                    List.pop_back();
        }
        catch (const char *x)
        {
            std::cout << "\033[1;31mError: " << x << "\033[0m Ending early.\n";
        }
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        if (f & OP_FRONT)
            std::cout << "Front: " << List.front() << std::endl;
        if (f & OP_BACK)
            std::cout << "Back: " << List.back() << std::endl;

        std::cout << "Time taken by the\033[1;36m Standard \033[0mlist to perform\n";
        getActions(f);
        std::cout << " was \033[1;33m" << duration.count() << "\033[0m ms ";
        if (c != 1)
            std::cout << " which averages to \033[1;35m" << duration.count() / i << "\033[0m ms for all actions" << "\n";
        std::cout << "and resulted in a list of ";
        if (List.size() < 100)
            dumpList(List);
    }
}

void allStandardTest()
{
    std::cout << "\n\n\n\n";
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
}

void allScarletTest()
{
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
    std::cout << "\n\n\033[1;31mScarlet\033[0m tests finished.";
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
        case 'a':
            allScarletTest();
            allStandardTest();
            break;
        default:
            std::cout << "\r";
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        c = atoi(argv[1]);
        std::cout << "Number of repetitions set to: \033[1;32m" << c << "\033[0m";
    }
    char ff;
    std::cout << "\nChoose library:\n";
    std::cout << "0.\033[1;31m Scarlet \033[0mlibrary.\n1.\033[1;36m Standard \033[0mlibrary.\n2. Compare libraries.\n3. \033[1;31mExit.\033[0m\n";
    switch (std::cin.get())
    {
    case '0':
        testScarletList(createBitMask(), true);
        return 1;
        break;
    case '1':
        testStandardList(createBitMask(), true);
        return 1;
        break;
    case '2':
        std::cout << "Compare libraries.\n";
        ff = createBitMask();
        interpretBitMask(ff);
        std::cout << "\n\n\033[1;36mStandard library:\033[0m";
        testStandardList(ff);
        std::cout << "\n\n\033[1;31mScarlet library:\033[0m";
        testScarletList(ff);
        return 1;
        break;
    case '3':
        return 0;
    case '4':
        allScarletTest();
        allStandardTest();
        return 2;
    case '5':
        allScarletTest();
        return 2;
    case '6':
        allStandardTest();
        return 2;
    default:
        std::cout << "Invalid parameter.\n";
        return -1;
        break;
    } /**/

    /*
    for (int i = 0; i < 10; ++i)
    {
        _sleep(300);
        std::cout << "\r" << std::string(i, '.');
    }
    std::cout << "\n";/**/

    // pierdole to kurwa
    /*
        double sum = 0;
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
        std::cout << "Average time taken by the\033[1;36m Standard \033[0mlist to create a list of {1, 2, 3}: " << sum / REP << " ms\n\n";

        sum = 0;
        for (int i = 0; i < REP; i++)
        {
            start = std::chrono::high_resolution_clock::now();
            auto List = Scarlet::List<int>(1, 2, 3);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            sum += duration.count();
        }
        // std::cout << List.size();
        std::cout << "Average time taken by the\033[1;31m Scarlet \033[0mlist to create a list of {1, 2, 3}: " << sum / REP << " ms\n\n"; /**/
}