#include "lists.h"
#include <stdarg.h>

Lists::Lists(...)
{
    head.prev = nullptr;
    tail.next = nullptr;

    va_list ap;
    va_start(ap);
}

Lists::~Lists()
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

Lists::Node *Lists::newNode(int value, Node *prev = nullptr)
{
    Lists::Node *x = new Lists::Node;
    x->value = value;
    x->prev = prev;
    x->next = newNode(value, x);
    return x;
}