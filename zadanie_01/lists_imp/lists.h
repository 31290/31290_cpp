#pragma once

namespace Scarlet
{
    template <typename T>
    class List
    {
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
        void dumpNode(Node *n);
        void dumpContent(bool full = false);
        void dump();
        bool empty();

        class Iterator
        {
        public:
            Iterator(Node *ptr);
            T &operator*();
            Iterator &operator++();
            bool operator!=(const Iterator &other);

        protected:
            Node *current;
        };

        Iterator begin();
        Iterator end();
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
        T pop_front();

        class reverseIterator : public List<T>::Iterator
        {
        public:
            reverseIterator &operator++();
        };

        using List<T>::Iterator;

        using List<T>::begin;
        using List<T>::end;

        reverseIterator rbegin();
        reverseIterator rend();

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
        void dumpContent(bool full = false);
        void dump();

        class cyclicIterator : public List<T>::Iterator
        {
        public:
            using Node = typename List<T>::Node;
            cyclicIterator(Node *start, Node *current, bool done = false);
            T &operator*();
            cyclicIterator &operator++();
            bool operator!=(const cyclicIterator &other);

        private:
            Node *_start;
            bool _done;
        };

        cyclicIterator begin();
        cyclicIterator end();

        using typename List<T>::Node;
        using List<T>::dumpNode;
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