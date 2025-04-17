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
    // KURWA MAĆĆĆĆĆĆĆĆĆĆ
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
    delete head;
    delete tail;
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
    Node *x = new Node(val, (head==nullptr) ? nullptr : head);
    head = x;
    if (tail == nullptr)
        tail = head;
}

template <typename T>
void Scarlet::List<T>::push_back(T val)
{
    len++;
    Node *x = new Node(val);
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
    T t = front();
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
    T t = back();
    delete tail;
    Node *n = head->next;
    while(n->next != tail)
    {
        n = n->next;
    }
    tail = n;
    len--;
    return t;
}

template <typename T>
T Scarlet::List<T>::front()
{
    if (head != nullptr) return head->value;
    throw "Empty list.";
}

template <typename T>
T Scarlet::List<T>::back()
{
    if (tail != nullptr) return head->value;
    throw "Empty list.";
}

template <typename T>
Scarlet::List<T>::Node::Node(T value, Node *next) : value(value), next(next) {};
