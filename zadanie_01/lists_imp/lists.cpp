#include "lists.h"
#include <stdarg.h>

template <typename T>
Lists<T>::Lists()
{
    initiate();
}

template <typename T>
Lists<T>::Lists(T first, ...)
{
    initiate();

    va_list ap;
    va_start(ap, first);
}

template <typename T>
void Lists<T>::initiate()
{
    head.prev = nullptr;
    head.next = nullptr;
    tail.next = nullptr;
    tail.prev = nullptr;
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