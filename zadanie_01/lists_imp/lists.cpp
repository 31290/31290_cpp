#include "lists.h"

/*
template <typename T>
Scarlet::List<T>::List()
{
    initiate();
    std::cout << "Empty list created.\n";
}/**/

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
Scarlet::List<T>::Node::Node(T value, Node *next, Node *prev) : value(value), next(next), prev(prev){};

#ifdef ENABLE_DUMP

template <typename T>
void Scarlet::List<T>::dumpNode(Node *n)
{

    std::cout << "\n[\033[1;31mptr: " << n
              << ", \033[1;32mval: " << n->value
              << ", \033[1;33mnext: " << n->next
              << ", \033[1;35mprev: " << n->prev
              << "\033[1;34m]\n";
}

template <typename T>
void Scarlet::List<T>::dumpContent(bool full)
{
    Node *n = head;
    std::cout << "\033[1;34m{  ";
    while (n != nullptr)
    {
        if (full)
        {
            std::cout << "\n";
            dumpNode(n);
            std::cout << "\n";
        }
        else
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

// kurwinator
template <typename T>
Scarlet::List<T>::Iterator::Iterator(Node *ptr) : current(ptr) {}

template <typename T>
T &Scarlet::List<T>::Iterator::operator*()
{
    return current->value;
}

template <typename T>
typename Scarlet::List<T>::Iterator &Scarlet::List<T>::Iterator::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>
bool Scarlet::List<T>::Iterator::operator!=(const Iterator &other)
{
    return current != other.current;
}

template <typename T>
typename Scarlet::List<T>::Iterator Scarlet::List<T>::begin()
{
    return Iterator(head);
}

template <typename T>
typename Scarlet::List<T>::Iterator Scarlet::List<T>::end()
{
    return Iterator(nullptr);
}

// twoWayList here.

template <typename T>
template <typename... Args>
Scarlet::twoWayList<T>::twoWayList(Args... args)
{
    initiate();

    (push_back(args), ...);
} /**/

template <typename T>
void Scarlet::twoWayList<T>::push_front(T val)
{
    len++;
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
T Scarlet::twoWayList<T>::pop_front()
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
    n->prev = nullptr;
    delete head;
    head = n;
    len--;
    return t;
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
        len--;
        return t;
    }
    Node *n = tail->prev;
    delete tail;
    tail = n;
    tail->next = nullptr;
    len--;
    return t;
}

template <typename T>
Scarlet::twoWayList<T>::reverseIterator &Scarlet::twoWayList<T>::reverseIterator::operator++()
{
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename Scarlet::twoWayList<T>::reverseIterator Scarlet::twoWayList<T>::rbegin()
{
    return reverseIterator(tail);
}

template <typename T>
typename Scarlet::twoWayList<T>::reverseIterator Scarlet::twoWayList<T>::rend()
{
    return reverseIterator(nullptr);
}

/**/

/*
template <typename T>
Scarlet::twoWayList<T>::~twoWayList()
{
    Node *curr = head;
    while (curr != nullptr)
    {
        Node *n = curr->next;
        delete curr;
        curr = n;
    }
}
/**/

// cyclicList here.

template <typename T>
template <typename... Args>
Scarlet::cyclicList<T>::cyclicList(Args... args)
{
    initiate();

    (push_back(args), ...);
    if (head != nullptr)
        updateCycle();
}

template <typename T>
Scarlet::cyclicList<T>::~cyclicList()
{
    if (head == nullptr)
        return;
    Node *curr = head;
    do
    {
        Node *next = curr->next;
        delete curr;
        curr = next;
    } while (curr != head);

    head = tail = nullptr;
}

template <typename T>
void Scarlet::cyclicList<T>::push_front(T val)
{
    len++;
    Node *x = new Node(val, (head == nullptr) ? nullptr : head);
    head = x;
    if (tail == nullptr)
        tail = head;
    else
        updateCycle();
}

template <typename T>
void Scarlet::cyclicList<T>::push_back(T val)
{
    len++;
    Node *x = new Node(val, (head == nullptr) ? nullptr : head);
    if (tail != nullptr)
    {
        tail->next = x;
    }
    tail = x;
    if (head == nullptr)
        head = tail;
    else
        updateCycle();
}

template <typename T>
T Scarlet::cyclicList<T>::pop_front()
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
    updateCycle();
    return t;
}

template <typename T>
T Scarlet::cyclicList<T>::pop_back()
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
    tail->next = head;
    len--;
    return t;
}

template <typename T>
void Scarlet::cyclicList<T>::updateCycle()
{
    tail->next = head;
}

#ifdef ENABLE_DUMP
template <typename T>
void Scarlet::cyclicList<T>::dumpContent(bool full)
{
    Node *n = head;
    std::cout << "\033[1;34m{  ";
    while (n != tail)
    {
        if (full)
        {
            std::cout << "\n";
            dumpNode(n);
            std::cout << "\n";
        }
        else
            std::cout << n->value << ", ";
        n = n->next;
    }
    if (!empty())
        if (full)
        {
            std::cout << "\n";
            dumpNode(n);
            std::cout << "\n";
        }
        else
            std::cout << n->value << ", ";
    std::cout << "\b\b  }\033[0m";
}

template <typename T>
void Scarlet::cyclicList<T>::dump()
{
    dumpContent();
    std::cout << "\033[1;34m(Size:" << len << ")\033[0m";
}
#endif

template <typename T>
Scarlet::cyclicList<T>::cyclicIterator::cyclicIterator(Node *start, Node *current, bool done)
    : List<T>::Iterator(current), _start(start), _done(done) {}

template <typename T>
T &Scarlet::cyclicList<T>::cyclicIterator::operator*()
{
    return this->current->value;
}

template <typename T>
typename Scarlet::cyclicList<T>::cyclicIterator &Scarlet::cyclicList<T>::cyclicIterator::operator++()
{
    this->current = this->current->next;
    if (this->current == _start)
    {
        _done = true;
    }
    return *this;
}

template <typename T>
bool Scarlet::cyclicList<T>::cyclicIterator::operator!=(const typename Scarlet::cyclicList<T>::cyclicIterator &other)
{
    return !(this->current == other.current && this->_done == other._done);
}

template <typename T>
typename Scarlet::cyclicList<T>::cyclicIterator Scarlet::cyclicList<T>::begin()
{
    return cyclicIterator(this->head, this->head, this->empty());
}

template <typename T>
typename Scarlet::cyclicList<T>::cyclicIterator Scarlet::cyclicList<T>::end()
{
    return cyclicIterator(this->head, this->head, true);
}