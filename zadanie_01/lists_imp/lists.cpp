#include "lists.h"

template <typename T>
Scarlet::List<T>::List()
{
    initiate();
}


template <typename T>
template <typename... Args>
Scarlet::List<T>::List(Args... args)
{
    // do the logic
}

template <typename T>
void Scarlet::List<T>::initiate()
{
    head.next = nullptr;
    tail.next = nullptr;
}

template <typename T>
Scarlet::List<T>::~List()
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
Scarlet::List<T>::Node *Scarlet::List<T>::newNode(T value, Node *prev = nullptr)
{
    List<T>::Node *x = new List<T>::Node;
    x->value = value;
    x->prev = prev;
    x->next = newNode(value, x);
    return x;
}