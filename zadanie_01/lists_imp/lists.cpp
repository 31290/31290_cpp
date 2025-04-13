#include "lists.h"

template <typename T>
Lists<T>::Lists()
{
    initiate();
}

template <typename T>
Lists<T>::Lists(T first)
{
    initiate();
}

template <typename T>
Lists<T>::Lists(Args... args)
{
    initiate();
}

template <typename T>
void Lists<T>::initiate()
{
    head.next = nullptr;
    tail.next = nullptr;
}

template <typename T>
Lists<T>::~Lists()
{
    Node *curr = head.next;
    while (curr->next != nullptr)
    {
        Node *t = curr->next;
        delete curr;
        curr = t;
    }
    delete curr;
}

template <typename T>
Lists<T>::Node *Lists<T>::newNode(T value, Node *prev = nullptr)
{
    Lists<T>::Node *x = new Lists<T>::Node;
    x->value = value;
    x->prev = prev;
    x->next = newNode(value, x);
    return x;
}

// #include <stdarg.h>
// template <typename T>
// Lists<T>::Lists(T first, ...)
// {
//     initiate();

//     va_list ap;
//     va_start(ap, first);

//     T arg = first;
//     while (arg != NULL)
//     {
//         push_back(arg);
//         arg = va_arg(ap, T);
//     }
// }