#include <iostream>

int main()
{
    int i = 1;

    while (i > 0)
    {
        if (i-- > 0)
        {
            std::cout << "Hello, World! " << i << std::endl;
        }
        else
        {
            std::cout << "Goodbye, World! " << i << std::endl;
        }
    }
}