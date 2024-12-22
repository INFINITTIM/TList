#include <iostream>

#include "TList.h"

int main()
{
    TList<int> a;
    std::cout << a << std::endl;
    a.PushFront(5);
    std::cout << a << std::endl;
    a.PushFront(5);
    std::cout << a << std::endl;
    a.PushFront(7);
    std::cout << a << std::endl;
    a.PushFront(3);
    std::cout << a << std::endl;
    a.PushInPosition(0, 10);
    std::cout << a << std::endl;
    a.PushFront(4);
    a.PushLast(23);
    a.PushInPosition(0, 180);
    std::cout << a << std::endl;
    std::cout << a[7] << std::endl;
    std::cout << a.IsEmpty() << std::endl;
    std::cout << a.Size() << std::endl;
}

