#pragma once

namespace Scarlet
{
    template <typename T>
    class List
    {
    public:
        // List();
        template <typename... Args>
        List(Args... args);
        ~List();
        void push_front(T val);
        void push_back(T val);
        T pop_front();
        T pop_back();
        T front();
        T back();
        int size();
        void dumpContent();
        void dump();
        bool empty();

        List<T> operator=(T val);

    protected:
        int len;
        struct Node
        {
            T value;
            Node *next;
            Node *prev;
            Node(T value, Node *next = nullptr, Node *prev = nullptr);
        };
        Node *head;
        Node *tail;
        void initiate();
    };

    template <typename T>
    class twoWayList : public List<T>
    {
    public:
        template <typename... Args>
        twoWayList(Args... args);
        /*
        ~twoWayList();
        /**/
        void push_front(T val);
        void push_back(T val);
        T pop_back();

        using typename List<T>::Node;
        using List<T>::size;
        using List<T>::head;
        using List<T>::tail;
        using List<T>::len;
        using List<T>::initiate;
    };

    template <typename T>
    class cyclicList : public List<T>
    {
    public:
        template <typename... Args>
        cyclicList(Args... args);
        ~cyclicList();
        void push_front(T val);
        void push_back(T val);
        T pop_back();
        T pop_front();
        void dumpContent();
        void dump();

        using typename List<T>::Node;
        using List<T>::size;
        using List<T>::head;
        using List<T>::tail;
        using List<T>::len;
        using List<T>::initiate;
        using List<T>::empty;

    protected:
        void updateCycle();
    };
}

#include "lists.cpp"