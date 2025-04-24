#pragma once

namespace Scarlet
{
    template <typename T>
    class List
    {
    public:
        List();
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
            Node(T value, Node *next = nullptr);
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
        ~twoWayList();
        void push_front(T val);
        void push_back(T val);
        T pop_back();

    protected:
        struct Node
        {
            T value;
            Node *next;
            Node *prev;
            Node(T value, Node *next = nullptr, Node *prev = nullptr);
        };
    };

    template <typename T>
    class cyclicList : public List<T>
    {
    public:
        /*there will be a cyclic list here
         _   |~  _
        [_]--'--[_]
        |'|""`""|'|
        | | /^\ | |
        |_|_|I|_|_|
        */

    private:
        void updateCycle() {};
    };
}

#include "lists.cpp"