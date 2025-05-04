#include <iostream>
#include <list>
#include <chrono>
#include <string>
#define ENABLE_DUMP
#include "lists.h"
#include <functional>
#include <type_traits>

#define small 1, 2, 3, 4, 5
#define lll 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
#define mmm lll, lll, lll, lll, lll, lll, lll, lll, lll, lll
#define nnn mmm, mmm, mmm, mmm, mmm, mmm, mmm, mmm, mmm, mmm
// #define ooo nnn, nnn, nnn, nnn, nnn, nnn, nnn, nnn, nnn, nnn

#define ScarletLabel "\033[1;31mScarlet\033[0m"
#define TwoWayLabel "\033[1;32mScarlet Two Way\033[0m"
#define CyclicLabel "\033[1;34mScarlet Cyclic\033[0m"
#define StandardLabel "\033[1;36mStandard\033[0m"

#define FLAG_INPUT (1 << 0)
#define OP_PUSH_FRONT (1 << 1)
#define OP_PUSH_BACK (1 << 2)
#define OP_POP_FRONT (1 << 3)
#define OP_POP_BACK (1 << 4)
#define OP_RETURN (1 << 5)
#define OP_ITER (1 << 6)

int c = 1;
int a = 0;
bool saveToCSV = false;

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
    if (f & OP_RETURN)
        std::cout << "OP_RETURN ";
    if (f & OP_ITER)
        std::cout << "OP_ITER ";
}

void getActions(char f, int i = -1)
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
    if (i == -1)
        std::cout << "\033[1;32m" << c << "\033[0m times";
    else
        std::cout << "\033[1;32m" << i << "\033[0m times";
    if (f & OP_ITER)
        std::cout << " and \033[1;31mOP_ITER\033[0m";
}

void listOptions()
{
    std::cout << "\nChoose actions:\n0. Only constructor.\n1. Push front\n2. Push back\n3. Pop front\n4. Pop back\n5. Begin and End\n6. Iterate\n7. Repetition.\n8. End\n9. List options.\n";
}

template <typename T>
void dumpContent(std::list<T> &List)
{
    std::cout << "\033[1;34m{  ";
    for (const T &element : List)
    {
        std::cout << element << ", ";
    }
    std::cout << "\b\b  }\033[0m";
}

template <typename T>
void dumpList(std::list<T> &List)
{
    dumpContent(List);
    std::cout << "\033[1;34m(Size:" << List.size() << ")\033[0m";
}

template <typename list>
void constructor(const char *label, std::function<list()> constr)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long, std::nano> duration = end - end;
    std::chrono::duration<long long, std::nano> d = end - end;
    int t = 0;
    for (int i = 0; i < c; ++i)
    {
        {
            start = std::chrono::high_resolution_clock::now();
            list List = constr();
            end = std::chrono::high_resolution_clock::now();
            t = List.size();
            duration += end - start;
            if (c == 1)
            {
                std::cout << "\nTime taken by the " << label << " list to create a list of size " << t;
                if (List.size() <= 200)
                    if constexpr (requires { List.dump(); })
                        List.dump();
                    else
                        dumpList(List);
                std::cout << ": \033[1;33m" << duration.count() << "\033[0m ns.\n";
            }
            start = std::chrono::high_resolution_clock::now();
        }
        end = std::chrono::high_resolution_clock::now();
        d += end - start;
    }
    if (c == 1)
    {
        std::cout << "Time taken to destroy the list: \033[1;33m" << d.count() << "\033[0m ns.";
    }
    else
    {
        std::cout << "\nTime taken by the " << label << " list to create a list of size " << t << " over \033[1;32m" << c << "\033[0m repetitions: \033[1;33m" << duration.count() << "\033[0m ns or \033[1;33m" << duration.count() / 1000000.f << "\033[0m ms averaged to: \033[1;35m" << duration.count() / c << "\033[0m ns.\n";
        std::cout << "Time taken to destroy the list averaged over \033[1;32m" << c << "\033[0m repetitions: \033[1;33m" << duration.count() << "\033[0m ns or \033[1;33m" << d.count() / 1000000.f << "\033[0m ms averaged to: \033[1;35m" << d.count() / c << "\033[0m ns.\n";
    }
}

template <typename list>
void perform(const char *label, char f, std::function<list()> constr)
{
    // list List = constr();
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long, std::nano> duration = end - start;
    int t = 0;

    {
        start = std::chrono::high_resolution_clock::now();
        list List = constr();
        end = std::chrono::high_resolution_clock::now();
        std::cout << "\n\nTime taken by the " << label << " list to create a list of size: " << List.size();
        if (List.size() <= 200)
            if constexpr (requires { List.dump(); })
                List.dump();
            else
                dumpList(List);
        duration = end - start;
        std::cout << " \033[1;33m" << duration.count() << "\033[0m ms\n";

        int i = 0;
        try
        {
            if constexpr (requires { List.dump(); })
            {
                // std::cout << "\nThis is my implementation\n";
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
            else
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
                        if (List.size() > 0)
                            List.pop_front();
                        else
                            throw "Empty list.";
                if (f & OP_POP_BACK)
                    for (i = 0; i < c; ++i)
                        if (List.size() > 0)
                            List.pop_back();
                        else
                            throw "Empty list.";
            }
        }
        catch (const char *x)
        {
            std::cout << "\033[1;31mError: " << x << "\033[0m Ending early.\n";
        }
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        if (f & OP_RETURN)
            std::cout << "\nFront: " << List.front() << " Back: " << List.back() << "\n";
        if (f & OP_ITER)
        {
            int sum = 0;
            std::cout << List.size();
            std::cout << "\033[1;37m{  ";
            
            if constexpr (requires { List.rbegin(); })
            {
                if (List.size() <= 200)
                    for (auto rev = List.rbegin(); rev != List.rend(); ++rev)
                    {
                        const auto &el = *rev;
                        std::cout << el << ", ";
                    }
                start = std::chrono::high_resolution_clock::now();
                for (auto rev = List.rbegin(); rev != List.rend(); ++rev)
                {
                    const auto &el = *rev;
                    sum += el;
                }
                end = std::chrono::high_resolution_clock::now();
            }
            else
            {/**/
                if (List.size() <= 200)
                    for (const auto &el : List)
                    {
                        if (List.size() <= 200)
                            std::cout << el << ", ";
                    }
                start = std::chrono::high_resolution_clock::now();
                for (const auto &el : List)
                {
                    sum += el;
                }
                end = std::chrono::high_resolution_clock::now();
            }
            std::cout << "\b\b  } \033[1;31mChecksum: " << sum << "\033[0m";
            std::chrono::duration<long long, std::nano> d = end - start;
            std::cout << "\nTime taken by the " << label << " list to iterate a list of size " << List.size() << ": \033[1;33m" << d.count() << "\033[0m ns.\n";
        }
        std::cout << "Time taken by the " << label << " list to perform\n";
        getActions(f, i);
        std::cout << " was \033[1;33m" << duration.count() << "\033[0m ns or \033[1;33m" << duration.count() / 1000000.f << "\033[0m ms ";
        if (c != 1 && i != 0)
            std::cout << "which averages to \033[1;35m" << duration.count() / i << "\033[0m ns for all actions.";
        if (List.size() <= 200)
        {
            std::cout << "\nand resulted in a list ";
            if constexpr (requires { List.dump(); })
                List.dump();
            else
                dumpList(List);
        }
        t = List.size();
        start = std::chrono::high_resolution_clock::now();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "\nTime taken to destroy the list (size " << t << "): \033[1;33m" << duration.count() << "\033[0m ns or \033[1;33m" << duration.count() / 1000000.f << "\033[0m ms ";
}

template <typename list>
void testList(const char *label, std::function<list()> constr, unsigned char f, bool mask = false)
{
    if (mask)
        interpretBitMask(f);

    if (!f & FLAG_INPUT)
    {
        constructor<list>(label, constr);
    }
    else
    {
        perform<list>(label, f, constr);
    }
}

void testScarletList(unsigned char f, bool mask = false)
{
    testList<Scarlet::List<int>>(
        ScarletLabel,
        []
        {
            return Scarlet::List<int>(nnn);
        },
        f,
        mask);
}
void testTwoWayScarletList(unsigned char f, bool mask = false)
{
    testList<Scarlet::twoWayList<int>>(
        TwoWayLabel,
        []
        {
            return Scarlet::twoWayList<int>(nnn);
        },
        f,
        mask);
}
void testCyclicScarletList(unsigned char f, bool mask = false)
{
    testList<Scarlet::cyclicList<int>>(
        CyclicLabel,
        []
        {
            return Scarlet::cyclicList<int>(nnn);
        },
        f,
        mask);
}
void testStandardList(unsigned char f, bool mask = false)
{
    testList<std::list<int>>(
        StandardLabel,
        []
        {
            return std::list<int>{nnn};
        },
        f,
        mask);
}

template <typename list>
void allTestList(const char *label, std::function<list()> constr)
{
    std::cout << "\n";
    unsigned char f = 0;
    testList<list>(label, constr, f);
    f ^= OP_PUSH_FRONT;
    testList<list>(label, constr, f);
    f = 0;
    f ^= OP_PUSH_BACK;
    testList<list>(label, constr, f);
    f = 0;
    f ^= OP_POP_FRONT;
    testList<list>(label, constr, f);
    f = 0;
    f ^= OP_POP_BACK;
    testList<list>(label, constr, f);
    f = 0;
    f ^= OP_ITER;
    testList<list>(label, constr, f);
    std::cout << "\n"
              << label << " tests finished.\n";
}

template <typename list>
void fullTestList(const char *label, std::function<list()> constr)
{
    std::cout << "\n";
    unsigned char f = 0;
    testList<list>(label, constr, f);
    f ^= OP_PUSH_FRONT;
    f ^= OP_PUSH_BACK;
    f ^= OP_POP_FRONT;
    f ^= OP_POP_BACK;
    testList<list>(label, constr, f);
    f = 0;
    f ^= OP_ITER;
    testList<list>(label, constr, f);
    std::cout << "\n"
              << label << " tests finished.\n";
}

void allScarletTest()
{
    allTestList<Scarlet::List<int>>(
        ScarletLabel,
        []
        {
            return Scarlet::List<int>(lll);
        });
}
void allTwoWayScarletTest()
{
    allTestList<Scarlet::twoWayList<int>>(
        TwoWayLabel,
        []
        {
            return Scarlet::twoWayList<int>(lll);
        });
}
void allCyclicScarletTest()
{
    allTestList<Scarlet::cyclicList<int>>(
        CyclicLabel,
        []
        {
            return Scarlet::cyclicList<int>(lll);
        });
}
void allStandardTest()
{
    allTestList<std::list<int>>(
        StandardLabel,
        []
        {
            return std::list<int>{lll};
        });
}

void fullScarletTest()
{
    fullTestList<Scarlet::List<int>>(
        ScarletLabel,
        []
        {
            return Scarlet::List<int>(lll);
        });
}
void fullTwoWayScarletTest()
{
    fullTestList<Scarlet::twoWayList<int>>(
        TwoWayLabel,
        []
        {
            return Scarlet::twoWayList<int>(lll);
        });
}
void fullCyclicScarletTest()
{
    fullTestList<Scarlet::cyclicList<int>>(
        CyclicLabel,
        []
        {
            return Scarlet::cyclicList<int>(lll);
        });
}
void fullStandardTest()
{
    fullTestList<std::list<int>>(
        StandardLabel,
        []
        {
            return std::list<int>{lll};
        });
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
            f ^= OP_RETURN;
            break;
        case '6':
            f ^= OP_ITER;
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
            fullScarletTest();
            if (a & OP_PUSH_FRONT)
                fullStandardTest();
            if (a & OP_PUSH_BACK)
                fullTwoWayScarletTest();
            if (a & OP_POP_FRONT)
                fullCyclicScarletTest();
            if (a & FLAG_INPUT)
                fullScarletTest();
            throw "Done testing.";
        case 's':
            f ^= OP_PUSH_FRONT;
            f ^= OP_PUSH_BACK;
            f ^= OP_POP_FRONT;
            f ^= OP_ITER;
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
    std::cout << "0. " << ScarletLabel << " library.\n1. " << TwoWayLabel << " library.\n2. " << CyclicLabel << " library.\n3. " << StandardLabel << " library.\n4. Compare libraries.\n5. \033[1;31mExit.\033[0m\n";

    try
    {
        switch (std::cin.get())
        {
        case '0':
            a ^= FLAG_INPUT;
            testScarletList(createBitMask(), true);
            return 1;
            break;
        case '1':
            a ^= OP_PUSH_BACK;
            testTwoWayScarletList(createBitMask(), true);
            return 1;
            break;
        case '2':
            a ^= OP_POP_FRONT;
            testCyclicScarletList(createBitMask(), true);
            return 1;
            break;
        case '3':
            a ^= OP_PUSH_FRONT;
            testStandardList(createBitMask(), true);
            return 1;
            break;
        case '4':
            a ^= FLAG_INPUT;
            std::cout << a << '\n';
            a ^= OP_PUSH_FRONT;
            std::cout << a << '\n';
            a ^= OP_PUSH_BACK;
            std::cout << a << '\n';
            a ^= OP_POP_FRONT;
            std::cout << a << '\n';
            std::cout << "Compare libraries.\n";
            ff = createBitMask();
            interpretBitMask(ff);
            std::cout << "\n\n"
                      << StandardLabel << " library:";
            testStandardList(ff);
            std::cout << "\n\n"
                      << ScarletLabel << " library:";
            testScarletList(ff);
            std::cout << "\n\n"
                      << TwoWayLabel << " library:";
            testTwoWayScarletList(ff);
            std::cout << "\n\n"
                      << CyclicLabel << " library:";
            testCyclicScarletList(ff);
            return 1;
            break;
        case '5':
            return 0;
        case 's':
            allScarletTest();
            allStandardTest();
            return 2;
        case 'd':
            allStandardTest();
            allScarletTest();
            return 2;
        case '6':
            allStandardTest();
            return 2;
        case '7':
            allScarletTest();
            allScarletTest();
            return 2;
        case '8':
            allScarletTest();
            return 2;
        case '9':
            allScarletTest();
            allScarletTest();
            return 2;
        case 'a':
            allScarletTest();
            allStandardTest();
            allTwoWayScarletTest();
            allCyclicScarletTest();
            allScarletTest();
            return 2;
        default:
            std::cout << "Invalid parameter.\n";
            return -1;
            break;
        } /**/
    }
    catch (const char *e)
    {
        std::cout << "\n\033[1;32m" << e << "\033[0m\n";
    }
}