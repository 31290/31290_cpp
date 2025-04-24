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
    initiate();

    (push_back(args), ...);
}

template <typename T>
void Scarlet::List<T>::initiate()
{
    head = nullptr;
    tail = nullptr;
    len = 0;
}

template <typename T>
Scarlet::List<T>::~List()
{
    Node *curr = head;
    while (curr != nullptr)
    {
        Node *n = curr->next;
        delete curr;
        curr = n;
    }
}

template <typename T>
int Scarlet::List<T>::size()
{
    return len;
}

#ifdef ENABLE_DUMP
template <typename T>
void Scarlet::List<T>::dumpContent()
{
    Node *n = head;
    std::cout << "\033[1;34m{  ";
    while (n != nullptr)
    {
        std::cout << n->value << ", ";
        n = n->next;
    }
    std::cout << "\b\b  }\033[0m";
}

template <typename T>
void Scarlet::List<T>::dump()
{
    dumpContent();
    std::cout << "\033[1;34m(Size:" << len << ")\033[0m";
}
#endif

#ifndef ENABLE_DUMP
#warning "Dump functions are unavailable."
#endif

template <typename T>
void Scarlet::List<T>::push_front(T val)
{
    len++;
    Node *x = new Node(val, (head == nullptr) ? nullptr : head);
    head = x;
    if (tail == nullptr)
        tail = head;
}

template <typename T>
void Scarlet::List<T>::push_back(T val)
{
    len++;
    Node *x = new Node(val, nullptr);
    if (tail != nullptr)
        tail->next = x;
    tail = x;
    if (head == nullptr)
        head = tail;
}

template <typename T>
T Scarlet::List<T>::pop_front()
{
    if (head == nullptr)
        throw "Empty list.";
    T t = head->value;
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        len--;
        return t;
    }
    Node *n = head->next;
    delete head;
    head = n;
    len--;
    return t;
}

template <typename T>
T Scarlet::List<T>::pop_back()
{
    if (tail == nullptr)
        throw "Empty list.";
    T t = tail->value;
    if (head == tail)
    {
        delete tail;
        head = nullptr;
        tail = nullptr;
        len--;
        return t;
    }
    Node *n = head;
    while (n->next != tail)
    {
        n = n->next;
    }
    delete tail;
    tail = n;
    tail->next = nullptr;
    len--;
    return t;
}

template <typename T>
T Scarlet::List<T>::front()
{
    if (head != nullptr)
        return head->value;
    throw "Empty list.";
}

template <typename T>
T Scarlet::List<T>::back()
{
    if (tail != nullptr)
        return head->value;
    throw "Empty list.";
}

template <typename T>
bool Scarlet::List<T>::empty()
{
    return len == 0;
}

template <typename T>
Scarlet::List<T>::Node::Node(T value, Node *next) : value(value), next(next){};

// twoWayList here.

template <typename T>
template <typename... Args>
Scarlet::twoWayList<T>::twoWayList(Args... args)
{
    initiate();

    (push_back(args), ...);
}

template <typename T>
void Scarlet::twoWayList<T>::push_front(T val)
{
    this->len++;
    Node *x = new Node(val, head, nullptr);
    if (head != nullptr)
        head->prev = x;
    head = x;
    if (tail == nullptr)
        tail = head;
}

template <typename T>
void Scarlet::twoWayList<T>::push_back(T val)
{
    this->len++;
    Node *x = new Node(val, nullptr, tail);
    if (tail != nullptr)
        tail->next = x;
    tail = x;
    if (head == nullptr)
        head = tail;
}

template <typename T>
T Scarlet::twoWayList<T>::pop_back()
{
    if (tail == nullptr)
        throw "Empty list.";
    T t = tail->value;
    if (head == tail)
    {
        delete tail;
        head = nullptr;
        tail = nullptr;
        this->len--;
        return t;
    }
    Node *n = tail->prev;
    delete tail;
    tail = n;
    tail->next = nullptr;
    this->len--;
    return t;
}

template <typename T>
Scarlet::twoWayList<T>::Node::Node(T value, Node *next, Node *prev) : value(value), next(next), prev(prev){};