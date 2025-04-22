#include <functional>
#include "lists.h"

#define lll 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20

template <typename ListType>
void testList(char* label, std::function<ListType()> constructor) {
    auto start = std::chrono::steady_clock::now();

    ListType lst = constructor();

    int sum = 0;
    for (auto& val : lst) {
        sum += val;
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << label << ": " << elapsed.count() << "s (sum = " << sum << ")\n";
}